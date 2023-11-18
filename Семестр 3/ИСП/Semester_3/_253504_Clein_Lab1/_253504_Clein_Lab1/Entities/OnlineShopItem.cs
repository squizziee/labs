namespace _253504_Clein_Lab1.Entities
{
    internal class OnlineShopItem
    {
        public OnlineShopItemCategory Category { get; set; }
        public string Name { get; set; }
        public double PriceInUSD { get; set; }
        public OnlineShopItem(OnlineShopItemCategory category, string name, double priceInUSD) 
            => (Category, Name, PriceInUSD) = (category, name, priceInUSD);
    }
}