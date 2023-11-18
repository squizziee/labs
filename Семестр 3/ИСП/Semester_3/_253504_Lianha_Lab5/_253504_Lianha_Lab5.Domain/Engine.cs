namespace _253504_Lianha_Lab5.Domain
{
	public class Engine : IEquatable<Engine>
	{
		public string? Name { get; set; }
		public double Power { get; set; }
		public double Torque { get; set; }
		public double Displacement { get; set; }
		public int CylinderCount { get; set; }
		public EngineLayoutType LayoutType { get; set; }

        public bool Equals(Engine? other)
        {
			if (other is null) return false;
			return Name!.Equals(other.Name) &&
				   Power.Equals(other.Power) &&
				   Torque.Equals(other.Torque) &&
				   Displacement.Equals(other.Displacement) &&
				   CylinderCount.Equals(other.CylinderCount) &&
				   LayoutType.Equals(other.LayoutType);
        }

        public override bool Equals(object? obj)
        {
            return Equals(obj as Engine);
        }

        public override string ToString()
		{
			return $"{Name} :\n" +
				   $"\t\tPower in horsepower : {Power}\n" +
				   $"\t\tTorque in newtons per meter : {Torque}\n" +
				   $"\t\tDisplacement in cubic centimeters : {Displacement}\n" +
				   $"\t\tCylinder count : {CylinderCount}\n" +
				   $"\t\tEngine layout type : {LayoutType}";
		}

        public override int GetHashCode()
        {
            return Name!.GetHashCode() - (Power.GetHashCode() << 2) + Torque.GetHashCode() 
				 - Displacement.GetHashCode() + CylinderCount.GetHashCode() 
				 - (LayoutType.GetHashCode() >> 2);
        }
    }
}