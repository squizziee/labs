namespace _253504_Lianha_Lab3.Entities
{
    internal class Client
    {
        public string name;
        public List<Room> bookedRooms = new();

        public Client(string _name) => name = _name;

        public static bool operator ==(Client c1, Client c2) =>
            c1.name == c2.name;

        public static bool operator !=(Client c1, Client c2) =>
            !(c1 == c2);

        public override bool Equals(object? obj)
        {
            if (obj is null) return false;
            return name == ((Client)obj).name;
        }

        public double GetRoomBookingMoneyTotal() =>
            bookedRooms.Sum(room => room.RoomPricePerDay);

        public override int GetHashCode() =>
            name.GetHashCode();
    }
}