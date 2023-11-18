namespace _253504_Lianha_Lab1.Entities
{
    internal record OnlineShopEvent
    {
        public OnlineShopEventType type;
        public DateTime timestamp;

        public OnlineShopEvent(OnlineShopEventType _type, DateTime _timestamp)
        {
            type = _type;
            timestamp = _timestamp;
        }
    }
}