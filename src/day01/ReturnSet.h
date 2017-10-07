#pragma once

#include "Main.h"

template <class T>
class return_set {
	public:
		T return_value;

		exception caught_exception() const
		{
			return m_exception_;
		}

		string exception_string() const
		{
			return m_exception_.what();
		}

		bool has_error() const
		{
			return m_has_error_;
		}

		explicit return_set(const exception exception) {
			m_exception_ = exception;
			m_has_error_ = true;
		}

		explicit return_set(T object_value) {
			return_value = object_value;
			m_has_error_ = false;
		}
	private:
		exception m_exception_;
		bool m_has_error_;
};
