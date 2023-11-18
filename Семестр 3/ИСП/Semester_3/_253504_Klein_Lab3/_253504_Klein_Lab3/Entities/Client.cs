using _253504_Lianha_Lab1.Interfaces;

namespace _253504_Clein_Lab1.Entities
{
    internal class Client
    {
        public string Name { get; set; }
        public double Total { get; set; }
        public List<OnlineShopItem> orderItems =
            new();

        public Client(string _name) => Name = _name;

        public static bool operator ==(Client c1, Client c2)
        {
            return c1.Name == c2.Name;
        }

        public static bool operator !=(Client c1, Client c2)
        {
            return !(c1 == c2);
        }

        public override bool Equals(object? obj)
        {
            if (obj is null) return false;
            return Name == ((Client)obj).Name;
        }

        public override int GetHashCode()
        {
            return Name.GetHashCode();
        }
    }

}