using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;

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

            return new ReturnSet<bool>(true);
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