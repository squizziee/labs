namespace Lab3.Services;

public abstract class Expression
{
    public static double Calc(double z)
    {
        double x;
        if (z > 0)
        {
            x = -3 * z;
        }
        else
        {
            x = z * z;
        }
        return x * (Math.Sin(x) + Math.Pow(Math.E, -x + 3));
    }
}