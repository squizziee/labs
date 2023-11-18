using _253504_Lianha_Lab1.Collections;
using _253504_Lianha_Lab1.Interfaces;

namespace _253504_Lianha_Lab1.Entities
{
    internal class Journal
    {
        private ICustomCollection<HotelEvent> events =
            new MyCustomCollection<HotelEvent>();

        public void AddEvent(HotelEvent hotelEvent) => events.Add(hotelEvent);

        public void PrintEvents(Printer<String> printer)
        {
            ICustomCollection<String> temp =
                new MyCustomCollection<String>();
            foreach (HotelEvent hotelEvent in events)
            {
                temp.Add(hotelEvent.ToString());
            }
            printer.Process(temp);
        }
    }
}