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
using System.Windows.Forms;

using SharpDX.Windows;

using VulkanNET;

using Tutorial01.Common;
using Tutorial01.Enums;
using Tutorial01.Objects;

namespace Tutorial01
{
    public class VulkanRenderer : IDisposable
    {
        private readonly Form _form;

        private Instance _instance;
        
        private Surface _surface;

        private Queue _queue;

        public List<VulkanDevice> Devices => _instance.PhysicalDevices.Select(a => new VulkanDevice(a)).ToList();

        public ReturnSet<bool> Initialize(Logger logger)
        {
            try
            {
                var instanceCreationResult = VulkanInstance.Create();

                if (instanceCreationResult.IsError)
                {
                    throw instanceCreationResult.Error;
                }

                _instance = instanceCreationResult.Value;

                logger.AddMessage("Instance created successfully");

                var surfaceCreationResult = VulkanSurface.Create(_instance, _form);

                if (surfaceCreationResult.IsError)
                {
                    throw surfaceCreationResult.Error;
                }

                _surface = surfaceCreationResult.Value;

                logger.AddMessage("Surface created successfully");

                return new ReturnSet<bool>(true);                
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

            var enabledLayerNames = new[]
            {
                ExtensionNames.VK_LAYER_LUNARG_standard_validation.ToIntPtr()
            };

            var enabledExtensionNames = new[]
            {
                ExtensionNames.VK_KHR_swapchain.ToIntPtr()
            };

            fixed (void* enabledLayerNamesPointer = &enabledLayerNames[0])
            fixed (void* enabledExtensionNamesPointer = &enabledExtensionNames[0])
            {
                var deviceCreateInfo = new DeviceCreateInfo
                {
                    StructureType = StructureType.DeviceCreateInfo,
                    QueueCreateInfoCount = 1,
                    QueueCreateInfos = new IntPtr(&deviceQueueCreateInfo),
                    EnabledExtensionCount = (uint) enabledExtensionNames.Length,
                    EnabledExtensionNames = new IntPtr(enabledExtensionNamesPointer),
                    EnabledFeatures = new IntPtr(&physicalDeviceFeatures),
                    EnabledLayerCount = (uint) enabledLayerNames.Length,
                    EnabledLayerNames = new IntPtr(enabledLayerNamesPointer)
                };
                
                physicalDevice.CreateLogicalDevice(deviceCreateInfo);

                _queue = physicalDevice.CreateQueue(_surface);

                return new ReturnSet<bool>(true);
            }
        }

        public VulkanRenderer()
        {
            _form = new RenderForm(Constants.TutorialName);
        }

        private unsafe void ReleaseUnmanagedResources()
        {
            _instance.DestroySurface(_surface);

            foreach (var device in Devices)
            {                
                device.Dispose();
            }
            
            _instance.Destroy();

            _form.Dispose();
        }

        public void Dispose()
        {
            ReleaseUnmanagedResources();

            GC.SuppressFinalize(this);
        }
    }
}