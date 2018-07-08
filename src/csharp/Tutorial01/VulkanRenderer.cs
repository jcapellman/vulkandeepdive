﻿// Copyright (c) 2018 Jarred Capellman
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
using System.Diagnostics;
using System.Linq;
using System.Windows.Forms;

using SharpDX.Windows;

using VulkanNET;

using Tutorial01.Common;
using Tutorial01.Objects;

namespace Tutorial01
{
    public class VulkanRenderer : IDisposable
    {
        private readonly Form form;

        private Instance _instance;
        
        private Surface _surface;

        private Queue _queue;

        public List<VulkanDevice> Devices => _instance.PhysicalDevices.Select(a => new VulkanDevice(a)).ToList();

        private IntPtr[] BuildExtensionArray(params ExtensionNames[] extensionName) => extensionName.Select(a => a.ToIntPtr()).ToArray();

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

                var enabledExtensionNames =
                    BuildExtensionArray(ExtensionNames.VK_KHR_surface, ExtensionNames.VK_KHR_win32_surface, ExtensionNames.VK_EXT_debug_report);

                fixed (void* enabledExtensionNamesPointer = &enabledExtensionNames[0])
                {
                    var instanceCreateInfo = new InstanceCreateInfo
                    {
                        StructureType = StructureType.InstanceCreateInfo,
                        ApplicationInfo = new IntPtr(&applicationInfo),
                        EnabledExtensionCount = (uint) enabledExtensionNames.Length,
                        EnabledExtensionNames = new IntPtr(enabledExtensionNamesPointer),
                    };

                    _instance = Vulkan.CreateInstance(ref instanceCreateInfo);

                    var surfaceCreateInfo = new Win32SurfaceCreateInfo
                    {
                        StructureType = StructureType.Win32SurfaceCreateInfo,
                        InstanceHandle = Process.GetCurrentProcess().Handle,
                        WindowHandle = form.Handle,
                    };

                    _surface = _instance.CreateWin32Surface(surfaceCreateInfo);

                    return new ReturnSet<bool>(true);
                }
            }
            catch (Exception ex)
            {
                return new ReturnSet<bool>(ex);
            }
        }

        public unsafe ReturnSet<bool> InitializeLogicalDevice(VulkanDevice physicalDevice)
        {
            uint queuePriorities = 0;

            var deviceQueueCreateInfo = new DeviceQueueCreateInfo
            {
                StructureType = StructureType.DeviceQueueCreateInfo,
                QueueFamilyIndex = 0,
                QueueCount = 1,
                QueuePriorities = new IntPtr(&queuePriorities)
            };

            var physicalDeviceFeatures = new PhysicalDeviceFeatures
            {
                ShaderClipDistance = true,
            };

            var enabledExtensionNames = BuildExtensionArray(ExtensionNames.VK_KHR_swapchain);

            fixed (void * enabledExtensionNamesPtr = &enabledExtensionNames[0])
            {
                var deviceCreateInfo = new DeviceCreateInfo
                {
                    StructureType = StructureType.DeviceCreateInfo,
                    QueueCreateInfoCount = 1,
                    QueueCreateInfos = new IntPtr(&deviceQueueCreateInfo),
                    EnabledExtensionCount = (uint) enabledExtensionNames.Length,
                    EnabledExtensionNames = new IntPtr(enabledExtensionNamesPtr),
                    EnabledFeatures = new IntPtr(&physicalDeviceFeatures)
                };

                physicalDevice.CreateLogicalDevice(deviceCreateInfo);
            }

            _queue = physicalDevice.CreateQueue(_surface);
           
            return new ReturnSet<bool>(true);
        }

        public VulkanRenderer()
        {
            form = new RenderForm("Vulkan Tutorial 1");
        }

        private unsafe void ReleaseUnmanagedResources()
        {
            _instance.DestroySurface(_surface);

            foreach (var device in Devices)
            {                
                device.Dispose();
            }
            
            _instance.Destroy();
        }

        public void Dispose()
        {
            ReleaseUnmanagedResources();

            GC.SuppressFinalize(this);
        }
    }
}