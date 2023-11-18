using lab_1;
using NewNumeric;
using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;
using Microsoft.SolverFoundation.Common;

namespace lab_1
{
    class lab_2
    {
        static Rational[,] T = new Rational[3, 3]
        {
            {new Rational(5, 1),  new Rational(-1, 1),     new Rational(3, 1) },
            {new Rational(1, 1),  new Rational(-4, 1),     new Rational(2, 1) },
            {new Rational(2, 1),  new Rational(-1, 1),     new Rational(5, 1) }
        };
        static Rational[] T_b = new Rational[3] { new Rational(5, 1), new Rational(20, 1), new Rational(10, 1) };

        static Rational[,] C = new Rational[5, 5]
        {
            {new Rational(1, 100),  new Rational(0, 1),     new Rational(-2, 100),  new Rational(0, 1),     new Rational(0, 1)},
            {new Rational(1, 100),  new Rational(1, 100),   new Rational(-2, 100),  new Rational(0, 1),     new Rational(0, 1)},
            {new Rational(0, 1),    new Rational(1, 100),   new Rational(1, 100),   new Rational(0, 1),     new Rational(-2, 100)},
            {new Rational(0, 1),    new Rational(0, 1),     new Rational(1, 100),   new Rational(1, 100),   new Rational(0, 1)},
            {new Rational(0, 1),    new Rational(0, 1),     new Rational(0, 1),     new Rational(1, 100),   new Rational(1, 100)},
        };

        static Rational[,] D = new Rational[5, 5]
        {
            {new Rational(133, 100),    new Rational(21, 100),     new Rational(17, 100),   new Rational(12, 100),     new Rational(-13, 100)},
            {new Rational(-13, 100),    new Rational(-133, 100),   new Rational(11, 100),   new Rational(17, 100),     new Rational(12, 100)},
            {new Rational(12, 100),     new Rational(-13, 100),    new Rational(-133, 100), new Rational(11, 100),     new Rational(17, 100)},
            {new Rational(17, 100),     new Rational(12, 100),     new Rational(-13, 100),  new Rational(-133, 100),   new Rational(11, 100)},
            {new Rational(11, 100),     new Rational(67, 100),     new Rational(12, 100),   new Rational(-13, 100),    new Rational(-133, 100)},
        };
        static Rational[] b = new Rational[5] { new Rational(12, 10), new Rational(22, 10), new Rational(4, 1), new Rational(0, 1), new Rational(-12, 10) };
        static public void mini_main()
        {
            Console.WriteLine("Тестовое уравнение");
            Rational[] T_Rationals = T_Iteration(T, T_b);
            foreach (Rational a in T_Rationals)
            {
                Console.WriteLine(a.ToString() + "\t" + ((decimal)a).ToString("F" + 4));
            }
            Console.WriteLine();
            Check_answ(T_Rationals, T);
            Console.WriteLine("Мой вариант(8)\n");
            Rational[,] A = new Rational[5, 5];
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

            Rational[] Rationals = Iteration(A);
            for (int i = 0; i < Rationals.Length; i++)
            {
                Rationals[i] = new();
            }

            Console.WriteLine("\nКорни уравнения методом простых итераций");
            foreach (Rational a in Rationals)
            {
                Console.WriteLine(a.ToString() + "\t" + ((decimal)a).ToString("F" + 4));
            }

            Rationals = Zaidela(A);
            for (int i = 0; i < Rationals.Length; i++)
            {
                Rationals[i] = new();
            }
            Console.WriteLine("\nКорни уравнения методом Зейделя");
            foreach (Rational a in Rationals)
            {
                Console.WriteLine(a.ToString() + "\t" + ((decimal)a).ToString("F" + 4));
            }

            Console.WriteLine("\nПроверка корней подстановкой в изначальную матрицу: ");
            Check_answ(Rationals, A);
        }

        static Rational[] Iteration(Rational[,] A)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            Rational[] prev_it = new Rational[A.GetLength(0)];
            for (int i = 0; i < prev_it.Length; i++)
                prev_it[i] = new Rational();
            Rational[] this_it = new Rational[A.GetLength(0)];
            for (int i = 0; i < this_it.Length; i++)
                prev_it[i] = new Rational();

            int it;
            for (it = 0; ; it++)
            {
                this_it[0] = (b[0] - (A[0, 1] * prev_it[1] + A[0, 2] * prev_it[2] + A[0, 3] * prev_it[3] + A[0, 4] * prev_it[4])) / A[0, 0];
                this_it[1] = (b[1] - (A[1, 0] * prev_it[0] + A[1, 2] * prev_it[2] + A[1, 3] * prev_it[3] + A[1, 4] * prev_it[4])) / A[1, 1];
                this_it[2] = (b[2] - (A[2, 0] * prev_it[0] + A[2, 1] * prev_it[1] + A[2, 3] * prev_it[3] + A[2, 4] * prev_it[4])) / A[2, 2];
                this_it[3] = (b[3] - (A[3, 0] * prev_it[0] + A[3, 1] * prev_it[1] + A[3, 2] * prev_it[2] + A[3, 4] * prev_it[4])) / A[3, 3];
                this_it[4] = (b[4] - (A[4, 0] * prev_it[0] + A[4, 1] * prev_it[1] + A[4, 2] * prev_it[2] + A[4, 3] * prev_it[3])) / A[4, 4];
                if (Check_end(prev_it, this_it))
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

        static Rational[] T_Iteration(Rational[,] A, Rational[] b)
        {
            Rational[] prev_it = new Rational[A.GetLength(0)];
            for (int i = 0; i < prev_it.Length; i++)
                prev_it[i] = new Rational();
            Rational[] this_it = new Rational[A.GetLength(0)];
            for (int i = 0; i < this_it.Length; i++)
                prev_it[i] = new Rational();
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

        static Rational[] Zaidela(Rational[,] A)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            Rational[] prev_it = new Rational[A.GetLength(0)];
            for (int i = 0; i < prev_it.Length; i++)
                prev_it[i] = new Rational();
            Rational[] this_it = new Rational[A.GetLength(0)];
            for (int i = 0; i < this_it.Length; i++)
                prev_it[i] = new Rational();

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

        static Rational pogreshnost(Rational first, Rational second)
        {
            Rational answer = new Rational();
            answer = Rational.Abs(first - second) / Rational.Abs(first);
            return answer;
        }

        static bool Check_end(Rational[] prev_it, Rational[] this_it)
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

        static bool T_Check_end(Rational[] prev_it, Rational[] this_it)
        {
            if ((decimal)pogreshnost(this_it[0], prev_it[0]) < (decimal)0.01 &&
                (decimal)pogreshnost(this_it[1], prev_it[1]) < (decimal)0.01 &&
                (decimal)pogreshnost(this_it[2], prev_it[2]) < (decimal)0.01)
                return true;
            else
                return false;
        }

        static void Check_answ(Rational[] answ, Rational[,] A)
        {
            for (int i = 0; i < A.GetLength(0); i++)
            {
                Rational a = new Rational();
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    a += A[i, j] * answ[j];
                }
                Console.WriteLine(a.ToString() + "\t" + ((decimal)a).ToString("F" + 4));
            }
        }
    }
}

public class Program
{
    public static void Main()
    {
        lab_2.mini_main();
    }
}