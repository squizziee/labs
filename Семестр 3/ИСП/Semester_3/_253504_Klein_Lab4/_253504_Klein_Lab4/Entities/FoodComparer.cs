using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253504_Klein_Lab4.Entities
{
    internal class FoodComparer : IComparer<Food>
    {
        public int Compare(Food? x, Food? y)
        {
            if (x is null || y is null)
            {
                return -1;
            }
            return x.Name!.CompareTo(y.Name);
        }
    }
}
