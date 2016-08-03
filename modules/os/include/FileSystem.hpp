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
 
#pragma once

/// @defgroup os
/// @{

#include <string>
#include <vector>
#include <bitset>
#include <sys/types.h> // mode_t.

namespace ax {
namespace os {
	class Path {
	public:
		enum class Type {
			INVALID,
			REGULAR,
			DIRECTORY,
			FIFO,
			SOCKET,
			CHAR_DEVICE,
			BLOCK_DEVICE,
			SYMB_LINK,
			UNKNOWN
		};

		class Permission {
		public:
			enum class Type { READ, WRITE, EXEC };

			Permission(bool read, bool write, bool exec)
			{
				_perms[0] = read;
				_perms[1] = write;
				_perms[2] = exec;
			}

			bool operator[](const Type& permission) const
			{
				return _perms[static_cast<int>(permission)];
			}

			bool All() const
			{
				return _perms.all();
			}

		private:
			std::bitset<3> _perms;
		};

		Path(const std::string& file_path);

		Path(const std::string& file_path, Path::Type type, bool overwrite = false);

		bool IsValid() const
		{
			return _is_valid;
		}

		inline bool IsDirectory() const
		{
			return _type == Type::DIRECTORY;
		}

		inline bool IsRegular() const
		{
			return _type == Type::REGULAR;
		}

		inline bool IsSymbolicLink() const
		{
			return _type == Type::SYMB_LINK;
		}

		inline bool IsFifo() const
		{
			return _type == Type::FIFO;
		}

		inline bool IsSocket() const
		{
			return _type == Type::SOCKET;
		}

		inline Type GetType() const
		{
			return _type;
		}

		inline const std::string& GetPath() const
		{
			return _path;
		}

		inline const std::string& GetName() const
		{
			return _name;
		}

		inline const std::string& GetFullName() const
		{
			return _file_name;
		}

		inline const std::string& GetExtension() const
		{
			return _ext;
		}

		inline bool IsHidden() const
		{
			return _is_hidden;
		}

		inline bool IsAbsolute() const
		{
			return _is_absolute;
		}

		inline bool IsRelative() const
		{
			return !_is_absolute;
		}

		std::string GetAbsolutePath() const;

		inline bool HasContent() const
		{
			return _has_content;
		}

		std::vector<std::string> GetPathArray() const;

		std::vector<std::string> GetAbsolutePathArray() const;

		Permission GetOwnerPermission() const;

		Permission GetGroupPermission() const;

		Permission GetOtherPermission() const;

		std::vector<std::string> GetDirectoryList() const;

		std::vector<Path> GetDirectoryContent() const;

	private:
		Type _type;

		std::string _path;
		std::string _name;
		std::string _ext;
		std::string _file_name;
		mode_t _perm;

		bool _is_hidden;
		bool _is_valid;
		bool _is_absolute;
		bool _has_content;
	};
} // os.
} // ax.

/// @}
