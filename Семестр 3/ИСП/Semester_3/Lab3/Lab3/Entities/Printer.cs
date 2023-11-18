using System.Collections;

namespace _253504_Lianha_Lab3.Entities
{
	internal class Printer
	{
		private PrinterParameters _params;

		public Printer(PrinterParameters printerParameters) => 
			_params = printerParameters;

		public void Process<T>(IEnumerable<T> _entity)
		{
			bool first = true;
			foreach (var element in _entity)
			{
				if (first)
				{
					Console.Write($"{element}");
					first = false;
				}
				else
				{
					Console.Write($"{_params.separator}{element}");
				}
			}
		}
	}

	internal class PrinterParameters
	{
		public String separator = " ";

		public PrinterParameters(String _separator) => 
			(separator) = (_separator);

		public PrinterParameters() { }
    }
}