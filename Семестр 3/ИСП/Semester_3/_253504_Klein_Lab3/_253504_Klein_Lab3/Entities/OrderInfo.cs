namespace _253504_Clein_Lab1.Entities
{
    internal class OrderInfo
    {
        public IEnumerable<OnlineShopItem> Items { get; set; }
        public double Total { get; set; }
        public string ClientName { get; set; }

        public OrderInfo(IEnumerable<OnlineShopItem> items, double total, string clientName) 
            => (Items, Total, ClientName) = (items, total, clientName);

        public override string ToString()
        {
            string listOfItems = "";
            var first = true;
            foreach (var item in Items)
            {
                if (first) {
                    listOfItems += item.Name;
                    first = false;
                }
                listOfItems += ", " + item.Name;
            }
            return $"{ClientName}`s items : {listOfItems}, Total : ${Total:0.##}";
        }
    }
}