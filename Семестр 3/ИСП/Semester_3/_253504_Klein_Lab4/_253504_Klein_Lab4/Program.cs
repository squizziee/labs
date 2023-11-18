// See https://aka.ms/new-console-template for more information
using _253504_Klein_Lab4.Entities;
using _253504_Klein_Lab4.Services;

FileService<Food> fileService = new() {
    Serializer = new FoodSerializer() 
};
// 1
/*{
    var directory = Directory.GetCurrentDirectory() + "/output/";
    Directory.CreateDirectory(directory);
    fileService.CreateFilesWithRandomNames(directory, 10);
    foreach (var file in Directory
        .GetFiles(directory)
        .Select(file => Path.GetFileName(file)))
    {
        var parts = file.Split(".");
        Console.WriteLine($"File {parts[0]} has .{parts[^1]} extension");
    }
}*/
// 2
{
    Food f1 = new()
    {
        Name = "a",
        Id = 6,
        IsExpired = false,
    };
    Food f2 = new()
    {
        Name = "b",
        Id = 5,
        IsExpired = true,
    };
    Food f3 = new()
    {
        Name = "c",
        Id = 4,
        IsExpired = false,
    };
    Food f4 = new()
    {
        Name = "d",
        Id = 3,
        IsExpired = true,
    };
    Food f5 = new()
    {
        Name = "e",
        Id = 2,
        IsExpired = false,
    };
    Food f6 = new()
    {
        Name = "f",
        Id = 1,
        IsExpired = true,
    };
    List<Food> patients = new()
    {
       f1, f2, f3, f4, f5, f6
    };
    var fileName = "result.file";
    var newFileName = "new_result.file";
    fileService.SaveData(patients, fileName);
    File.Move(fileName, newFileName);
    var collection = fileService.ReadFile(newFileName);
    foreach (var food in collection)
    {
        Console.WriteLine(food);
    }
    Console.WriteLine();
    var comparer = new FoodComparer();
    foreach (var food in collection.OrderBy(p => p, comparer)) {
        Console.WriteLine(food);
    }
    Console.WriteLine();
    foreach (var food in collection.OrderBy(p => p.Id))
    {
        Console.WriteLine(food);
    }
}