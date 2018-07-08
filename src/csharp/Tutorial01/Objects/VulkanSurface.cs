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
using System.Diagnostics;
using System.Windows.Forms;

using Tutorial01.Common;

using VulkanNET;

namespace Tutorial01.Objects
{
    public static class VulkanSurface
    {
        public static unsafe ReturnSet<Surface> Create(Instance instance, Form form)
        {
            try
            {
                var surfaceCreateInfo = new Win32SurfaceCreateInfo
                {
                    StructureType = StructureType.Win32SurfaceCreateInfo,
                    InstanceHandle = Process.GetCurrentProcess().Handle,
                    WindowHandle = form.Handle,
                };

                return new ReturnSet<Surface>(instance.CreateWin32Surface(surfaceCreateInfo));
            }
            catch (Exception ex)
            {
                return new ReturnSet<Surface>(ex);
            }
        }
    }
}