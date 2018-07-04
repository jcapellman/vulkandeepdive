using System;
using System.Collections.Generic;
using System.Linq;

using SharpVulkan;

using Tutorial01.Common;
using Tutorial01.Objects;

namespace Tutorial01
{
    public class VulkanRenderer :IDisposable
    {
        private Instance _instance;

        public List<VulkanDevice> Devices => _instance.PhysicalDevices.Select(a => new VulkanDevice(a)).ToList();

        public unsafe ReturnSet<bool> Initialize()
        {
            try
            {
                var applicationInfo = new ApplicationInfo
                {
                    StructureType = StructureType.ApplicationInfo,
                    EngineVersion = 0,
                    ApiVersion = Vulkan.ApiVersion
                };

                var instanceCreateInfo = new InstanceCreateInfo
                {
                    StructureType = StructureType.InstanceCreateInfo,
                    ApplicationInfo = new IntPtr(&applicationInfo)
                };

                _instance = Vulkan.CreateInstance(ref instanceCreateInfo);

                return new ReturnSet<bool>(true);
            }
            catch (Exception ex)
            {
                return new ReturnSet<bool>(ex);
            }
        }

        private unsafe void ReleaseUnmanagedResources()
        {
            _instance.Destroy();
        }

        public void Dispose()
        {
            ReleaseUnmanagedResources();

            GC.SuppressFinalize(this);
        }
    }
}