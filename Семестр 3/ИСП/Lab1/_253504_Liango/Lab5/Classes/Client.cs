namespace Lab5.Classes;

public class Client
{
    public Deposit Deposit { get; set; }
    private readonly string _clientName;
    private readonly int _clientID;
    public Client(string clientName)
    {
        this._clientName = clientName;
        this._clientID = ConstructID(clientName);
    }

    private int ConstructID(string clientName)
    {
        int part1 = 0;
        int part2 = 0;
        for (int i = 0; i < clientName.Length / 2; i++)
        {
            part1 += clientName[i];
        }
        for (int i = clientName.Length / 2; i < clientName.Length; i++)
        {
            part2 += clientName[i];
        }
        part1 <<= (part2 % 853);
        DateTime now = DateTime.Now;
        return Math.Abs(~part1 + 1 + (now.Year << part1) + (now.Month >> part2) + (now.Day << part1) + 
            (now.Hour >> part2) + (now.Minute << part1) - (now.Second >> part2));
    }

    public string GetClientName()
    {
        return _clientName;
    }
    
    public int GetClientID()
    {
        return _clientID;
    }
}