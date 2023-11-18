using _253504_Lianha_Lab3.Interfaces;

namespace _253504_Lianha_Lab3.Entities
{
	internal class Journal
	{
		private List<HotelEvent> events = new();

		public void AddEvent(HotelEvent hotelEvent) => 
			events.Add(hotelEvent);

		public void PrintEvents(Printer printer) => 
			printer.Process<HotelEvent>(events);
	}
}