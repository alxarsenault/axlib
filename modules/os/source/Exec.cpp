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

#include "Exec.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace ax {
namespace os {
	std::string ExecuteProgram(
		const std::string& folder, const std::string& name, const std::vector<std::string>& args)
	{
		int filedes[2]; // [0] Read, [1] Write.

		if (pipe(filedes) == -1) {
			perror("pipe");
			std::cerr << "Can't create pipe." << std::endl;
			return "";
		}

		pid_t pid = fork();

		// Fork error.
		if (pid == -1) {
			std::cerr << "Can't create fork process." << std::endl;
			return "";
		}
		// Child process.
		else if (pid == 0) {
			while ((dup2(filedes[1], STDOUT_FILENO) == -1) && (errno == EINTR)) {
			}

			// Close stdin and stdout file descriptor.
			close(filedes[1]);
			close(filedes[0]);

			// Get formatted arguments vector.
			std::vector<const char*> char_ptr_args = GetCharVectorFromArgs(name, args);

			std::string program_path = folder + name;

			// Call program.
			execv(program_path.c_str(), (char* const*)char_ptr_args.data());

			std::cerr << "Error : Can't exec." << std::endl;
			return "";
		}

		// Parent process.

		// Close stdout file descriptor.
		close(filedes[1]);

		// Get output from child program stdout.
		std::string program_ouput = GetChildProgramOutput(filedes[0]);

		// Close read file descriptor.
		close(filedes[0]);
		wait(0);

		return program_ouput;
	}

	std::vector<const char*> GetCharVectorFromArgs(
		const std::string& prog_name, const std::vector<std::string>& args)
	{
		std::vector<const char*> char_ptr_args;
		char_ptr_args.reserve(args.size() + 2);

		// Add program name to arguments.
		char_ptr_args.push_back(prog_name.data());

		// Copie all arguments from StringVector.
		for (auto& n : args) {
			char_ptr_args.push_back(n.data());
		}

		// Add end of arguments.
		char_ptr_args.push_back((char*)0);

		return char_ptr_args;
	}

	std::string GetChildProgramOutput(const int& stdin_fd)
	{
		std::string program_ouput = "";
		char buffer[4096];

		// Read output from child program.
		while (1) {
			ssize_t count = read(stdin_fd, buffer, sizeof(buffer));

			if (count == -1) {
				if (errno == EINTR) {
					continue;
				}
				else {
					std::cerr << "Error : parent can't read." << std::endl;
					return "";
				}
			}
			else if (count == 0) {
				break;
			}
			else {

				std::string prog_answer(buffer, count);
				program_ouput += prog_answer;
			}
		}

		return program_ouput;
	}
} // os.
} // ax.
