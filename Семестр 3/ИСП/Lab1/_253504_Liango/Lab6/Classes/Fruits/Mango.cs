namespace Lab6.Classes.Fruits;

public sealed class Mango : Fruit
{
    public Mango(double price, DateTime productionDate,
        DateTime expirationDate) 
        : base(price, productionDate, expirationDate) {}

    public Mango(double price, DateTime productionDate,
        DateTime expirationDate, Taste taste) 
        : base(price, productionDate, expirationDate, taste) {}

    public override string TasteFruit() =>
        $"Mango tastes {Taste.ToString().ToLower()}.";

    public override void Consume()
    {
        Console.WriteLine("Mango is consumed");
        Console.WriteLine(IsExpired()
            ? "You`ve been poisoned by rotten mango."
            : "That was a tasty specimen of a mango.");
    }

    public override void Sell()
    {
        Console.WriteLine(IsExpired() 
            ? "You sold someone a rotten mango for ${0}"
            : "You sold someone a mango for ${0}", _price);
    }
}