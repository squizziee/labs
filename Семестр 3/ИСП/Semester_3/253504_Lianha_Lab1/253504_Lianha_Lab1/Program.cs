using _253504_Lianha_Lab1.Collections;
using _253504_Lianha_Lab1.Entities;
using _253504_Lianha_Lab1.Interfaces;

try
{
    var printer = new Printer<String>(new PrinterParameters("\n"));
    Journal journal = new();
    Hotel hotel = new Hotel(40);
    hotel.NotifySubscribers += (_event) =>
    {
        journal.AddEvent(_event);
    };
    hotel.BookRoom("vanek", 5);
    hotel.BookRoom("some dude", 10);
    hotel.BookRoom("vanek", 6);
    Console.WriteLine(hotel.AccountClient("vanek"));
    hotel.UnbookRoom("vanek", 6);
    hotel.PrintAllRooms(printer);
    hotel.BookRoom("vadim uladymtseu", 6);
    Console.WriteLine();
    Console.WriteLine(hotel.GetMostTrendingRoomId());
    journal.PrintEvents(printer);
} catch (Exception e)
{
    Console.WriteLine($"Error: {e.Message}");
}