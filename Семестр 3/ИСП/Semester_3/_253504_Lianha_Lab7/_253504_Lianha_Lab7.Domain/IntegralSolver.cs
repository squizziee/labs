using System.Diagnostics;
using System.Threading;

namespace _253504_Lianha_Lab7.Domain
{
	public class IntegralSolver
	{
		private const double _start = 0;
		private const double _end = 1;
		private const double _step = 0.00000001;
		private static SemaphoreSlim? _semaphore;

		public delegate void ProgressHandler(double step);
		public delegate void CompletionHandler(SolutionData result);

		public event ProgressHandler? NotifyProgressListeners;
		public event CompletionHandler? NotifyCompletionListeners;

		public IntegralSolver(int _maxThreadCount) {
			_semaphore = new(_maxThreadCount);
		}

		public void AlertProgress(double step)
		{
			NotifyProgressListeners?.Invoke(step);
		}

		public void AlertCompletion(SolutionData result)
		{
			NotifyCompletionListeners?.Invoke(result);
		}

		public void Solve()
		{
			_semaphore!.Wait();
			var timer = new Stopwatch();
			double sum = 0;
			var intervalIterations = (int)((_end - _start) / _step / 1000);
			var counter = 0;
			timer.Start();
			for (double i = _start; i < _end; i += _step)
			{
				sum += Math.Sin(i) * _step;
				counter++;
				if (counter == intervalIterations)
				{
					AlertProgress(_step * intervalIterations);
						counter = 0;
				}
			}
			timer.Stop();
			AlertCompletion(new()
			{
				ThreadId = Thread.CurrentThread.ManagedThreadId,
                Result = sum,
                ElapsedMillis = timer.ElapsedMilliseconds
            });
			_semaphore.Release();
		}
	}

	public record SolutionData
	{
		public int ThreadId { get; set; }
		public double Result { get; set; }
		public double ElapsedMillis { get; set; }

		public override string ToString()
		{
			return $"Thread Id : {ThreadId}, Result : {Result}, time elapsed : {ElapsedMillis}ms";
		}
	}
}