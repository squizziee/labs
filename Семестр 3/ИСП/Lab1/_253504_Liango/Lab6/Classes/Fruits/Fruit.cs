namespace Lab6.Classes;

public abstract class Fruit : Product
{
    public Taste Taste { get; set; }

    protected Fruit(double price, DateTime productionDate,
        DateTime expirationDate) : base(price, productionDate, expirationDate)
    {
        Taste = Taste.Alright;
    }

    protected Fruit(double price, DateTime productionDate,
        DateTime expirationDate, Taste taste) : base(price, productionDate, expirationDate)
    {
        Taste = taste;
    }

    public virtual string TasteFruit() => 
        $"Fruit tastes {Taste.ToString().ToLower()}.";
}