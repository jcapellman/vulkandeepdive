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

using VulkanNET;

namespace Tutorial01.Objects
{
    public class VulkanDevice
    {
        private PhysicalDevice _physicalDevice;

        public VulkanDevice(PhysicalDevice physicalDevice)
        {
            _physicalDevice = physicalDevice;
        }

        public string DeviceType
        {
            get
            {
                _physicalDevice.GetProperties(out var properties);

                return properties.DeviceType.ToString();
            }
        }

        private string _name;

        public string Name
        {
            get
            {
                if (!string.IsNullOrEmpty(_name))
                {
                    return _name;
                }

                _physicalDevice.GetProperties(out var properties);

                _name = properties.DeviceName.ToString();

                return _name;
            }
        }
    }
}