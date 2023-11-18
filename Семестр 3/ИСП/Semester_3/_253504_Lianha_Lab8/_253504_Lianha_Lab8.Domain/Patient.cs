namespace _253504_Lianha_Lab8.Domain
{
    public class Patient
    {
        public int Id { get; set; }
        public string? Name { get; set; }
        public double TreatmentTotal { get; set; }

        public Patient(int id, string name, double displacement) => 
            (Id, Name, TreatmentTotal) = (id, name, displacement);
        public Patient() =>
            (Id, Name, TreatmentTotal) = (-1, "undefiend", 0);

        public override string ToString() =>
            $"{Id},{Name},{TreatmentTotal};";
    }
}