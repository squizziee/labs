using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_1
{
    class lab_1_modified
    {
        // test 1
        /*{8.0, 1.2, 1.0, 9.0, 1.0 },
                {6.0, 2.0, 9.0, 8.0, 2.0 },
                { 5.0, 3.0, 8.0, 7.0, 9.0 },
                { 3.0, 4.0, 7.0, 6.0, 7.0 },
                { 2.0, 5.0, 6.0, 14.0, 5.0 }*/
        /*{1.0, 1.0, 1.0, 1.0, 1.0 },
                {1.0, 2.0, 1.0, 2.0, 1.0 },6
                { 2.0, 2.0, 2.0, 2.0, 2.0 },
                { 1.0, 2.0, 1.0, 0.0, 0.0 },
                { 1.0, 1.0, 13.0, 14.0, 2.0 }*/
const int size = 5;
        static public void _main()
        {
            NumberFormatInfo info = new();
            info.NumberDecimalDigits = 64;
            double[,] C = new double[,]
            {
                {8.0, 1.2, 1.0, 9.0, 1.0 },
                {6.0, 2.0, 9.0, 8.0, 2.0 },
                { 5.0, 3.0, 8.0, 7.0, 9.0 },
                { 3.0, 4.0, 7.0, 6.0, 7.0 },
                { 2.0, 5.0, 6.0, 14.0, 5.0 },
            };

            double[,] D = new double[,]
            {
                {1.0, 1.0, 1.0, 1.0, 1.0 },
                {1.0, 2.0, 1.0, 2.0, 1.0 },
                { 2.0, 2.0, 2.0, 2.0, 2.0 },
                { 1.0, 2.0, 1.0, 0.0, 0.0 },
                { 1.0, 1.0, 13.0, 14.0, 2.0 },
            };

            double[] b = new double[] { 4.1, 4.2, 4.2, 4.2, 4.2 };
            int[] out_answ = new int[] { 0, 1, 2, 3, 4 };

            double[,] A = new double[size, size];

            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    A[i, j] = 8 * C[i, j] + D[i, j];
                }
            }

            Console.WriteLine("Изначальная матрица:");
            out_array(A, b);
            var valid = check(C);
            if (!valid)
            {
                Console.WriteLine("Нет решений");
                return;
            }
            edit_array(A, b);
            Console.WriteLine("Измененная матрица(метод последовательного исключения неизвестных):");
            out_array(A, b);

            Console.WriteLine("\nОтветы:");
            foreach (double root in find_roots(A, b))
            {
                Console.WriteLine(root.ToString("F" + 16) + "  ");
            }
            Console.WriteLine();

            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    A[i, j] = 8 * C[i, j] + D[i, j];
                }
                b[i] = 4.2;
            }

            main_column(A, b);
            Console.WriteLine("Измененная матрица(метод с выбором главного элемента по столбцу):");
            out_array(A, b);

            Console.WriteLine("\nОтветы:");
            foreach (double root in find_roots(A, b))
            {
                Console.WriteLine(root.ToString("F" + 16) + "  ");
            }
            Console.WriteLine();

            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    A[i, j] = 8 * C[i, j] + D[i, j];
                }
                b[i] = 4.2;
            }
            main_elem(A, b, out_answ);
            Console.WriteLine("Измененная матрица(метод с выбором главного элемента по всей матрице):");
            out_array(A, b);

            double[] answer = find_roots(A, b);

            Console.WriteLine("\nОтветы:");
            for (int i = 0; i < find_roots(A, b).Length; i++)
            {
                Console.WriteLine(find_roots(A, b)[out_answ[i]].ToString("F" + 16) + "  ");
            }
            Console.WriteLine();

            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    A[i, j] = 8 * C[i, j] + D[i, j];
                }
                b[i] = 4.2;
            }
            check_answ(A, answer, out_answ);
        }

        static bool check(double[,] arr)
        {
            for (int i = 0; i < arr.GetLength(0); i++)
            {
                if (Math.Abs(arr[i, 0]) > Double.Epsilon)
                {
                    return true;
                }
            }
            return false;
        }

        static void out_array(double[,] arr, double[] bonus)
        {
            for (int i = 0; i < arr.GetLength(0); i++)
            {
                for (int j = 0; j < arr.GetLength(1); j++)
                {
                    Console.Write(arr[i, j].ToString("F" + 16) + "\t");
                }
                Console.Write("| " + bonus[i].ToString("F" + 16));
                Console.WriteLine();
            }
        }

        static void edit_array(double[,] arr, double[] bonus)
        {
            for (int i = 0; i < arr.GetLength(0); i++)
            {
                for (int j = i + 1; j < arr.GetLength(0); j++)
                {
                    double q = arr[j, i] / arr[i, i];
                    for (int k = 0; k < arr.GetLength(1); k++)
                    {
                        arr[j, k] -= q * arr[i, k];
                    }
                    bonus[j] -= bonus[i] * q;
                }
            }
        }

        static void main_column(double[,] arr, double[] bonus)
        {
            for (int i = 0; i < arr.GetLength(0); i++)
            {
                int max_ind = i;
                double max = arr[i, i];
                for (int j = i + 1; j < arr.GetLength(0); j++)
                {
                    if (Math.Abs(max) < Math.Abs(arr[j, i]))
                    {
                        max = arr[j, i];
                        max_ind = j;
                    }
                }

                if (i != max_ind)
                {
                    for (int j = i; j < arr.GetLength(1); j++)
                    {
                        swap(ref arr[i, j], ref arr[max_ind, j]);
                    }
                    swap(ref bonus[i], ref bonus[max_ind]);
                }

                for (int j = i + 1; j < arr.GetLength(0); j++)
                {
                    double q = arr[j, i] / arr[i, i];
                    for (int k = 0; k < arr.GetLength(1); k++)
                    {
                        arr[j, k] -= q * arr[i, k];
                    }
                    bonus[j] -= bonus[i] * q;
                }
            }
        }

        static void main_elem(double[,] arr, double[] bonus, int[] out_answ)
        {
            for (int i = 0; i < arr.GetLength(0); i++)
            {
                int row_ind = i, col_ind = i;
                double max = arr[i, i];
                for (int j = i; j < arr.GetLength(0); j++)
                {
                    for (int k = i; k < arr.GetLength(1); k++)
                    {
                        if (Math.Abs(max) < Math.Abs(arr[j, k]))
                        {
                            max = arr[j, k];
                            row_ind = j;
                            col_ind = k;
                        }
                    }
                }

                if (i != row_ind)
                {
                    for (int j = 0; j < arr.GetLength(0); j++)
                    {
                        swap(ref arr[i, j], ref arr[row_ind, j]);
                    }
                    swap(ref bonus[i], ref bonus[row_ind]);
                }

                //меняем местами столбцы
                if (i != col_ind)
                {
                    for (int j = 0; j < arr.GetLength(1); j++)
                    {
                        swap(ref arr[j, i], ref arr[j, col_ind]);
                    }
                    swap(ref out_answ[i], ref out_answ[col_ind]);
                }

                for (int j = i + 1; j < arr.GetLength(0); j++)
                {
                    double q = arr[j, i] / arr[i, i];
                    for (int k = 0; k < arr.GetLength(1); k++)
                    {
                        arr[j, k] -= q * arr[i, k];
                    }
                    bonus[j] -= bonus[i] * q;
                }
            }
        }

        static double[] find_roots(double[,] arr, double[] bonus)
        {
            double[] result = new double[size];
            for (int i = arr.GetLength(0) - 1; i >= 0; i--)
            {
                double S = 0;
                for (int k = i + 1; k < arr.GetLength(0); k++)
                {
                    S += arr[i, k] * result[k];
                }
                result[i] = (bonus[i] - S) / arr[i, i];
            }

            return result;
        }

        static void swap(ref double a, ref double b)
        {
            double c = a;
            a = b;
            b = c;
        }

        static void swap(ref int a, ref int b)
        {
            int c = a;
            a = b;
            b = c;
        }

        static void check_answ(double[,] A, double[] answ, int[] num)
        {
            for (int i = 0; i < A.GetLength(0); i++)
            {
                double b = 0;
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    b += A[i, j] * answ[num[j]];
                }
                Console.WriteLine("row " + i + "  " + b.ToString("F" + 16));
            }
        }
    }
}
