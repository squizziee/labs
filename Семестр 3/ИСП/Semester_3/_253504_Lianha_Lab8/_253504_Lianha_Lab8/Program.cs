
using _253504_Lianha_Lab8.Domain;
using LoremNET;

public class Program
{
    public static async Task Main()
    {
        var service = new StreamService<Patient>();
        service.NotifyActivity += (percentage, what) =>
        {
            Console.Write($"\t\t{what} progress : {percentage}%");
        };
        var progress = new Progress<string>(Console.Write);
        var list = new List<Patient>();
        for (int i = 0; i < 1000; i++)
        {
            list.Add(GenerateAuto());
        }
        var stream = new MemoryStream();
        var t1 = service.WriteToStreamAsync(stream, list, progress);
        await Task.Delay(2000); //Thread.Sleep(2000);
        Console.WriteLine();
        var t2 =service.CopyFromStreamAsync(stream, "output.txt", progress);

        await Task.WhenAll(t1, t2);

        var stats = await service.GetStatisticsAsync("output.txt", 
            (auto) => auto.TreatmentTotal > 2.0);
        Console.WriteLine();
        Console.WriteLine(stats);
    }

    private static Patient GenerateAuto()
    {
        return new Patient() { 
            Id = new Random().Next(0, int.MaxValue), 
            Name = Lorem.Words(1), 
            TreatmentTotal = (double)(new Random().Next(1, 100)) 
        };
    }
}