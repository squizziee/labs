using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253504_Lianha_Lab4.Entities
{
	internal class Patient
	{
		public string Name { get; set; }
		private int _roomNumber;
		public int RoomNumber
		{
			get {
				return _roomNumber;
			}
			set { 
				if (value <= 0)
				{
					throw new ArgumentException("Only positive room numbers are allowed");
				}
				_roomNumber = value;
			} }
		public bool IsPaidForByInsurance { get; set; }

		public Patient(string name, int roomNumber, bool isPaidForbyInsurance) => 
			(Name, RoomNumber, IsPaidForByInsurance) = (name, roomNumber, isPaidForbyInsurance);

		public static Patient FromBinary(BinaryReader reader)
		{
			try
			{
				var patientName = reader.ReadString();
				var patientRoomNumber = reader.ReadInt32();
				var isPatientPaidForWithInsurance = reader.ReadBoolean();
				return new Patient(patientName, patientRoomNumber, isPatientPaidForWithInsurance);
			} catch (Exception)
			{
				return new Patient("ERROR", -1, false);
			}
		}

		public static int ToBinary(BinaryWriter writer, Patient patient)
		{
			writer.Write(patient.Name);
			writer.Write(patient.RoomNumber);
			writer.Write(patient.IsPaidForByInsurance);
			return 1;
		}

        public override string ToString()
        {
            return $"Patient {Name} : Room №{RoomNumber}, treatment is {(IsPaidForByInsurance ? "" : "NOT ")}paid by insurance";
        }
    }
}
