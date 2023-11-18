using _253504_Lianha_Lab1.Interfaces;
using System.Collections;

namespace _253504_Lianha_Lab1.Entities
{
    internal class Journal : IEnumerable<OnlineShopEvent>
    {
        private List<OnlineShopEvent> events =
            new();

        public void AddEvent(OnlineShopEvent hotelEvent) => events.Add(hotelEvent);

        public IEnumerator<OnlineShopEvent> GetEnumerator()
        {
            foreach (var _event in events)
            {
                yield return _event;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}