#pragma once

#include "Main.h"

template <class T>
class ReturnSet {
	public:
		T ReturnValue;

		exception Exception() const
		{
			return m_exception;
		}

		string ExceptionString() const
		{
			return m_exception.what();
		}

		bool HasError() const
		{
			return m_hasError;
		}

		explicit ReturnSet(exception exception) {
			m_exception = exception;
			m_hasError = true;
		}

		explicit ReturnSet(T objectValue) {
			ReturnValue = objectValue;
			m_hasError = false;
		}
	private:
		exception m_exception;
		bool m_hasError;
};
