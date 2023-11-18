using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253504_Klein_Lab4.Entities
{
	public class Food
	{
		public string? Name { get; set; }
		public int Id { get; set; }
		public bool IsExpired { get; set; }

        public override string ToString()
        {
            return $"@{Id} Name: {Name}, is {(IsExpired ? "" : "not")} expired";
        }
    }
}
