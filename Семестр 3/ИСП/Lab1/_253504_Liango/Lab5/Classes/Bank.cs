namespace Lab5.Classes;

public class Bank
{
    private string _bankName;
    private readonly Dictionary<Client, Deposit> _clientList;

    public Bank(string bankName)
    {
        this._bankName = bankName;
        this._clientList = new Dictionary<Client, Deposit>();
    }

    public void AddClient(Client client, Deposit deposit)
    {
        _clientList.Add(client, deposit);
    }

    public void UpdateDepositSizes()
    {
        foreach (var pair in _clientList)
        {
            var client = pair.Key;
            var deposit = pair.Value;
            pair.Value.SetDepositSizeInUSD(deposit.GetDepositSizeInUSD() * 
                                           (1.0 + (int)(deposit.GetDepositPercentage()) / 100.0));
        }
    }

    public double CalculatePayments()
    {
        double sum = 0;
        foreach (var pair in _clientList)
        {
            double percentage = (int)(pair.Value.GetDepositPercentage()) / 100.0;
            sum += percentage * pair.Value.GetDepositSizeInUSD();
        }
        return sum;
    }
    
    public void AddToDeposit(int clientID, double sum)
    {
        foreach (var pair in _clientList)
        {
            if (pair.Key.GetClientID() == clientID)
            {
                pair.Value.SetDepositSizeInUSD(pair.Value.GetDepositSizeInUSD() + sum);
            }
        }
    }
}