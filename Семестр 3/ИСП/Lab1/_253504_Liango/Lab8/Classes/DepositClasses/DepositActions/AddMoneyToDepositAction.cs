using Lab8.Interfaces;

namespace Lab8.Classes.DepositClasses.DepositActions
{
    public sealed class AddMoneyToDepositAction : IDepositAction
    {
        private readonly IDeposit _target;
        private readonly double _sumToAdd;

        public AddMoneyToDepositAction(IDeposit target, double sumToAdd) =>
            (_target, _sumToAdd) = (target, sumToAdd);

        public void Execute() =>
            _target.SetBalance(_target.GetBalance() + _sumToAdd);
    }
}