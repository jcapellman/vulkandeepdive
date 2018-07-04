using System.Windows;

using Tutorial01.ViewModel;

namespace Tutorial01
{
    public partial class MainWindow
    {
        private MainWindowViewModel ViewModel => (MainWindowViewModel) DataContext;

        public MainWindow()
        {
            InitializeComponent();

            Loaded += MainWindow_Loaded;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            var initializeResult = ViewModel.InitializeRenderer();

            if (initializeResult.IsNullOrError)
            {
                MessageBox.Show($"Error Occurred initializing Vulkan: {initializeResult.Error}");
            }
        }
    }
}