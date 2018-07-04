using SharpVulkan;

using Tutorial01.Helpers;

namespace Tutorial01.Objects
{
    public class VulkanDevice
    {
        private PhysicalDevice _physicalDevice;

        public VulkanDevice(PhysicalDevice physicalDevice)
        {
            _physicalDevice = physicalDevice;
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

                _name = properties.DeviceName.ToFullString();

                return _name;
            }
        }
    }
}