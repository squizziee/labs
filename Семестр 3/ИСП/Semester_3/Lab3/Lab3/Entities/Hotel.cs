using _253504_Lianha_Lab3.Interfaces;
namespace _253504_Lianha_Lab3.Entities
{
	internal class Hotel : IHotel
	{
		private readonly List<Client> clients = new();
		private readonly Dictionary<int, Room> rooms = new();

		public delegate void EventHandler(HotelEvent _event);
		public event EventHandler? NotifySubscribers;

		public Hotel(int roomCount) {
			Random random = new();
			for (int i = 0; i < roomCount; i++)
			{
				rooms.Add(i, new Room(i, random.Next(250), random.Next(50)));
			}
		}

		private void Log(HotelEventType _event) =>
            NotifySubscribers?.Invoke(new HotelEvent(_event, DateTime.Now));

		private void RegisterClient(string name)
		{
			var newClient = new Client(name);
			if (clients.Contains(newClient))
			{
				throw new Exception("Client is already registered in the system");
			}
			clients.Add(new Client(name));
		}

		private Client? FindClient(string clientName)
		{
			try
			{
				return clients
                    .Where(client => client.name == clientName)
                    .First(); ;
			}  catch(Exception)
			{
				return null;
			}
        }

		public void BookRoom(String clientName, int roomId)
		{
			var client = FindClient(clientName);
			if (client is null)
			{
				RegisterClient(clientName);
				client = FindClient(clientName);
                Log(HotelEventType.NewClientRegistered);
			}
			var room = rooms[roomId];
			if (room is null) {
                throw new Exception("No such room found in the system");
            }
            if (room.IsBooked)
            {
                throw new Exception($"Chosen room №{roomId} is already booked");
            }
            room.IsBooked = true;
            room.TimesBooked++;
            client!.bookedRooms.Add(room);
			Log(HotelEventType.RoomBooked);
		}

		public void UnbookRoom(String clientName, int roomId)
		{
            var client = FindClient(clientName);
            if (client is null)
			{
				throw new Exception("No such client registered in the system");
			}
			var room = rooms[roomId];
			if (room is null)
			{
                throw new Exception("No such room found in the system");
            }
            room.IsBooked = false;
            client.bookedRooms.Remove(room);
            Log(HotelEventType.RoomUnbooked);
		}

		public void PrintAllRooms(Printer printer) =>
			printer.Process<Room>(rooms.Values);

		public void PrintVacantRooms(Printer printer) =>
			printer.Process<Room>(rooms.Values.Where(room => room.IsBooked).ToList());

		public double AccountClient(string clientName)
		{
			var client = FindClient(clientName);
			if (client is null)
			{
				throw new Exception("No such client registered in the system");
			}
			return client.bookedRooms.Sum(room => room.RoomPricePerDay);
		}

		public List<int> GetListOfRoomIdsSortedByPrice() =>
			rooms.Values.OrderBy(room => room.RoomPricePerDay)
						.Select(room => room.RoomId)
						.ToList();

		public double GetTotalRoomBookingMoneySum() =>
			rooms.Values.Where(room => room.IsBooked)
						.Select(room => room.RoomPricePerDay)
						.Sum();

        public int GetMostTrendingRoomId() =>
            rooms.Values.OrderByDescending(room => room.TimesBooked)
                        .First().RoomId;

        public String GetMostValuableClientName() =>
			clients.OrderByDescending(client => client.GetRoomBookingMoneyTotal())
				   .First().name;

		public int GetNumberOfClientsThatPaidMoreThan(double sum) =>
			clients.Aggregate(0, 
				(count, next) => (next.GetRoomBookingMoneyTotal() > sum) ? count + 1 : count);

		public Dictionary<RoomCategory, int> GetNumberOfRoomsOfEachCategory()
		{
			var temp = rooms.Values.GroupBy(room => room.category);
			Dictionary<RoomCategory, int> table = new();
			foreach (var group in temp)
				table.Add(group.Key, group.Count());
			return table;
		}
	}
}