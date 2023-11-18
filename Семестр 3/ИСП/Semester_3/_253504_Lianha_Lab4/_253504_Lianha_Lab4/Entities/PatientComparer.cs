using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253504_Lianha_Lab4.Entities
{
    internal class PatientComparer : IComparer<Patient>
    {
        public int Compare(Patient? x, Patient? y)
        {
            if (x is null || y is null)
            {
                return 0;
            }
            return x.Name.CompareTo(y.Name);
        }
    }
}
