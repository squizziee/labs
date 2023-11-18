using System.Text;

namespace _253504_Lianha_Lab8.Domain
{
	public class StreamService<T>
	{
		private readonly SemaphoreSlim _semaphore;

		public delegate void EventHandler(int percentage, string what);
		public event EventHandler? NotifyActivity;

		public StreamService()
		{
			_semaphore = new(1);
		}

		private void ReportProgress(IProgress<string> progress, 
			int percentage, string what)
		{
			int chunkCount = percentage / 10;
			if (percentage > 100) percentage = 100;
            NotifyActivity!.Invoke(percentage, what);
            progress.Report($"\r{what} in Thread #{Environment.CurrentManagedThreadId} : [" +
				$"{new string('#', chunkCount)}" +
				$"{new string('-', 10 - chunkCount)}](" +
				$"{percentage}%)");
		}

		public async Task WriteToStreamAsync(Stream stream, 
			IEnumerable<T> data, IProgress<string> progress)
		{
			int delay = 5000 / data.Count();
			int itemsRead = 0;
			foreach (var item in data)
			{
				var str = item!.ToString();
                var bytes = Encoding.UTF8.GetBytes(str!);
				_semaphore.Wait();
				try
				{
					await stream.WriteAsync(bytes, 0, bytes.Length);
					++itemsRead;
				} finally 
				{ 
					_semaphore.Release(); 
				}
				var percentage = ((double)itemsRead / data.Count()) * 100.0;
				ReportProgress(progress, (int)percentage, "Writing");
				Thread.Sleep(delay);
			}
		}

        public async Task CopyFromStreamAsync(Stream stream, 
			string filename, IProgress<string> progress)
		{
			_semaphore.Wait();
            ReportProgress(progress, 0, "Copying");
			Thread.Sleep(200);
            using var file = File.OpenWrite(filename);
            stream.Seek(0, SeekOrigin.Begin);
            await stream.CopyToAsync(file);
            ReportProgress(progress, 100, "Copying");
			_semaphore.Release();
        }

        public async Task<int> GetStatisticsAsync(string fileName, 
			Func<T, bool> filter)
		{
			var text = await File.ReadAllTextAsync(fileName);
			var items = text.Split(';');
			var count = 0;
			foreach (var item in items)
			{
				var fields = item.Split(',');
				try
				{
					var instance = (T?)Activator.CreateInstance(
						typeof(T),
						int.Parse(fields[0]),
						fields[1],
						double.Parse(fields[2]));
                    if (filter(instance!))
                    {
                        ++count;
                    }
                } catch { continue; }
			}
			return count;
		}

    }
}