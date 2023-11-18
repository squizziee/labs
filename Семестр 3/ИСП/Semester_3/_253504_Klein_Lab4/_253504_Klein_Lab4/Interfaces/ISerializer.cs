namespace _253504_Klein_Lab4.Interfaces
{
    internal interface ISerializer<T>
    {
        void Serialize(IEnumerable<T> data, string fileName);
        IEnumerable<T> Deserialize(string fileName);
    }
}