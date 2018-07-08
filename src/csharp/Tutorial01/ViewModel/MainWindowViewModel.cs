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

using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Input;

using Tutorial01.Common;
using Tutorial01.Objects;

namespace Tutorial01.ViewModel
{
    public class MainWindowViewModel : BaseViewModel
    {
        #region Variables
        private ObservableCollection<VulkanDevice> _availableDevices;

        public ObservableCollection<VulkanDevice> AvailableDevices
        {
            get => _availableDevices;
            set { _availableDevices = value; OnPropertyChanged(); }
        }

        private VulkanDevice _selectedDevice;

        public VulkanDevice SelectedDevice
        {
            get => _selectedDevice;

            set {
                _selectedDevice = value;
                OnPropertyChanged();
                LaunchBtnEnabled = value != null;

                SelectedDeviceName = $"{value?.Name} ({value?.DeviceType})";
            }
        }

        private string _selectedDeviceName;

        public string SelectedDeviceName
        {
            get => _selectedDeviceName;
            set { _selectedDeviceName = value; OnPropertyChanged(); }
        }

        private bool _launchBtnEnabled;

        public bool LaunchBtnEnabled
        {
            get => _launchBtnEnabled;

            set { _launchBtnEnabled = value; OnPropertyChanged(); }
        }

        public ObservableCollection<string> MessageLog
        {
            get => logger.MessageLog;

            set => OnPropertyChanged();
        }

        private readonly VulkanRenderer _vulkanRenderer;
        #endregion

        #region Main Methods
        public MainWindowViewModel()
        {
            _vulkanRenderer = new VulkanRenderer();
        }

        public void InitializeRenderer()
        {
            var initResult = _vulkanRenderer.Initialize();

            if (initResult.IsNullOrError)
            {
                AddErrorLog(initResult.Error);

                return;
            }

            AddLog("Initialized Successfully");

            AvailableDevices = new ObservableCollection<VulkanDevice>(_vulkanRenderer.Devices);

            if (!AvailableDevices.Any())
            {
                AddLog("No Vulkan devices available, verify your drivers are installed");

                SelectedDeviceName = "No Vulkan Device Found";

                return;
            }

            SelectedDevice = AvailableDevices.FirstOrDefault();

            AddLog($"{AvailableDevices.Count} Vulkan Device(s) found");
        }
        #endregion

        #region Commands
        private ICommand _launchRendererCommand;

        public ICommand LaunchRendererCommand => _launchRendererCommand ?? (_launchRendererCommand = new CommandHandler(LaunchRenderer));

        public void LaunchRenderer()
        {
            _vulkanRenderer.InitializeLogicalDevice(SelectedDevice);
        }
        #endregion
    }
}