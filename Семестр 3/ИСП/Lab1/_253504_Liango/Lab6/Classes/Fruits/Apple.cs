namespace Lab6.Classes.Fruits;

public sealed class Apple : Fruit
{
    public Apple(double price, DateTime productionDate,
        DateTime expirationDate) : base(price, productionDate, expirationDate) {}

    public Apple(double price, DateTime productionDate,
        DateTime expirationDate, Taste taste) : base(price, productionDate, expirationDate, taste) {}

    public override void Consume()
    {
        Console.WriteLine("Apple is consumed");
        Console.WriteLine(IsExpired()
            ? "You`ve been poisoned by rotten apple."
            : "That was a tasty specimen of an apple.");
    }
    
    public override void Sell()
    {
        Console.WriteLine(IsExpired() 
            ? "You sold someone a rotten apple for ${0}"
            : "You sold someone an apple for ${0}", _price);
    }
}