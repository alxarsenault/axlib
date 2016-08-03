/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of axLib.
 *
 * axLib is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axFrameworks License.
 *
 * axLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLib. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLib, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#include "Terminal.hpp"
#include "ConsolePrint.hpp"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>

#ifdef __linux__
#include <pty.h>
#include <utmp.h>
#endif // __linux__

#ifdef __APPLE__
#include <util.h>
#endif //__APPLE__

#ifdef __FreeBSD__
#include <libutil.h> // Need to link with -lutil to call login_tty.
#endif // __FreeBSD__

ax::os::Terminal::Terminal(std::shared_ptr<ax::event::Manager> evt_manager)
	: ax::event::Object(evt_manager)
{
}

bool ax::os::Terminal::Execute(const std::string& program_folder_path, const std::string& program_name,
	const std::vector<std::string>& args)
{
	int fd_master = posix_openpt(O_RDWR | O_NOCTTY);

	int gd = grantpt(fd_master);

	if (gd == -1) {
		ax::util::console::Error("Can't grand master.");
	}

	if (fd_master == -1) {
		ax::util::console::Error("Can't open terminal.");
	}

	// Unlock PTY.
	if (unlockpt(fd_master) == -1) {
		ax::util::console::Error("Can't unlock pty.");
	}

	const char* pts = ptsname(fd_master);

	if (pts == NULL) {
		ax::util::console::Error("Can't get pty name.");
	}

	//    int filedes[2]; // [0] Read, [1] Write.
	//
	//    if (pipe(filedes) == -1)
	//    {
	//        ax::Error("Can't creare pipe.");
	//        return false;
	//    }

	int fd_slave = open(pts, O_RDWR);

	if (fd_slave == -1) {
		ax::util::console::Error("Can't open slave pts.");
	}

	// Create fork to execute program.
	pid_t pid = fork();

	// Fork error.
	if (pid == -1) {
		ax::util::console::Error("Can't create fork process.");
		return false;
	}

	// Child process.
	else if (pid == 0) {
		int err = -1;

		//        do
		//        {
		//            // Copy write file descriptor as standard output.
		//            err = dup2(filedes[1], STDOUT_FILENO);
		//
		//        } while(err == -1 && errno == EINTR);

		if (close(fd_master)) {
			ax::util::console::Error("Can't close master pty.");
		}

		close(0); // Close standard input (current terminal)
		close(1); // Close standard output (current terminal)
		close(2); // Close standard error (current terminal)

		if (login_tty(fd_slave) == -1) {
			ax::util::console::Error("Can't login slave pts.");
		}

		dup2(fd_slave, STDIN_FILENO); // PTY becomes standard output (1)
		dup2(fd_slave, STDOUT_FILENO); // PTY becomes standard output (1)
		dup2(fd_slave, STDERR_FILENO); // PTY becomes standard error (2)

		close(fd_slave);

		// Add program name as first argument and copy all
		// std::string args in ax::StringVector to
		// std::vector<const char*> (needed to call execv).
		std::vector<const char*> c_args(args.size() + 2);

		// Add program path to arguments.
		c_args[0] = program_name.data();

		// Copy all arguments from args.
		std::transform(args.begin(), args.end(),
			c_args.begin() + 1, // Start adding after program path.
			[](const std::string& arg) { return arg.c_str(); });

		// Add null character at the end off c_args.
		c_args.back() = (char*)0;

		std::string path = program_folder_path + program_name;

		// Call program.
		err = execv(path.c_str(), (char* const*)c_args.data());

		// This should never be called except in case of error.
		ax::util::console::Error("Can't execute program", program_name);

		// Not sure where goes the return value in child process.
		return false;
	}

	// Parent process.
	close(fd_slave);

	//    write(fd_slave, "pwd\n", 4);

	//    sleep(4);
	//    write(fd_master, "pwd\n", 4);
	//    ax::Print("TEXT");
	//    write(fd_master, "pwd\n", 4);

	// Close write file descriptor.
	//    close(filedes[1]);
	_fd_master = fd_master;

	// Return true if the thread object identifies an active thread
	// of execution, false otherwise.
	if (_read_child_thread.joinable() == false) {
		_read_child_thread = std::thread(&ReadFromChild, std::ref(*this), fd_master);
		// filedes[0]);
		_read_child_thread.detach();
	}

	//    write(fd_master, "pwd\n", 4);
	// File descriptor filedes[0] will be close at the end of read.

	// wait(0);

	return true;
}

bool ax::os::Terminal::Write(const std::string& command)
{
	write(_fd_master, command.c_str(), command.size());
	return true;
}

void ax::os::Terminal::ReadFromChild(Terminal& terminal, const int& stdin_fd)
{
	char buffer[4096];

	terminal.PushEvent(READ_CHILD_BEGIN, new ax::event::StringMsg("BEGIN"));

	// Read output from child program.
	while (1) {
		ssize_t count = read(stdin_fd, buffer, sizeof(buffer));

		// Read error.
		if (count == -1) {
			// Interrupted function call.
			if (errno == EINTR) {
				continue;
			}
			else {
				ax::util::console::Error("Can't read child process.");
				return;
			}
		}
		// End of reading file.
		else if (count == 0) {
			terminal.PushEvent(READ_CHILD_END, new ax::event::StringMsg("END"));

			// Close read file descriptor.
			close(stdin_fd);
			return;
		}
		else {
			// Process output buffer.
			std::string out_str(buffer, count);

			terminal.PushEvent(READ_CHILD_OUTPUT, new ax::event::StringMsg(out_str));
		}
	}
}
