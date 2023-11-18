using _253504_Lianha_Lab1.Collections;
using _253504_Lianha_Lab1.Interfaces;

namespace _253504_Lianha_Lab1.Entities
{
	internal class Hotel : IHotel
	{
        internal class Room
        {
            public int RoomId { get; }
            public double RoomPricePerDay { get; set; }
            public double AreaInSquareMeters { get; set; }
            public bool IsBooked { get; set; }
            public int TimesBooked { get; set; }
            public Room(int _roomId, double _roomPricePerDay, double _areaInSquareMeters)
            {
                RoomId = _roomId;
                RoomPricePerDay = _roomPricePerDay;
                AreaInSquareMeters = _areaInSquareMeters;
                IsBooked = false;
            }

            public override string ToString()
            {
                String booked = IsBooked ? "Booked" : "Vacant";
                return $"Room №{RoomId,-5}Price per day: {RoomPricePerDay,-8}" +
                       $"Area in sq. m.: {AreaInSquareMeters,-8}" +
                       $"Times booked: {TimesBooked,-5}{booked,-8}";
            }
        }

        internal class Client
        {
            public string name;
            public ICustomCollection<Room> bookedRooms =
                new MyCustomCollection<Room>();

            public Client(string _name) => name = _name;

            public static bool operator ==(Client c1, Client c2)
            {
                return c1.name == c2.name;
            }

            public static bool operator !=(Client c1, Client c2)
            {
                return !(c1 == c2);
            }

            public override bool Equals(object? obj)
            {
                if (obj is null) return false;
                return name == ((Client)obj).name;
            }

            public override int GetHashCode()
            {
                return name.GetHashCode();
            }
        }

        private readonly ICustomCollection<Client> clients =
			new MyCustomCollection<Client>();

		private readonly ICustomCollection<Room> rooms =
			new MyCustomCollection<Room>();

		private readonly Journal eventJournal = new();

		public delegate void EventHandler(HotelEvent _event);
		public event EventHandler? NotifySubscribers;

		public Hotel(int roomCount) {
			Random random = new();
			for (int i = 0; i < roomCount; i++)
			{
				rooms.Add(new Room(i, random.Next(250), random.Next(50)));
			}
		}


		private void RegisterClient(string name)
		{
			var newClient = new Client(name);
			if (clients.Contains(newClient))
			{
				throw new Exception("Client is already registered in the system");
			}
			clients.Add(new Client(name));
		}

		public void BookRoom(String clientName, int roomId)
		{
			bool foundClient = false;
			Client chosenClient = new("new_client");
			foreach (Client client in clients)
			{
				if (client.name == clientName)
				{
					foundClient = true;
					chosenClient = client;
				}
			}
			if (!foundClient)
			{
				RegisterClient(clientName);
                NotifySubscribers?.Invoke(new HotelEvent(HotelEventType.NewClientRegistered, DateTime.Now));
            }
			bool foundRoom = false;
			foreach (Room room in rooms)
			{
				if (room.RoomId == roomId)
				{
					if (room.IsBooked)
					{
                        throw new Exception("Chosen room is already booked");
                    }
					foundRoom = true;
					room.IsBooked = true;
					room.TimesBooked++;
					chosenClient.bookedRooms.Add(room);
					NotifySubscribers?.Invoke(new HotelEvent ( HotelEventType.RoomBooked, DateTime.Now ));
					break;
				}
			}
			if (!foundRoom)
			{
                throw new Exception("No such room found in the system");
            }
        }

		public void UnbookRoom(String clientName, int roomId)
		{
			bool foundClient = false;
			Client chosenClient = new("new_client");
			foreach (Client client in clients)
			{
				if (client.name == clientName)
				{
					foundClient = true;
					chosenClient = client;
				}
			}
			if (!foundClient)
			{
                throw new Exception("No such client registered in the system");
            }
			bool foundRoom = false;
			foreach (Room room in rooms)
			{
				if (room.RoomId == roomId)
				{
					foundRoom = true;
					room.IsBooked = false;
					chosenClient.bookedRooms.Remove(room);
                    NotifySubscribers?.Invoke(new HotelEvent(HotelEventType.RoomUnbooked, DateTime.Now));
                    break;
					//throw new Exception("Client already registered in the system");
				}
			}
            if (!foundRoom)
            {
                throw new Exception("No such room found in the system");
            }
        }

        public void PrintAllRooms(Printer<string> printer)
        {
            ICustomCollection<String> temp =
            new MyCustomCollection<String>();
            foreach (Room room in rooms)
			{
				temp.Add(room.ToString());
			}
			printer.Process(temp);
        }

        public void PrintVacantRooms(Printer<string> printer)
        {
            ICustomCollection<String> temp =
            new MyCustomCollection<String>();
            foreach (Room room in rooms)
            {
				if (!room.IsBooked) temp.Add(room.ToString());
            }
            printer.Process(temp);
        }

        public double AccountClient(string clientName)
        {
            bool foundClient = false;
            Client chosenClient = new("new_client");
            foreach (Client client in clients)
            {
                if (client.name == clientName)
                {
                    foundClient = true;
                    chosenClient = client;
                }
            }
			if (!foundClient)
			{
				throw new Exception("No such client registered in the system");
			}
			double sum = 0;
			foreach (Room room in chosenClient.bookedRooms)
			{
				sum += room.RoomPricePerDay;
			}
			return sum;
        }

        public int GetMostTrendingRoomId()
        {
			int biggest = 0;
			Room mostTrendingRoom = new(0, 0, 0);
            foreach (Room room in rooms) { 
				if (room.TimesBooked > biggest)
				{
					mostTrendingRoom = room;
					biggest = room.TimesBooked;
				}
			}
			return mostTrendingRoom.RoomId;
        }
    }
}