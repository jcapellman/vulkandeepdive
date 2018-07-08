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
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Windows.Input;

using Tutorial01.Common;
using Tutorial01.Objects;

namespace Tutorial01.ViewModel
{
    public class MainWindowViewModel : INotifyPropertyChanged
    {
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

            set { _selectedDevice = value;
                OnPropertyChanged();
                LaunchBtnEnabled = value != null;
            }
        }

        private bool _launchBtnEnabled;

        public bool LaunchBtnEnabled
        {
            get => _launchBtnEnabled;

            set
            {
                _launchBtnEnabled = value;
                OnPropertyChanged();
            }
        }

        private readonly VulkanRenderer _vulkanRenderer;

        public MainWindowViewModel()
        {            
            _vulkanRenderer = new VulkanRenderer();
        }

        public ReturnSet<bool> InitializeRenderer()
        {
            var initResult = _vulkanRenderer.Initialize();

            if (initResult.IsNullOrError)
            {
                return new ReturnSet<bool>(initResult.Error);
            }

            AvailableDevices = new ObservableCollection<VulkanDevice>(_vulkanRenderer.Devices);

            if (!AvailableDevices.Any())
            {
                return new ReturnSet<bool>(false);
            }

            SelectedDevice = AvailableDevices.FirstOrDefault();

            return new ReturnSet<bool>(true);
        }

        private ICommand _launchRendererCommand;

        public ICommand LaunchRendererCommand => _launchRendererCommand ?? (_launchRendererCommand = new CommandHandler(LaunchRenderer));

        public void LaunchRenderer()
        {
            _vulkanRenderer.InitializeLogicalDevice(SelectedDevice);
        }

        #region MVVM Boilerplate code
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
        #endregion
    }
}