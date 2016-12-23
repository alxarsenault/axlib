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

/// @defgroup util
/// @{

// http://codereview.stackexchange.com/questions/20058/a-c11-any-class

#include <type_traits>
#include <utility>
#include <typeinfo>
#include <string>
#include <cassert>

namespace ax {

template <class T> using StorageType = typename std::decay<T>::type;

class Var {
public:
	bool is_null() const;
	bool not_null() const;

	template <typename U>
	Var(U&& value)
		: ptr(new Derived<StorageType<U>>(std::forward<U>(value)))
	{
	}

	template <class U> bool is() const
	{
		typedef StorageType<U> T;

		auto derived = dynamic_cast<Derived<T>*>(ptr);

		return derived;
	}

	template <class U> StorageType<U>& as()
	{
		typedef StorageType<U> T;

		auto derived = dynamic_cast<Derived<T>*>(ptr);

		if (!derived) {
			throw std::bad_cast();
		}

		return derived->value;
	}

	template <class U> operator U()
	{
		return as<StorageType<U>>();
	}

	Var()
		: ptr(nullptr)
	{
	}

	Var(Var& that)
		: ptr(that.clone())
	{
	}

	Var(Var&& that)
		: ptr(that.ptr)
	{
		that.ptr = nullptr;
	}

	Var(const Var& that)
		: ptr(that.clone())
	{
	}

	Var(const Var&& that)
		: ptr(that.clone())
	{
	}

	Var& operator=(const Var& a)
	{
		if (ptr == a.ptr) {
			return *this;
		}

		auto old_ptr = ptr;

		ptr = a.clone();

		if (old_ptr) {
			delete old_ptr;
		}

		return *this;
	}

	Var& operator=(Var&& a)
	{
		if (ptr == a.ptr) {
			return *this;
		}

		std::swap(ptr, a.ptr);

		return *this;
	}

	~Var()
	{
		if (ptr) {
			delete ptr;
		}
	}

private:
	class Base {
	public:
		virtual ~Base()
		{
		}
		virtual Base* clone() const = 0;
	};

	template <typename T> struct Derived : Base {
		template <typename U>
		Derived(U&& value)
			: value(std::forward<U>(value))
		{
		}

		T value;

		Base* clone() const
		{
			return new Derived<T>(value);
		}
	};

	Base* clone() const
	{
		if (ptr) {
			return ptr->clone();
		}
		else {
			return nullptr;
		}
	}

	Base* ptr;
};
}

/// @}
