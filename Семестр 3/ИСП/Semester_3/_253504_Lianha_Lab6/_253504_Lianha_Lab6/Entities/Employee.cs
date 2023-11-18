namespace _253504_Lianha_Lab6.Entities
{
	public class Employee
	{
		public int Id { get; set; }
		public string? Name { get; set; }
		public bool IsWorkingFullTime { get; set; }

		public Employee() {
			Name = "";
			IsWorkingFullTime = false;
			Id = -1;
		}

		public override string ToString()
		{
			return $"@{Id} : {Name}, working " +
				   $"{(IsWorkingFullTime ? "full" : "part")} time";
		}
	}
}