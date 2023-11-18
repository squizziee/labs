// See https://aka.ms/new-console-template for more information
using Lab5.Classes;

Bank bank = new Bank("Aboba Industries");
Client a = new Client("Nikita Kalabin");
Client b = new Client("Gosha Kazakevich");
Client c = new Client("Vadim Vladymtsev");
bank.AddClient(a, new Deposit(10000, Percentage.High));
bank.AddClient(b, new Deposit(500, Percentage.ExtraHigh));
bank.AddClient(c, new Deposit(3, Percentage.Low));

Console.WriteLine("Client A: {0},\nClient B: {1},\nClient C: {2}", 
    a.GetClientID(), b.GetClientID(), c.GetClientID());

Console.WriteLine("Total payments this year: {0}", bank.CalculatePayments());

bank.UpdateDepositSizes();

Console.WriteLine("Total payments next year: {0}", bank.CalculatePayments());

bank.AddToDeposit(a.GetClientID(), 100000);

Console.WriteLine("Total payments next year: {0}", bank.CalculatePayments());