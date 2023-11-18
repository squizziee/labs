// See https://aka.ms/new-console-template for more information

using Lab4.Classes;

Bank BSB = Bank.CreateBank("BSB Bank", new Deposit(40000), 0.05, 150); 
Console.WriteLine("Created : {0}", Bank.IsCreated());
Console.WriteLine("Payments before SetDepositSize() : {0}", BSB.CalculateTotalPayments());
BSB.SetDepositSize(5);
Console.WriteLine("Payments after SetDepositSize() : {0}", BSB.CalculateTotalPayments());