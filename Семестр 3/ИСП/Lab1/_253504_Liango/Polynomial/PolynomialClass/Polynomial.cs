namespace PolynomialClass;

public class Polynomial
{
    private int _a { get; set; }
    private int _b { get; set; }
    private int _c { get; set; }

    public Polynomial(int a, int b, int c) => (_a, _b, _c) = (a, b, c);

    public override String ToString() => 
        String.Format("{0}x + {1}y + {2}z", 
            _a == 1 ? "" : _a,
            _b == 1 ? "" : _b,
            _c == 1 ? "" : _c);

    // Comparison operators
    public static bool operator ==(Polynomial left, Polynomial right) => 
        left._a == right._a && left._b == right._b && left._c == right._c;

    public static bool operator !=(Polynomial left, Polynomial right) => 
        !(left == right);

    // Bool cast operators
    public static bool operator true(Polynomial obj) =>
        obj._a != 0 || obj._b != 0 || obj._c != 0;

    public static bool operator false(Polynomial obj) => 
        obj._a == 0 && obj._b == 0 && obj._c == 0;

    // Other cast operators (Polynomial to int, int to Polynomial)

    public static explicit operator int(Polynomial obj) => obj._a;

    public static explicit operator Polynomial(int num) => new(num, 0, 0);

    // Aritmetical operators
    public static Polynomial operator +(Polynomial obj) => obj;

    public static Polynomial operator -(Polynomial obj) => 
        new(-obj._a, -obj._b, -obj._c);

    public static Polynomial operator +(Polynomial left, Polynomial right) => 
        new(left._a + right._a, left._b + right._b, left._c + right._c);

    public static Polynomial operator -(Polynomial left, Polynomial right) => 
        new(left._a - right._a, left._b - right._b, left._c - right._c);

    public static Polynomial operator *(Polynomial obj, int cff) => 
        new(cff * obj._a, cff * obj._b, cff * obj._c);

    public static Polynomial operator /(Polynomial obj, int cff) => 
        new(obj._a / cff, obj._b / cff, obj._c / cff);

    public static Polynomial operator ++(Polynomial obj) =>
        new(obj._a + 1, obj._b + 1, obj._c + 1);

    public static Polynomial operator --(Polynomial obj) =>
        new(obj._a - 1, obj._b - 1, obj._c - 1);

    // Object class override methods
    public override bool Equals(object? obj) =>
        obj is not null && (obj is Polynomial polynomial) && polynomial == this;

    public override int GetHashCode() => 
        _a.GetHashCode() << _b.GetHashCode() >> _c.GetHashCode();
}