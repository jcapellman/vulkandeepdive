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
using System.Collections.Generic;
using System.Linq;

using VulkanNET;

using Tutorial01.Common;
using Tutorial01.Objects;

namespace Tutorial01
{
    public class VulkanRenderer : IDisposable
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