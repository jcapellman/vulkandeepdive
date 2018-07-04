using System;
using System.Linq;

using SharpVulkan;

namespace Tutorial01.Helpers
{
    public static class ExtensionMethods
    {
        public static string ToFullString(this PhysicalDeviceProperties.DeviceNameArray nameArray)
        {
            var fields = nameArray.GetType().GetFields();

            return (from field in fields where field.IsPublic select field.GetValue(nameArray) 
                into value select Convert.ToChar(value)).TakeWhile(charValue => charValue != char.MinValue).Aggregate(string.Empty, (current, charValue) => current + charValue);
        }
    }
}