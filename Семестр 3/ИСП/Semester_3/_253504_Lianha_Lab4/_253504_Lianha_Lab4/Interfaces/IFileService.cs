namespace _253504_Lianha_Lab4.Interfaces
{
    internal interface IFileService<T>
    {
        IEnumerable<T> ReadFile(string fileName,
            Func<BinaryReader, T> fromBinary);
        void SaveData(IEnumerable<T> data, string fileName,
            Func<BinaryWriter, T, int> toBinary);
    }
}