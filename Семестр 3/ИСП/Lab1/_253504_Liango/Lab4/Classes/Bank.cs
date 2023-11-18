namespace Lab4.Classes;

public class Bank
{
    private readonly string _bankName;
    private readonly Deposit _deposit;
    private readonly double _depositPercentage;
    private readonly int _depositQuantity;

    private static Bank? _bankInstance;
    
    
    private static bool _created = false;
    
    private Bank(string bankName, Deposit deposit, double depositPercentage, int depositQuantity)
    {
        this._bankName = bankName;
        this._deposit = deposit;
        this._depositPercentage = depositPercentage;
        this._depositQuantity = depositQuantity;
    }

    public static Bank CreateBank(string bankName, Deposit deposit, double depositPercentage,
        int depositQuantity)
    {
        return _bankInstance ??= new Bank(bankName, deposit, depositPercentage, depositQuantity);
    }
    
    public static Bank CreateBank(string bankName, Deposit deposit, double depositPercentage)
    {
        if (_created) throw new Exception("Error: instance already created");
        _created = true;
        return new Bank(bankName, deposit, depositPercentage, 1);
    }

    public double CalculateTotalPayments()
    {
        return _deposit.GetDepositSizeInUSD() * _depositPercentage * _depositQuantity;
    }

    public string GetBankName()
    {
        return _bankName;
    }
    
    public void SetDepositSize(double newSize)
    {
        this._deposit.SetDepositSizeInUSD(newSize);
    }

    public Deposit GetDeposit()
    {
        return _deposit;
    }

    public double GetDepositPercentage()
    {
        return _depositPercentage;
    }

    public int GetDepositQuantity()
    {
        return _depositQuantity;
    }

    public static bool IsCreated()
    {
        return _created;
    }
}