using Lab8.Classes;
using Lab8.Classes.ClientClasses;
using Lab8.Classes.DepositClasses;
using Lab8.Classes.DepositClasses.Currency;
using Lab8.Interfaces;

Bank b = new("Batman bank");

IDeposit deposit = new InvestmentDeposit(1000, new CurrencyUSD());
IClient client = new RegularClient("Bob", "Himalayas", deposit);

IDeposit deposit2 = new InvestmentDeposit(1000, new CurrencyUSD());
IClient client2 = new PrivilegedClient("Goshanchik", "uruchie", deposit2);
b.AddClient(client);
b.AddClient(client2);
b.PrintClientList();
b.GetClient(client).TakeFromDeposit(100);
b.PrintClientList();
Console.WriteLine(b.GetTotalDepositValue(new CurrencyUSD()));