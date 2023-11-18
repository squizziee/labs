namespace Lab6.Classes.Vegetables;

public abstract class Vegetable : Product
{
    protected Healthiness Healthiness { get; set; }

    protected Vegetable(double price, DateTime productionDate,
        DateTime expirationDate)
        : base(price, productionDate, expirationDate)
    {
        Healthiness = Healthiness.Neutral;
    }

    protected Vegetable(double price, DateTime productionDate,
        DateTime expirationDate, Healthiness healthiness) 
        : base(price, productionDate, expirationDate)
    {
        Healthiness = healthiness;
    }

    public virtual string TasteVegetable() =>
        $"Vegetables should be nutritious. This one is {Healthiness.ToString().ToLower()}. ";
}