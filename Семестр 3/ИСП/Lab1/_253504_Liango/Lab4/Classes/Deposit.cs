namespace Lab4.Classes;

public class Deposit
{
    private double _depositSizeInUSD;

    public Deposit(double depositSizeInUSD)
    {
        this._depositSizeInUSD = depositSizeInUSD;
    }

    public double GetDepositSizeInUSD()
    {
        return _depositSizeInUSD;
    }

    public void SetDepositSizeInUSD(double depositSizeInUSD)
    {
        this._depositSizeInUSD = depositSizeInUSD;
    }
}