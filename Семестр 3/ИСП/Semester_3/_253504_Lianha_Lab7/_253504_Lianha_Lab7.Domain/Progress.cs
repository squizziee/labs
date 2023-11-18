namespace _253504_Lianha_Lab7.Domain
{
	public class Progress
	{
		private bool init = true;
		private double goal;
		private double progress;
		public int Delay { get; set; }
		public Progress(double _goal)
		{
			goal = _goal;
			progress = 0;
		}
		public void Update(double step)
		{
			progress += step;
			Thread.Sleep(Delay);
			double percentage = (progress / goal) * 100;
			int chunkCount = (int)(percentage / 10);
			Console.Write($"\rThreadID: {Environment.CurrentManagedThreadId}, Progress: [" +
				$"{new string('#', chunkCount)}" +
				$"{new string('-', 10 - chunkCount)}]({(percentage > 100 ? 100 : percentage):##}%)");
		}
	}
}