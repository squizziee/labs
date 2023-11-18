using _253504_Clein_Lab1.Entities;
using _253504_Lianha_Lab1.Collections;
using _253504_Lianha_Lab1.Interfaces;

namespace _253504_Lianha_Lab1.Entities
{
	internal class OnlineShop : IOnlineShop
	{
        private readonly ICustomCollection<Client> clients =
			new MyCustomCollection<Client>();

		private readonly ICustomCollection<OnlineShopItem> items =
			new MyCustomCollection<OnlineShopItem>();

        private readonly ICustomCollection<OnlineShopItem> soldItems =
            new MyCustomCollection<OnlineShopItem>();

        public delegate void EventHandler(OnlineShopEvent _event);
		public event EventHandler? Notify;

		public OnlineShop() {
			items.Add(new OnlineShopItem(OnlineShopItemCategory.Food, "Burger", 19.99));
            items.Add(new OnlineShopItem(OnlineShopItemCategory.Food, "Carrot", 12.49));
            items.Add(new OnlineShopItem(OnlineShopItemCategory.Clothes, "Pants", 39.99));
            items.Add(new OnlineShopItem(OnlineShopItemCategory.Clothes, "Shirt", 25.49));
            items.Add(new OnlineShopItem(OnlineShopItemCategory.Electronics, "TV", 329.49));
            items.Add(new OnlineShopItem(OnlineShopItemCategory.Electronics, "Microvawe Oven", 59.99));
        }

		private void Log(OnlineShopEventType eventType)
		{
            Notify?.Invoke(new OnlineShopEvent(eventType, DateTime.Now));
        }

		public void AddItem(OnlineShopItem item)
		{
			items.Add(item);
			Log(OnlineShopEventType.NewItemAdded);
		}

		private void RegisterClient(string name)
		{
			var newClient = new Client(name);
			if (clients.Contains(newClient))
			{
				throw new Exception("Client is already registered in the system");
			}
			clients.Add(new Client(name));
			Log(OnlineShopEventType.NewClientRegistered);
        }

        private Client? FindClient(string clientName)
		{
			foreach (var client in clients)
			{
				if (client.Name == clientName)
				{
					return client;
				}
			}
			return null;
		}

		private OnlineShopItem? FindItem(string itemName)
		{
            foreach (var item in items)
            {
                if (item.Name == itemName)
                {
                    return item;
                }
            }
            return null;
        }

		public void AddItemToCart(String clientName, string itemName)
		{
			var client = FindClient(clientName);
			if (client is null)
			{
				RegisterClient(clientName);
				client = FindClient(clientName);
            }
			var item = FindItem(itemName);
			if (item is null)
			{
                throw new Exception("No such item found in shop catalog");
            }
            client!.orderItems.Add(item);
			Log(OnlineShopEventType.ItemAddedToCart);
        }

		public void RemoveItemFromCart(string clientName, string itemName)
		{
            var client = FindClient(clientName);
            if (client is null)
			{
                throw new Exception("No such client registered in the system");
            }
            var item = FindItem(itemName);
			if (item is null)
			{
                throw new Exception("No such item found in shop catalog");
            }
            client.orderItems.Remove(item);
            Log(OnlineShopEventType.ItemRemovedFromCart);
        }

		public IEnumerable<OnlineShopItem> GetOrderedItems(string clientName)
		{
            var client = FindClient(clientName);
            if (client is null)
            {
                throw new Exception("No such client registered in the system");
            }
			foreach (var item in client.orderItems)
			{
				yield return item;
			}
        }

        public OrderInfo AccountClient(string clientName)
        {
			var orderItems = GetOrderedItems(clientName);
			double total = 0;
			foreach(var item in orderItems)
			{
				total += item.PriceInUSD;
				soldItems.Add(item);
			}
			
			return new OrderInfo(orderItems, total, clientName);
        }

        public double GetSoldItemTotalPrice(OnlineShopItemCategory category)
        {
			double sum = 0;
			foreach (var item in soldItems)
			{
				if (item.Category == category)
				{
					sum += item.PriceInUSD;
				}
			}
			return sum;
        }
    }
}