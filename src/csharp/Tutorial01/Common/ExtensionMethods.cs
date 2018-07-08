using System;
using System.Runtime.InteropServices;

using Tutorial01.Enums;

namespace Tutorial01.Common
{
    public static class ExtensionMethods
    {
        public static IntPtr ToIntPtr(this ExtensionNames extensionName) =>
            Marshal.StringToHGlobalAnsi(extensionName.ToString());
    }
}