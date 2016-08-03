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
 
#include "FileSystem.hpp"
#include "ConsolePrint.hpp"

#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

namespace ax {
namespace os {

	std::string find_last_separator_name(const std::string& dir_path)
	{
		return dir_path.substr(dir_path.find_last_of("/") + 1);
	}

	std::string get_file_extension(const std::string& file_name)
	{
		std::size_t first_dot = file_name.find_first_of(".");

		if (first_dot == std::string::npos) {
			return "";
		}

		return std::string(file_name.substr(first_dot + 1));
	}

	std::string get_working_directory()
	{
		char temp[4096];
		return (getcwd(temp, 4096) ? std::string(temp) + "/" : std::string(""));
	}

	std::string get_file_name(const std::string& file_name)
	{
		std::size_t first_dot = file_name.find_first_of(".");

		if (first_dot == std::string::npos) {
			return "";
		}

		return std::string(file_name.substr(0, first_dot));
	}

	std::vector<std::string> split_string(const std::string& str, const std::string& delimiter)
	{
		std::vector<std::string> vec;

		std::string r = str;
		size_t pos = 0;
		std::string token;

		while ((pos = r.find(delimiter)) != std::string::npos) {
			token = r.substr(0, pos);
			vec.push_back(token);
			r.erase(0, pos + delimiter.length());
		}

		vec.push_back(r);

		return vec;
	}

	template <typename T> bool has_flag(const T& flag, T check)
	{
		return ((check & flag) != 0);
	}

	Path::Path(const std::string& file_path)
		: _type(Type::INVALID)
		, _path(file_path)
		, _is_hidden(false)
		, _is_valid(false)
		, _is_absolute(false)
		, _has_content(false)

	{
		if (_path.empty()) {
			return;
		}

		// Remove last separator if path is ending with separator.
		if (_path.size() > 1 && _path.back() == '/') {
			_path = _path.substr(0, _path.size() - 1);
		}

		// Check if path is absolute.
		if (_path[0] == '/') {
			_is_absolute = true;
		}

		struct stat buffer;

		// Check if file exist.
		if (stat(file_path.c_str(), &buffer) != 0) {
			return;
		}

		_is_valid = true;

		// Check if file path has content.
		if (buffer.st_size > 0) {
			_has_content = true;
		}

		_perm = buffer.st_mode;

		// Check file type.
		if (S_ISDIR(buffer.st_mode)) {
			_type = Type::DIRECTORY;
			_name = find_last_separator_name(_path);
		}
		else if (S_ISREG(buffer.st_mode)) {
			_type = Type::REGULAR;
			_file_name = find_last_separator_name(_path);
			_ext = get_file_extension(_file_name);
			_name = get_file_name(_file_name);

			if (_name.empty() && !_ext.empty()) {
				_is_hidden = true;
			}
		}
		else if (S_ISCHR(buffer.st_mode)) {
			_type = Type::CHAR_DEVICE;
		}
		else if (S_ISBLK(buffer.st_mode)) {
			_type = Type::BLOCK_DEVICE;
		}
		else if (S_ISFIFO(buffer.st_mode)) {
			_type = Type::FIFO;
		}
		else if (S_ISLNK(buffer.st_mode)) {
			_type = Type::SYMB_LINK;
		}
		else if (S_ISSOCK(buffer.st_mode)) {
			_type = Type::SOCKET;
		}
		else {
			_type = Type::UNKNOWN;
		}
	}

	Path::Path(const std::string& file_path, Path::Type type, bool overwrite)
		: _type(type)
		, _path(file_path)
		, _is_hidden(false)
		, _is_valid(false)
		, _is_absolute(false)
		, _has_content(false)

	{
		if (_path.empty()) {
			return;
		}

		// Remove last separator if path is ending with separator.
		if (_path.size() > 1 && _path.back() == '/') {
			_path = _path.substr(0, _path.size() - 1);
		}

		// Check if path is absolute.
		if (_path[0] == '/') {
			_is_absolute = true;
		}

		bool exist = false;

		struct stat buffer;

		// Check if file exist.
		if (stat(file_path.c_str(), &buffer) == 0) {
			exist = true;
		}

		// If file exist and don't overwrite is on, then return.
		if (exist && !overwrite) {
			_is_valid = true;
			return;
		}

		// Only regular file and directory are supported for now.
		if (type != Type::DIRECTORY && type != Type::REGULAR) {
			util::console::Warning("This path creation file type is not supported yet.");
			return;
		}

		if (exist) {
			util::console::Warning("Overwrite path is not supported yet.");
			_is_valid = true;
			return;
		}
		// Doesn't exist.
		else {

			/// @todo Check for recursive folder creation..

			if (type == Type::DIRECTORY) {
				int status = mkdir(_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

				if (status != 0) {
					ax::util::console::Error("Can't create directory :", _path);
					return;
				}

				_is_valid = true;
			}

			else if (type == Type::REGULAR) {
			}
		}
	}

	std::string Path::GetAbsolutePath() const
	{
		if (_is_absolute) {
			return _path;
		}

		return get_working_directory() + _path;
	}

	std::vector<std::string> Path::GetPathArray() const
	{
		if (!IsValid()) {
			return std::vector<std::string>();
		}

		if (IsAbsolute()) {
			auto split_array = split_string(_path, "/");
			split_array[0] = "/";
			return split_array;
		}

		return split_string(_path, "/");
	}

	std::vector<std::string> Path::GetAbsolutePathArray() const
	{
		if (!IsValid()) {
			return std::vector<std::string>();
		}

		std::string full_path = GetAbsolutePath();
		auto split_array = split_string(full_path, "/");
		split_array[0] = "/";
		return split_array;
	}

	Path::Permission Path::GetOwnerPermission() const
	{
		if (!IsValid()) {
			return Path::Permission(false, false, false);
		}

		// S_IRUSR : Read permission, owner.
		// S_IWUSR : Write permission, owner.
		// S_IXUSR : Execute/search permission, owner.
		return Path::Permission(has_flag<mode_t>(_perm, S_IRUSR), has_flag<mode_t>(_perm, S_IWUSR),
			has_flag<mode_t>(_perm, S_IXUSR));
	}

	Path::Permission Path::GetGroupPermission() const
	{
		if (!IsValid()) {
			return Path::Permission(false, false, false);
		}

		// S_IRGRP : Read permission, group.
		// S_IWGRP : Write permission, group.
		// S_IXGRP : Execute/search permission, group.
		return Path::Permission(has_flag<mode_t>(_perm, S_IRGRP), has_flag<mode_t>(_perm, S_IWGRP),
			has_flag<mode_t>(_perm, S_IXGRP));
	}

	Path::Permission Path::GetOtherPermission() const
	{
		if (!IsValid()) {
			return Path::Permission(false, false, false);
		}

		// S_IROTH : Read permission, others.
		// S_IWOTH : Write permission, others.
		// S_IXOTH : Execute/search permission, others.
		return Path::Permission(has_flag<mode_t>(_perm, S_IROTH), has_flag<mode_t>(_perm, S_IWOTH),
			has_flag<mode_t>(_perm, S_IXOTH));
	}

	std::vector<std::string> Path::GetDirectoryList() const
	{
		std::vector<std::string> dir;

		if (!IsValid() || !IsDirectory()) {
			return dir;
		}

		DIR* dirp;
		struct dirent* dp;

		if ((dirp = opendir(_path.c_str())) == nullptr) {
			ax::util::console::Error("Can't open directory :", _path);
			return dir;
		}

		do {
			if ((dp = readdir(dirp)) != nullptr) {
				std::string d_name(dp->d_name);

				// Remove from list.
				if (d_name == "." || d_name == "..") {
					continue;
				}

				dir.push_back(dp->d_name);
			}

		} while (dp != nullptr);

		closedir(dirp);

		return dir;
	}

	std::vector<Path> Path::GetDirectoryContent() const
	{
		std::vector<Path> content;

		if (!IsValid() || !IsDirectory()) {
			return content;
		}

		std::vector<std::string> dir_list = GetDirectoryList();

		if (dir_list.empty()) {
			return content;
		}

		for (auto& n : dir_list) {
			content.push_back(Path(_path + "/" + n));
		}

		return content;
	}
} // os.
} // ax.
