using _253504_Clein_Lab1.Entities;
using _253504_Lianha_Lab1.Entities;

namespace _253504_Lianha_Lab1.Interfaces
{
    internal interface IOnlineShop
    {
        void AddItem(OnlineShopItem item);
        void AddItemToCart(string clientName, string itemName);
        void RemoveItemFromCart(string clientName, string itemName);
        IEnumerable<OnlineShopItem> GetOrderedItems(string clientName);
        OrderInfo AccountClient(string clientName);
        double GetSoldItemTotalPrice(OnlineShopItemCategory category);
    }
}