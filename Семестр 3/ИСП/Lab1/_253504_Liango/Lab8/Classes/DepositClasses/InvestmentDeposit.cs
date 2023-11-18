using Lab8.Interfaces;

namespace Lab8.Classes.DepositClasses
{
    public class InvestmentDeposit : IDeposit
    {
        private double _depositSum;
        private ICurrency _currency;

        public InvestmentDeposit(double depositSum, ICurrency currency) =>
            (_depositSum, _currency) = (depositSum, currency);

        public void ConvertCurrencyTo(ICurrency newCurrency)
        {
            _depositSum = _depositSum / _currency.GetConversionRatioToUSD()
                * newCurrency.GetConversionRatioToUSD();
            _currency = newCurrency;
        }

        public double GetBalance() => _depositSum;

        public void SetBalance(double newBalance) =>
            _depositSum = newBalance;

        public void UpdateDeposit(IDepositAction action) =>
            action.Execute();

        public ICurrency GetCurrency() => _currency;
    }
}
