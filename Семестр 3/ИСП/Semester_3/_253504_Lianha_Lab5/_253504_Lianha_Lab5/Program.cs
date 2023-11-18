using _253504_Lianha_Lab5.Domain;
using SerializerLib;

Automobile bugatti = new(){
	Brand = "Bugatti",
	Model = "Chiron Pur Sport",
	BodyType = AutomobileBodyType.Coupe,
	Engine = new()
	{
		Name = "Monster",
		Power = 1500,
		Torque = 1600,
		Displacement = 7993,
		CylinderCount = 16,
		LayoutType = EngineLayoutType.WEngine
	}
};

Automobile koenigsegg = new()
{
    Brand = "Koenigsegg",
    Model = "Agera RS",
    BodyType = AutomobileBodyType.Coupe,
    Engine = new()
    {
        Name = "Twin Turbo Aluminum",
        Power = 1160,
        Torque = 1000,
        Displacement = 5000,
        CylinderCount = 8,
        LayoutType = EngineLayoutType.VEngine
    }
};

Automobile ferrari = new()
{
    Brand = "Ferrari",
    Model = "FXX K",
    BodyType = AutomobileBodyType.Coupe,
    Engine = new()
    {
        Name = "Naturally aspirated",
        Power = 1036,
        Torque = 900,
        Displacement = 6262,
        CylinderCount = 12,
        LayoutType = EngineLayoutType.VEngine
    }
};

Automobile mercedes = new()
{
    Brand = "Mercedes-Benz",
    Model = "G55 AMG",
    BodyType = AutomobileBodyType.Coupe,
    Engine = new()
    {
        Name = "Supercharged 3 valves per cylinder",
        Power = 507,
        Torque = 700,
        Displacement = 5439,
        CylinderCount = 8,
        LayoutType = EngineLayoutType.VEngine
    }
};

Automobile lamborghini = new()
{
    Brand = "Lamborghini",
    Model = "Sesto Elemento",
    BodyType = AutomobileBodyType.Coupe,
    Engine = new()
    {
        Name = "Odd-firing",
        Power = 562,
        Torque = 540,
        Displacement = 5200,
        CylinderCount = 10,
        LayoutType = EngineLayoutType.VEngine
    }
};

var list = new List<Automobile>() { 
    bugatti,
    koenigsegg,
    ferrari,
    mercedes,
    lamborghini
};

AutomobileSerializer s = new();

s.SerializeJSON(list, "output.json");
s.SerializeXML(list, "output.xml");
s.SerializeByLINQ(list, "linq_output.xml");

var data1 = s.DeSerializeJSON("output.json");
var data2 = s.DeSerializeXML("output.xml");
var data3 = s.DeSerializeByLINQ("linq_output.xml");

foreach (var item in data1)
{
    Console.WriteLine(item);
}
foreach (var item in data2)
{
    Console.WriteLine(item);
}
foreach (var item in data3)
{
    Console.WriteLine(item);
}
bool areSame = true;
for (int i = 0; i < list.Count; i++)
{
    if (list[i].Equals(data1.ElementAt(i)) &&
        list[i].Equals(data2.ElementAt(i)) &&
        list[i].Equals(data3.ElementAt(i)))
    {
        continue;
    }
    areSame = false;
}
Console.WriteLine(areSame);