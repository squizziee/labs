namespace Lab8.Interfaces
{
    public interface IDeposit
    {
        void ConvertCurrencyTo(ICurrency newCurrency);

        void UpdateDeposit(IDepositAction action);

        double GetBalance();

        void SetBalance(double newBalance);

        ICurrency GetCurrency();
    }
}
