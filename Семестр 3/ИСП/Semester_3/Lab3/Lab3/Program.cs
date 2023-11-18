// See https://aka.ms/new-console-template for more information
using _253504_Lianha_Lab3.Entities;

Hotel hotel = new(50);
Printer printer = new(new PrinterParameters("\n"));
Journal logs = new();
hotel.NotifySubscribers += (_event) => { 
    logs.AddEvent(_event);
};
hotel.BookRoom("vanek", 10);
hotel.BookRoom("aboba", 11);
hotel.BookRoom("vanek", 12);
hotel.PrintAllRooms(printer);
Console.WriteLine();
printer.Process(hotel.GetNumberOfRoomsOfEachCategory());
logs.PrintEvents(printer);