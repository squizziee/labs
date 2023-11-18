using Lab8.Interfaces;
using Lab8.Classes.DepositClasses.DepositActions;

namespace Lab8.Classes.ClientClasses
{
    public class RegularClient : IClient
    {
        private string _name { get; set; }
        private string _address { get; set; }
        private IDeposit _deposit;

        public RegularClient(string name, string address, IDeposit deposit) =>
            (_name, _address, _deposit) = (name, address, deposit); 

        public void AddToDeposit(double sum) =>
            _deposit.UpdateDeposit(new AddMoneyToDepositAction(_deposit, sum));

        public void TakeFromDeposit(double sum) =>
            _deposit.UpdateDeposit(new TakeMoneyFromDepositAction(_deposit, sum));

        public override string ToString() => 
            $"Regular client: {_name}, {_address}, " +
                $"{_deposit.GetBalance()} {_deposit.GetCurrency()}";

        public IDeposit GetDeposit() => _deposit;
    }
}
