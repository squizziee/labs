namespace _253504_Lianha_Lab3.Entities
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

        public override string ToString()
        {
            return $"{type.ToString().ToUpper()} : {timestamp}";
        }
    }
}