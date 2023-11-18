using Lab8.Interfaces;

namespace Lab8.Classes
{
    public class Bank
    {
        private string? _bankName { get; set; }
        private ISet<IClient> _clientList = new HashSet<IClient>();

        public Bank(string bankName) => (_bankName) = (bankName);

        public void AddClient(IClient newClient) => 
            _clientList.Add(newClient);

        public IClient GetClient(IClient client)
        {
            foreach (IClient tmp in _clientList)
            {
                if (client == tmp) return tmp;
            }
            throw new Exception("No such client in bank database");
        }

        public void RemoveClient(IClient client) => 
            _clientList.Remove(client);

        public void PrintClientList()
        {
            foreach (IClient cl in _clientList)
            {
                Console.WriteLine(cl);
            }
        }

        public double GetTotalDepositValue(ICurrency currency)
        {
            double result = 0;
            foreach (var client in _clientList)
            {
                result += client.GetDeposit().GetBalance() / 
                    client.GetDeposit().GetCurrency().GetConversionRatioToUSD() * 
                    currency.GetConversionRatioToUSD();
            }
            return result;
        }
    }
}
