using _253504_Klein_Lab4.Entities;
using _253504_Klein_Lab4.Interfaces;

namespace _253504_Klein_Lab4.Services
{
	internal class FoodSerializer : ISerializer<Food>
	{
		public void Serialize(IEnumerable<Food> data, string fileName)
		{
			using var stream = File.OpenWrite(fileName);
			var writer = new BinaryWriter(stream);
			foreach (var obj in data)
			{
				writer.Write(obj.Name!);
				writer.Write(obj.Id);
				writer.Write(obj.IsExpired);
			}
		}

		public IEnumerable<Food> Deserialize(string fileName)
		{
            using var stream = File.OpenRead(fileName);
            var reader = new BinaryReader(stream);
            while (reader.PeekChar() != -1)
			{
				var name = reader.ReadString();
				var id = reader.ReadInt32();
				var isExpired = reader.ReadBoolean();
				yield return new Food()
				{
					Name = name,
					Id = id,
					IsExpired = isExpired
				};
			}
			reader.Close();
			stream.Close();
		}
	}
}