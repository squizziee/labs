namespace _253504_Lianha_Lab5.Domain
{
	public class Automobile : IEquatable<Automobile>
	{
		public Engine? Engine { get; set; }
		public string? Brand { get; set; }
		public string? Model { get; set; }
		public AutomobileBodyType BodyType { get; set; }

        public bool Equals(Automobile? other)
        {
			if (other is null) return false;
			return Engine!.Equals(other.Engine) &&
				   Brand!.Equals(other.Brand) && 
				   Model!.Equals(other.Model) &&
				   BodyType.Equals(other.BodyType);
        }

        public override bool Equals(object? obj)
        {
            return Equals(obj as Automobile);
        }

        public override string ToString()
		{
			return $"{Brand} {Model} automobile :\n" +
				   $"\tEngine {Engine}\n" +
				   $"\tBody type : {BodyType}";
		}

        public override int GetHashCode()
        {
            return Engine!.GetHashCode() - Brand!.GetHashCode() + Model!.GetHashCode()
				- BodyType.GetHashCode() << 3;
        }

    }
}