using _253504_Lianha_Lab3.Entities;

namespace _253504_Lianha_Lab3.Interfaces
{
    internal interface IHotel
    {
        void BookRoom(String clientName, int roomId);
        void UnbookRoom(String clientName, int roomId);
        void PrintAllRooms(Printer printer);
        void PrintVacantRooms(Printer printer);
        double AccountClient(String clientName);
        int GetMostTrendingRoomId();
    }
}