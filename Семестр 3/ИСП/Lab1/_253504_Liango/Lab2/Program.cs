// See https://aka.ms/new-console-template for more information

namespace Lab2
{
    internal abstract class Launcher
    {
        private static bool AreThreeDigitsTheSame(int number)
        {
            if (number <= 999 && number >= 100)
            {
                return number % 111 == 0;
            }
            return false;
        }
        
        // Task 1
        public static void Main(string[] args)
        {
            int action = 1;
            while (true)
            {
                if (action != 1)
                {
                    break;
                }
                Console.WriteLine("Action: 1 - enter number, 2 - stop");
                try
                {
                    action = Convert.ToInt32(Console.ReadLine());
                    switch (action)
                    {
                        case 1:
                            var n = Convert.ToInt32(Console.ReadLine());
                            Console.WriteLine("Three digits are the same: {0}", AreThreeDigitsTheSame(n));
                            break;
                    }
                }
                catch (Exception e)
                {
                    continue;
                }
            }
        }

        public static int IsPointPresentInArea(int x, int y)
        {
            if (x > -15 && x < 0 && y > -15 && y < 0)
            {
                return -1;
            }
            if ((x == -15 && y >= -15 && y <= 0) || (y == -15 && x >= -15 && x <= 0))
            {
                return 0;
            }
            return 1;
        }
        // Task 2
        /*public static void Main(string[] args)
        {
            int action = 1;
            while (true)
            {
                if (action != 1)
                {
                    break;
                }

                try
                {
                    Console.WriteLine("Action: 1 - enter coordinates, 2 - stop");
                    action = Convert.ToInt32(Console.ReadLine());
                    switch (action)
                    {
                        case 1:
                            var x = Convert.ToInt32(Console.ReadLine());
                            var y = Convert.ToInt32(Console.ReadLine());
                            int flag = IsPointPresentInArea(x, y);
                            string phrase;
                            if (flag == 1)
                            {
                                phrase = "Point is present in given area";
                            }
                            else if (flag == 0)
                            {
                                phrase = "Point is on the border of given area";
                            }
                            else
                            {
                                phrase = "Point is not present in given area";
                            }

                            Console.WriteLine(phrase);
                            break;
                    }
                }
                catch (Exception e)
                {
                    continue;
                }
            }
        }*/
    }
}