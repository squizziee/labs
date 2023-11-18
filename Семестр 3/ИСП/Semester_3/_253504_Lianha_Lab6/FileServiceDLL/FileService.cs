using _253504_Lianha_Lab6.Interfaces;
using _253504_Lianha_Lab6.Entities;
using System.Text.Json;

namespace FileServiceLib
{
    public class FileService<T> : IFileService<T>
    {
        public IEnumerable<T> ReadFile(string fileName)
        {
            using var stream = File.OpenRead(fileName);
            return JsonSerializer.Deserialize<IEnumerable<T>>(stream)!;
        }

        public void SaveData(IEnumerable<T> data, string fileName)
        {
            var text = JsonSerializer.Serialize(data);
            File.WriteAllText(fileName, text);
        }
    }

    public class FileBullshit<M>
    {
        void a()
        {
            var smth = new FileService<Employee>();
        }
    }
}