using _253504_Lianha_Lab4.Interfaces;
using System.Xml.Linq;

namespace _253504_Lianha_Lab4.Entities
{
	internal class FileService<T> : IFileService<T>
	{
		private static readonly List<string> extensions 
			= new() {"txt", "rtf", "dat", "inf"};

		public IEnumerable<T> ReadFile(string fileName, 
			Func<BinaryReader, T> fromBinary)
		{
			using var stream = File.OpenRead(fileName);
            var reader = new BinaryReader(stream);
            while (reader.PeekChar() != -1)
            {
                yield return fromBinary(reader);
            }
		}

		public void SaveData(IEnumerable<T> data, string fileName,
			Func<BinaryWriter, T, int> toBinary)
		{
			var file = new FileInfo(fileName);
			if (file.Exists)
			{
				file.Delete();
			}
			file.Create().Close();
			using var stream = File.OpenWrite(fileName);
            var writer = new BinaryWriter(stream);
            foreach (var element in data)
            {
				try
				{
					toBinary(writer, element);
				} catch (Exception)
				{
					continue;
				}
            }
		}

		public void CreateFilesWithRandomNames(string path, int count)
		{
			for(int i = 0; i < count; i++)
			{
                string fileName = $"{Path.GetRandomFileName()}.{extensions[new Random().Next(extensions.Count)]}";
                File.Create(path + fileName).Close();
            }
		}
	}
}
