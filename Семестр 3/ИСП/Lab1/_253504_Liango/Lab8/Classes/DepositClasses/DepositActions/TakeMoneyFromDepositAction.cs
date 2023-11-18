using Lab8.Interfaces;

namespace Lab8.Classes.DepositClasses.DepositActions
{
    public sealed class TakeMoneyFromDepositAction : IDepositAction
    {
        private readonly IDeposit _target;
        private readonly double _sumToTake;

        public TakeMoneyFromDepositAction(IDeposit target, double sumToTake) =>
            (_target, _sumToTake) = (target, sumToTake);

        public void Execute()
        {
            if (_target.GetBalance() < _sumToTake)
            {
                throw new Exception("Not enough money in deposit to take");
            }
            _target.SetBalance(_target.GetBalance() - _sumToTake);
        }
    }
}