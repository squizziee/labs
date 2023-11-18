using _253504_Lianha_Lab6.Entities;
using _253504_Lianha_Lab6.Interfaces;
using System.Reflection;
using static System.Net.Mime.MediaTypeNames;

var employees = new Employee[]
{
    new() { Id = 1, Name = "Egorik", IsWorkingFullTime = true },
    new() { Id = 2, Name = "Donatello", IsWorkingFullTime = false },
    new() { Id = 3, Name = "Vanek", IsWorkingFullTime = false },
    new() { Id = 4, Name = "Slavucci", IsWorkingFullTime = true },
    new() { Id = 5, Name = "Maksos", IsWorkingFullTime = false },
    new() { Id = 6, Name = "Vadim", IsWorkingFullTime = true },
};

var serializer = MyFileServiceLoader<Employee>.Load("FileServiceLib.dll");
serializer.SaveData(employees, "output.json");
var data = serializer.ReadFile("output.json");
foreach (var employee in data)
{
    Console.WriteLine(employee);
}