using _253504_Lianha_Lab5.Domain;
using SerializerLib.Interfaces;
using System.Text.Json;
using System.Xml.Linq;
using System.Xml.Serialization;

namespace SerializerLib
{
	public class AutomobileSerializer : ISerializer<Automobile>
	{
		public void SerializeJSON(IEnumerable<Automobile> items, string fileName)
		{
			var text = JsonSerializer.Serialize(items);
			File.WriteAllText(fileName, text);
		}

		public IEnumerable<Automobile> DeSerializeJSON(string fileName)
		{
			using var stream = File.OpenRead(fileName);
			return JsonSerializer.Deserialize<IEnumerable<Automobile>>(stream)!;
		}

		public void SerializeByLINQ(IEnumerable<Automobile> items, string fileName)
		{

			var doc = new XDocument(new XElement("AutomobileList", 
				from item in items
				select new XElement("Automobile", 
					new XElement("Engine", 
						new XAttribute("Name", item.Engine!.Name!),
                        new XAttribute("Power", item.Engine!.Power),
						new XAttribute("Torque", item.Engine!.Torque),
                        new XAttribute("Displacement", item.Engine!.Displacement),
                        new XAttribute("CylinderCount", item.Engine!.CylinderCount),
                        new XAttribute("LayoutType", ((int)item.Engine!.LayoutType))
                    ),
					new XElement("Brand", item.Brand!),
                    new XElement("Model", item.Model!),
                    new XElement("BodyType", ((int)item.BodyType))
                )));
			doc.Save(fileName);
		}
		#pragma warning disable CS8604
        public IEnumerable<Automobile> DeSerializeByLINQ(string fileName)
		{
			var doc = XDocument.Load(fileName);
			var list = doc.Element("AutomobileList");
			foreach (var automobile in list!.Elements("Automobile")) {
				var engineXML = automobile.Element("Engine");
                var name = (string?) engineXML!.Attribute("Name");
				var power = (double) engineXML!.Attribute("Power");
				var torque = (double) engineXML!.Attribute("Torque");
                var displacement = (double) engineXML!.Attribute("Displacement");
                var cylinderCount = (int) engineXML!.Attribute("CylinderCount");
				var layoutType = (EngineLayoutType)(int) engineXML!.Attribute("LayoutType");
				var engine = new Engine()
				{
					Name = name,
					Power = power,
					Torque = torque,
					Displacement = displacement,
					CylinderCount = cylinderCount,
					LayoutType = layoutType
				};
				var brand = (string?) automobile.Element("Brand");
				var model = (string?)automobile.Element("Model");
                var bodyType = (AutomobileBodyType)(int)automobile.Element("BodyType");
				yield return new Automobile() { 
					Engine = engine, 
					Brand = brand, 
					Model = model, 
					BodyType = bodyType 
				};
            }
		}
		#pragma warning restore CS8604

        public void SerializeXML(IEnumerable<Automobile> items, string fileName)
		{
			var serializer = new XmlSerializer(typeof(List<Automobile>));
			using var stream = File.OpenWrite(fileName);
			serializer.Serialize(stream, items.ToList());
		}
		public IEnumerable<Automobile> DeSerializeXML(string fileName)
		{
            var serializer = new XmlSerializer(typeof(List<Automobile>));
            using var stream = File.OpenRead(fileName);
            var list = (List<Automobile>?)serializer.Deserialize(stream);
			return list!;
        }
    }

    public class XMLItemList<T>
	{
		public List<T> Items { get; set; }

		public XMLItemList(IEnumerable<T> items) {
			Items = new List<T>();
			foreach (var item in items)
			{
				Items.Add(item);
			}
		}

        public XMLItemList()
        {
            Items = new List<T>();
        }
    }
}