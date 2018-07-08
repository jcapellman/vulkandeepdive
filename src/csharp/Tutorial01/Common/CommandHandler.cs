using System;
using System.Windows.Input;

namespace Tutorial01.Common
{
    public class CommandHandler : ICommand
    {
        private readonly Action _action;
        
        public CommandHandler(Action action)
        {
            _action = action;
        }
        
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter) => true;

        public void Execute(object parameter)
        {
            _action();
        }
    }
}