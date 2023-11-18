// See https://aka.ms/new-console-template for more information
using _253504_Lianha_Lab4.Entities;

FileService<Patient> fileService = new();
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
    Patient p1 = new("vanek", 10, true);
    Patient p2 = new("donatello", 69, false);
    Patient p3 = new("amogus", 119, true);
    Patient p4 = new("goshan", 1, false);
    Patient p5 = new("keril mahanko", 77, false);
    Patient p6 = new("hobo", 5, true);
    List<Patient> patients = new()
    {
        p1, p2, p3, p4, p5, p6
    };
    var fileName = "result.file";
    var newFileName = "new_result.file";
    fileService.SaveData(patients, fileName, Patient.ToBinary);
    File.Move(fileName, newFileName);
    var collection = fileService.ReadFile(newFileName, Patient.FromBinary);
    var comparer = new PatientComparer();
    foreach (var patient in collection)
    {
        Console.WriteLine(patient);
    }
    Console.WriteLine();
    collection = collection.OrderBy(p => p, comparer);
    foreach (var patient in collection) {
        Console.WriteLine(patient);
    }
    Console.WriteLine();
    collection = collection.OrderBy(p => p.RoomNumber);
    foreach (var patient in collection)
    {
        Console.WriteLine(patient);
    }
}