// See https://aka.ms/new-console-template for more information

using Lab3.Services;

Console.WriteLine("Result: {0}", Square.Calc(2) + Square.Calc(3) + Square.Calc(4));
Console.WriteLine("Result: {0}", Expression.Calc(4));
Console.WriteLine("Result: {0}", DateService.GetWeekDay("21.02.2023"));
Console.WriteLine($"Result: {DateService.DaysTill(21, 02, 2020)}");
