// See https://aka.ms/new-console-template for more information

using Lab6.Classes;
using Lab6.Classes.Vegetables;
using Lab6.Classes.Fruits;

Console.WriteLine("Hello, World!");

Product a = new Apple(4.5, new DateTime(2020, 12, 12), 
    new DateTime(2020, 12, 24));
Fruit b = new Mango(100.5, new DateTime(2025, 1, 1), 
    new DateTime(2025, 10, 9));
a.Consume();
a.Sell();
Console.WriteLine(b);
b.Consume();

Product c = new Tomato(10, new DateTime(2020, 12, 12), 
    new DateTime(2020, 12, 24)); 
Console.WriteLine(c.IsExpired());

Vegetable d = new Cucumber(double.MaxValue, new DateTime(1979, 10, 10), 
    new DateTime(2069, 12, 24));
    Console.WriteLine(d.TasteVegetable());