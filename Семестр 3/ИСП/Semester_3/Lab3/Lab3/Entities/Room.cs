namespace _253504_Lianha_Lab3.Entities
{
    internal class Room
    {
        public int RoomId { get; }
        public double RoomPricePerDay { get; set; }
        public double AreaInSquareMeters { get; set; }
        public bool IsBooked { get; set; }
        public int TimesBooked { get; set; }
        public RoomCategory category { get; }
        public Room(int _roomId, double _roomPricePerDay, double _areaInSquareMeters)
        {
            RoomId = _roomId;
            RoomPricePerDay = _roomPricePerDay;
            AreaInSquareMeters = _areaInSquareMeters;
            TimesBooked = 0;
            IsBooked = false;
            if (RoomPricePerDay < 75)
            {
                category = RoomCategory.Basic;
            }
            else if (RoomPricePerDay < 150)
            {
                category = RoomCategory.Intermediate;
            }
            else if (RoomPricePerDay < 225)
            {
                category = RoomCategory.Luxury;
            }
            else
            {
                category = RoomCategory.Presidential;
            }
        }

        public override string ToString()
        {
            String booked = IsBooked ? "Booked" : "Vacant";
            return $"Room №{RoomId,-5}Price per day: {RoomPricePerDay,-8}" +
                   $"Area in sq. m.: {AreaInSquareMeters,-8}" +
                   $"Times booked: {TimesBooked,-5}{booked,-8}";
        }
    }

    internal enum RoomCategory
    {
        Basic,
        Intermediate,
        Luxury,
        Presidential
    }
}