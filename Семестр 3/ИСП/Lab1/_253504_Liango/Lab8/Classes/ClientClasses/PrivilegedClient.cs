using Lab8.Interfaces;
using Lab8.Classes.DepositClasses.DepositActions;
using Lab8.Classes.DepositClasses.Currency;

namespace Lab8.Classes.ClientClasses
{
    public class PrivilegedClient : IClient
    {
        private string _name { get; set; }
        private string _address { get; set; }
        private IDeposit _deposit;
        private double _additionalMarginInUSD = 400;

        public PrivilegedClient(string name, string address, IDeposit deposit)
        {
            _name = name;
            _address = address;
            _deposit = deposit;
            if (_deposit.GetCurrency() is not CurrencyUSD)
            {
                _deposit.UpdateDeposit(
                    new AddMoneyToDepositAction(_deposit, _additionalMarginInUSD / 
                    (new CurrencyUSD()).GetConversionRatioToUSD() * _deposit.GetCurrency().GetConversionRatioToUSD()));
            } 
            else
            {
                _deposit.UpdateDeposit(
                    new AddMoneyToDepositAction(_deposit, _additionalMarginInUSD));
            }         
        }

        public void AddToDeposit(double sum) => 
            _deposit.UpdateDeposit(new AddMoneyToDepositAction(_deposit, sum));

        public void TakeFromDeposit(double sum) => 
            _deposit.UpdateDeposit(new TakeMoneyFromDepositAction(_deposit, sum));

        public override string ToString() =>
            $"Privileged client: {_name}, {_address}, " +
                $"{_deposit.GetBalance()} {_deposit.GetCurrency()}";

        public IDeposit GetDeposit() => _deposit;
    }
}