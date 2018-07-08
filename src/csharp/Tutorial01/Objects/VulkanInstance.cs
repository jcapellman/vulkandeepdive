// Copyright (c) 2018 Jarred Capellman
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

using System;
using System.Linq;

using Tutorial01.Common;
using Tutorial01.Enums;

using VulkanNET;

namespace Tutorial01.Objects
{
    public static class VulkanInstance
    {
        private static IntPtr[] BuildExtensionArray(params ExtensionNames[] extensionName) => extensionName.Select(a => a.ToIntPtr()).ToArray();

        public static unsafe ReturnSet<Instance> Create()
        {
            try
            {
                var applicationInfo = new ApplicationInfo
                {
                    StructureType = StructureType.ApplicationInfo,
                    EngineVersion = 0,
                    ApiVersion = Vulkan.ApiVersion
                };

                var enabledExtensionNames =
                    BuildExtensionArray(ExtensionNames.VK_KHR_surface, ExtensionNames.VK_KHR_win32_surface,
                        ExtensionNames.VK_EXT_debug_report);

                fixed (void* enabledExtensionNamesPointer = &enabledExtensionNames[0])
                {
                    var instanceCreateInfo = new InstanceCreateInfo
                    {
                        StructureType = StructureType.InstanceCreateInfo,
                        ApplicationInfo = new IntPtr(&applicationInfo),
                        EnabledExtensionCount = (uint) enabledExtensionNames.Length,
                        EnabledExtensionNames = new IntPtr(enabledExtensionNamesPointer),
                    };

                    return new ReturnSet<Instance>(Vulkan.CreateInstance(ref instanceCreateInfo));
                }
            }
            catch (Exception ex)
            {
                return new ReturnSet<Instance>(ex);
            }
        }
    }
}