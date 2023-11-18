namespace Lab5.Classes;

public class Deposit
{
    private double _depositSizeInUSD;
    private readonly Percentage _depositPercentage;
    private List<Client> clients;

    public Deposit(double depositSizeInUSD, Percentage depositPercentage)
    {
        this._depositSizeInUSD = depositSizeInUSD;
        this._depositPercentage = depositPercentage;
    }

    public double GetDepositSizeInUSD()
    {
        return _depositSizeInUSD;
    }

    public void SetDepositSizeInUSD(double depositSizeInUSD)
    {
        this._depositSizeInUSD = depositSizeInUSD;
    }
    
    public Percentage GetDepositPercentage()
    {
        return _depositPercentage;
    }
}