using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*namespace lab_1
{
    class lab_2
    {
        static fraction[,] T = new fraction[3, 3]
        {
            {new fraction(5, 1),  new fraction(-1, 1),     new fraction(3, 1) },
            {new fraction(1, 1),  new fraction(-4, 1),     new fraction(2, 1) },
            {new fraction(2, 1),  new fraction(-1, 1),     new fraction(5, 1) }
        };

        static fraction[] T_b = new fraction[3] { new fraction(5, 1), new fraction(20, 1), new fraction(10, 1) };

        static fraction[,] C = new fraction[5, 5]
        {
            {new fraction(1, 100),  new fraction(0, 1),     new fraction(-2, 100),  new fraction(0, 1),     new fraction(0, 1)},
            {new fraction(1, 100),  new fraction(1, 100),   new fraction(-2, 100),  new fraction(0, 1),     new fraction(0, 1)},
            {new fraction(0, 1),    new fraction(1, 100),   new fraction(1, 100),   new fraction(0, 1),     new fraction(-2, 100)},
            {new fraction(0, 1),    new fraction(0, 1),     new fraction(1, 100),   new fraction(1, 100),   new fraction(0, 1)},
            {new fraction(0, 1),    new fraction(0, 1),     new fraction(0, 1),     new fraction(1, 100),   new fraction(1, 100)},
        };

        static fraction[,] D = new fraction[5, 5]
        {
            {new fraction(133, 100),    new fraction(21, 100),     new fraction(17, 100),   new fraction(12, 100),     new fraction(-13, 100)},
            {new fraction(-13, 100),    new fraction(-133, 100),   new fraction(11, 100),   new fraction(17, 100),     new fraction(12, 100)},
            {new fraction(12, 100),     new fraction(-13, 100),    new fraction(-133, 100), new fraction(11, 100),     new fraction(17, 100)},
            {new fraction(17, 100),     new fraction(12, 100),     new fraction(-13, 100),  new fraction(-133, 100),   new fraction(11, 100)},
            {new fraction(11, 100),     new fraction(67, 100),     new fraction(12, 100),   new fraction(-13, 100),    new fraction(-133, 100)},
        };

        static fraction[] b = new fraction[5] { new fraction(12, 10), new fraction(22, 10), new fraction(4, 1), new fraction(0, 1), new fraction(-12, 10) };


        static public void mini_main()
        {
            Console.WriteLine("Тестовое уравнение");
            fraction[] T_fractions = T_Iteration(T, T_b);
            foreach (fraction a in T_fractions)
            {
                Console.WriteLine(a.ToString() + "\t" + ((decimal)a).ToString("F" + 4));
            }
            Console.WriteLine();
            Check_answ(T_fractions, T);

            Console.WriteLine("Мой вариант(8)\n");
            fraction[,] A = new fraction[5, 5];
            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    A[i, j] = 8 * C[i, j] + D[i, j];
                }
            }

            Console.WriteLine("Изначальная матрица");
            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    Console.Write(((decimal)A[i, j]).ToString("F" + 4) + "\t");
                }
                Console.WriteLine(" | " + ((decimal)b[i]).ToString("F" + 4));
            }

            fraction[] fractions = Iteration(A);
            for(int i = 0; i < fractions.Length; i++)
            {
                fractions[i].clear();
            }

            Console.WriteLine("\nКорни уравнения методом простых итераций");
            foreach(fraction a in fractions)
            {
                Console.WriteLine(a.ToString() + "\t" + ((decimal)a).ToString("F" + 4));
            }

            fractions = Zaidela(A);
            for (int i = 0; i < fractions.Length; i++)
            {
                fractions[i].clear();
            }
            Console.WriteLine("\nКорни уравнения методом Зейделя");
            foreach (fraction a in fractions)
            {
                Console.WriteLine(a.ToString() + "\t" + ((decimal)a).ToString("F" + 4));
            }

            Console.WriteLine("\nПроверка корней подстановкой в изначальную матрицу: ");
            Check_answ(fractions, A);
        }

        static fraction[] Iteration(fraction[,] A)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            fraction[] prev_it = new fraction[A.GetLength(0)];
            for (int i = 0; i < prev_it.Length; i++)
                prev_it[i] = new fraction();
            fraction[] this_it = new fraction[A.GetLength(0)];
            for (int i = 0; i < this_it.Length; i++)
                prev_it[i] = new fraction();

            int it;
            for (it = 0; ; it++)
            {
                this_it[0] = (b[0] - (A[0, 1] * prev_it[1] + A[0, 2] * prev_it[2] + A[0, 3] * prev_it[3] + A[0, 4] * prev_it[4])) / A[0, 0];
                this_it[1] = (b[1] - (A[1, 0] * prev_it[0] + A[1, 2] * prev_it[2] + A[1, 3] * prev_it[3] + A[1, 4] * prev_it[4])) / A[1, 1];
                this_it[2] = (b[2] - (A[2, 0] * prev_it[0] + A[2, 1] * prev_it[1] + A[2, 3] * prev_it[3] + A[2, 4] * prev_it[4])) / A[2, 2];
                this_it[3] = (b[3] - (A[3, 0] * prev_it[0] + A[3, 1] * prev_it[1] + A[3, 2] * prev_it[2] + A[3, 4] * prev_it[4])) / A[3, 3];
                this_it[4] = (b[4] - (A[4, 0] * prev_it[0] + A[4, 1] * prev_it[1] + A[4, 2] * prev_it[2] + A[4, 3] * prev_it[3])) / A[4, 4];
                if(Check_end(prev_it,this_it))
                {
                    Console.WriteLine("Кол-во итераций методом простых итераций: " + ++it);
                    break;
                }
                else
                {
                    for (int k = 0; k < this_it.Length; k++)
                        prev_it[k] = this_it[k];
                }
            }
            stopwatch.Stop();
            Console.WriteLine("Время, затраченное на простых итерациях(милисек): " + stopwatch.ElapsedMilliseconds);
            return this_it;
        }

        static fraction[] T_Iteration(fraction[,] A, fraction[] b)
        {
            fraction[] prev_it = new fraction[A.GetLength(0)];
            for (int i = 0; i < prev_it.Length; i++)
                prev_it[i] = new fraction();
            fraction[] this_it = new fraction[A.GetLength(0)];
            for (int i = 0; i < this_it.Length; i++)
                prev_it[i] = new fraction();
            int ii;
            for (ii = 0; ; ii++)
            {
                this_it[0] = (b[0] - (A[0, 1] * prev_it[1] + A[0, 2] * prev_it[2])) / A[0, 0];
                this_it[1] = (b[1] - (A[1, 0] * prev_it[0] + A[1, 2] * prev_it[2])) / A[1, 1];
                this_it[2] = (b[2] - (A[2, 0] * prev_it[0] + A[2, 1] * prev_it[1])) / A[2, 2];
                if (T_Check_end(prev_it, this_it))
                {
                    Console.WriteLine(++ii + "-кол-во итераций");
                    break;
                }
                else
                {
                    for (int i = 0; i < this_it.Length; i++)
                        prev_it[i] = this_it[i];
                }
            }
            return this_it;
        }

        static fraction[] Zaidela(fraction[,] A)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            fraction[] prev_it = new fraction[A.GetLength(0)];
            for (int i = 0; i < prev_it.Length; i++)
                prev_it[i] = new fraction();
            fraction[] this_it = new fraction[A.GetLength(0)];
            for (int i = 0; i < this_it.Length; i++)
                prev_it[i] = new fraction();

            int it;
            for (it = 0; ; it++)
            {
                this_it[0] = (b[0] - (A[0, 1] * prev_it[1] + A[0, 2] * prev_it[2] + A[0, 3] * prev_it[3] + A[0, 4] * prev_it[4])) / A[0, 0];
                this_it[1] = (b[1] - (A[1, 0] * this_it[0] + A[1, 2] * prev_it[2] + A[1, 3] * prev_it[3] + A[1, 4] * prev_it[4])) / A[1, 1];
                this_it[2] = (b[2] - (A[2, 0] * this_it[0] + A[2, 1] * this_it[1] + A[2, 3] * prev_it[3] + A[2, 4] * prev_it[4])) / A[2, 2];
                this_it[3] = (b[3] - (A[3, 0] * this_it[0] + A[3, 1] * this_it[1] + A[3, 2] * this_it[2] + A[3, 4] * prev_it[4])) / A[3, 3];
                this_it[4] = (b[4] - (A[4, 0] * this_it[0] + A[4, 1] * this_it[1] + A[4, 2] * this_it[2] + A[4, 3] * this_it[3])) / A[4, 4];
                if (Check_end(prev_it, this_it))
                {
                    Console.WriteLine("Кол-во итераций методом Зейделя: " + ++it);
                    break;
                }
                else
                {
                    for (int k = 0; k < this_it.Length; k++)
                        prev_it[k] = this_it[k];
                }
            }
            stopwatch.Stop();
            Console.WriteLine("Время, затраченное на простых итерациях(милисек): " + stopwatch.ElapsedMilliseconds);
            return this_it;
        }

        static fraction pogreshnost(fraction first, fraction second)
        {
            fraction answer = new fraction();
            answer = (first - second).Abs() / first.Abs();
            return answer;
        }

        static bool Check_end(fraction[] prev_it, fraction[] this_it)
        {
            if ((decimal)pogreshnost(this_it[0], prev_it[0]) < (decimal)0.0001 &&
                (decimal)pogreshnost(this_it[1], prev_it[1]) < (decimal)0.0001 &&
                (decimal)pogreshnost(this_it[2], prev_it[2]) < (decimal)0.0001 &&
                (decimal)pogreshnost(this_it[3], prev_it[3]) < (decimal)0.0001 &&
                (decimal)pogreshnost(this_it[4], prev_it[4]) < (decimal)0.0001)
                return true;
            else
                return false;
        }

        static bool T_Check_end(fraction[] prev_it, fraction[] this_it)
        {
            if ((decimal)pogreshnost(this_it[0], prev_it[0]) < (decimal)0.01 &&
                (decimal)pogreshnost(this_it[1], prev_it[1]) < (decimal)0.01 &&
                (decimal)pogreshnost(this_it[2], prev_it[2]) < (decimal)0.01)
                return true;
            else
                return false;
        }

        static void Check_answ(fraction[] answ, fraction[,] A)
        {
            for(int i = 0; i < A.GetLength(0); i++)
            {
                fraction a = new fraction();
                for(int j = 0; j < A.GetLength(1); j++)
                {
                    a += A[i,j] * answ[j];
                }
                Console.WriteLine(a.ToString() + "\t" + ((decimal)a).ToString("F" + 4));
            }
        }
    }
}*/
