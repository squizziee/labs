namespace _253504_Lianha_Lab1.Entities
{
    internal record HotelEvent
    {
        public HotelEventType type;
        public DateTime timestamp;

        public HotelEvent(HotelEventType _type, DateTime _timestamp)
        {
            type = _type;
            timestamp = _timestamp;
        }
    }
}