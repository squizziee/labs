using _253504_Lianha_Lab1.Entities;

namespace _253504_Lianha_Lab1.Interfaces
{
    internal interface IHotel
    {
        void BookRoom(String clientName, int roomId);
        void UnbookRoom(String clientName, int roomId);
        void PrintAllRooms(Printer<String> printer);
        void PrintVacantRooms(Printer<String> printer);
        double AccountClient(String clientName);
        int GetMostTrendingRoomId();
    }
}