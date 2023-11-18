namespace SerializerLib.Interfaces
{
    public interface ISerializer<T>
    {
        IEnumerable<T> DeSerializeByLINQ(string fileName);
        IEnumerable<T> DeSerializeXML(string fileName);
        IEnumerable<T> DeSerializeJSON(string fileName);
        void SerializeByLINQ(IEnumerable<T> items, string fileName);
        void SerializeXML(IEnumerable<T> items, string fileName);
        void SerializeJSON(IEnumerable<T> items, string fileName);
    }
}