using System;
using System.Runtime.InteropServices;

namespace Tutorial01.Common
{
    public static class ExtensionMethods
    {
        public static IntPtr ToIntPtr(this ExtensionNames extensionName) =>
            Marshal.StringToHGlobalAnsi(extensionName.ToString());
    }
}