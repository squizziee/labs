// See https://aka.ms/new-console-template for more information
using PolynomialClass;

Console.WriteLine("Hello, World!");
Polynomial p = new(1, 2, 3);
Console.WriteLine(p);
if (p)
{
    Console.WriteLine("Casted to bool");
}

if ((int)p == 1)
{
    Console.WriteLine("Casted to int");
}
Console.WriteLine(p.Equals("a"));