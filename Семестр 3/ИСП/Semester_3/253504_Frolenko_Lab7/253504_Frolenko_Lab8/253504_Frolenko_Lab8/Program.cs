using Library;
using LoremNET;

public class Program
{
	static async Task Main()
	{
		var streamService = new StreamService<Artwork>();
		var progress = new Progress<string>(Console.WriteLine);

		List<Artwork> artworks = new List<Artwork>();

		Random random = new Random();

		for (int i = 0; i < 1000; i++)
		{
			string title = LoremNET.Lorem.Words(1);

			Artwork artwork = new Artwork(i, title);

			artworks.Add(artwork);
		}

		using (MemoryStream memoryStream = new MemoryStream())
		{
			ManualResetEvent writeCompletedEvent = new ManualResetEvent(false);

			Thread thread1 = new Thread(() =>
			{
				Console.WriteLine($"Поток 1 запущен.Номер потока: {Thread.CurrentThread.ManagedThreadId}");
				streamService.WriteToStream(memoryStream, artworks, progress);
				writeCompletedEvent.Set();
			});

			Thread thread2 = new Thread(() =>
			{
				Console.WriteLine($"Поток 2 запущен. Номер потока: {Thread.CurrentThread.ManagedThreadId}");
				writeCompletedEvent.WaitOne();
				memoryStream.Position = 0;
				streamService.CopyFromStream(memoryStream, "output.txt", progress);
			});
			thread1.Start();
			thread2.Start();
			thread1.Join();
			thread2.Join();
			int statistics = await streamService.GetStatisticsAsync("output.txt", artwork => artwork.Id > 500);
			Console.WriteLine($"Статистика: {statistics} артов с Id выше 500.");
		}
		Console.WriteLine("Оба потока завершили выполнение.");
		Console.ReadKey();
	}
}