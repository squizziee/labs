using _253504_Clein_Lab1.Entities;
using _253504_Lianha_Lab1.Interfaces;

namespace _253504_Lianha_Lab1.Entities
{
	internal class OnlineShop : IOnlineShop
	{
		private readonly List<Client> clients =
			new();

		private readonly Dictionary<string, OnlineShopItem> items =
			new();

		private readonly List<OnlineShopItem> soldItems =
			new();

		public delegate void EventHandler(OnlineShopEvent _event);
		public event EventHandler? Notify;

		public OnlineShop() {
			items.Add("Burger", 
				new OnlineShopItem(OnlineShopItemCategory.Food, "Burger", 19.99));
			items.Add("Carrot",
				new OnlineShopItem(OnlineShopItemCategory.Food, "Carrot", 12.49));
			items.Add("Pants", 
				new OnlineShopItem(OnlineShopItemCategory.Clothes, "Pants", 39.99));
			items.Add("Shirt", 
				new OnlineShopItem(OnlineShopItemCategory.Clothes, "Shirt", 25.49));
			items.Add("TV", 
				new OnlineShopItem(OnlineShopItemCategory.Electronics, "TV", 329.49));
			items.Add("Microvawe Oven", 
				new OnlineShopItem(OnlineShopItemCategory.Electronics, "Microvawe Oven", 59.99));
		}

		private void Log(OnlineShopEventType eventType)
			=> Notify?.Invoke(new OnlineShopEvent(eventType, DateTime.Now));

		public void AddItem(OnlineShopItem item)
		{
			items.Add(item.Name, item);
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

		public void AddItemToCart(String clientName, string itemName)
		{
			var client = FindClient(clientName);
			if (client is null)
			{
				RegisterClient(clientName);
				client = FindClient(clientName);
			}
			var item = items[itemName];
			if (item is null)
			{
				throw new Exception("No such item found in shop catalog");
			}
			client!.orderItems.Add(item);
			client.Total += item.PriceInUSD;
			Log(OnlineShopEventType.ItemAddedToCart);
		}

		public void RemoveItemFromCart(string clientName, string itemName)
		{
			var client = FindClient(clientName);
			if (client is null)
			{
				throw new Exception("No client with that name is present");
			}
			var item = items[itemName];
			if (item is null)
			{
				throw new Exception("No such item found in shop catalog");
			}
			client.orderItems.Remove(item);
			client.Total -= item.PriceInUSD;
			Log(OnlineShopEventType.ItemRemovedFromCart);
		}

		public IEnumerable<OnlineShopItem> GetOrderedItems(string clientName)
		{
			var client = FindClient(clientName);
			if (client is null)
			{
				throw new Exception("No client with that name is present");
			}
			foreach (var item in client.orderItems)
			{
				yield return item;
			}
		}

		public OrderInfo AccountClient(string clientName)
		{
			var client = FindClient(clientName);
			var orderItems = GetOrderedItems(clientName);
			double total = orderItems.Sum(item => item.PriceInUSD);
			foreach(var item in orderItems) soldItems.Add(item);
			client!.orderItems.Clear();
			return new OrderInfo(orderItems, total, clientName);
		}

		public double GetSoldItemTotalPrice(OnlineShopItemCategory category)
			=> soldItems
			.Where(item => item.Category == category)
			.Sum(item => item.PriceInUSD);

		public IEnumerable<string> GetSortedItemNameList()
			=> items
			.OrderBy(pair => pair.Value.PriceInUSD)
			.Select(pair => pair.Key);

		public double GetSoldItemTotalPrice()
			=> soldItems
			.Sum(item => item.PriceInUSD);

		public string GetMostValuableClientName()
			=> clients
			.OrderByDescending(client => client.Total)
			.First().Name;

		public int GetClientCount(double totalLowBound)
			=> clients
			.Aggregate(0, (count, next) 
				=> (next.Total > totalLowBound) ? count + 1 : count);

        public Dictionary<string, double> GetTotalOfEachSoldItem()
        {
            var temp = soldItems.GroupBy(item => item.Name);
            Dictionary<string, double> table = new();
            foreach (var group in temp)
                table.Add(group.Key, group.Sum(item => item.PriceInUSD));
            return table;
        }
    }
}