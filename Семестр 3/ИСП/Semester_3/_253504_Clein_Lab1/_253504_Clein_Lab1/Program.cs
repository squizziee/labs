using _253504_Clein_Lab1.Entities;
using _253504_Lianha_Lab1.Collections;
using _253504_Lianha_Lab1.Entities;
using _253504_Lianha_Lab1.Interfaces;

try
{
    Journal journal = new();
    OnlineShop shop = new();
    shop.Notify += (_event) =>
    {
        if (
        _event.type == OnlineShopEventType.ItemAddedToCart ||
        _event.type == OnlineShopEventType.ItemRemovedFromCart
        )
        {
            Console.WriteLine($"{_event} in Program class");
        }
        else
        {
            journal.AddEvent(_event);
        }
    };
    shop.AddItem(new OnlineShopItem(OnlineShopItemCategory.Electronics, "Kawasaki Ninja 400", 7999.99));
    shop.AddItemToCart("maks", "Kawasaki Ninja 400");
    shop.AddItemToCart("maks", "Burger");
    shop.AddItemToCart("maks", "Burger");
    var cheque = shop.AccountClient("maks");
    Console.WriteLine(cheque);
    Printer.Execute<OnlineShopEvent>(journal);
    Console.WriteLine(shop.GetSoldItemTotalPrice(OnlineShopItemCategory.Electronics));

} catch (Exception e)
{
    Console.WriteLine($"Error: {e.Message}");
}