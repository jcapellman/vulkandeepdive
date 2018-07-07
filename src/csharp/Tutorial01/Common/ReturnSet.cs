using System;

namespace Tutorial01.Common
{
    public class ReturnSet<T>
    {
        public T Value { get; }

        public Exception Error { get; }

        public bool IsNullOrError => Value == null || Error != null;

        public bool IsError => Error != null;

        public ReturnSet(T objectValue)
        {
            Value = objectValue;
        }

        public ReturnSet(Exception exception)
        {
            Error = exception;
        }
    }
}