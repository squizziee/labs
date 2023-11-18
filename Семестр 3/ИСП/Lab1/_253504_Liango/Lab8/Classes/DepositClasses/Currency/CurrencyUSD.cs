using Lab8.Interfaces;

namespace Lab8.Classes.DepositClasses.Currency
{
    public sealed class CurrencyUSD : ICurrency
    {
        private const double CONVERSION_RATIO_TO_USD = 1.0;

        public double GetConversionRatioToUSD() => CONVERSION_RATIO_TO_USD;

        public override string ToString() => "USD";
    }
}
