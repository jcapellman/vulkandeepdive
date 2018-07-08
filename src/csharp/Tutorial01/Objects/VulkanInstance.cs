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
    }
}