using System.Collections;

namespace _253504_Lianha_Lab1.Entities
{
	abstract internal class Printer
	{
		public static void Execute<T>(IEnumerable<T> list)
		{
			bool first = true;
			foreach (T element in list)
			{
				if (first)
				{
					Console.Write($"{element}");
					first = false;
				}
				else
				{
					Console.Write($"\n{element}");
				}
			}
		}
	}
}