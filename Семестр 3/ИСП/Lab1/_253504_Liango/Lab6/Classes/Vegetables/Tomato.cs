namespace Lab6.Classes.Vegetables;

public sealed class Tomato : Vegetable
{
    public Tomato(double price, DateTime productionDate, 
        DateTime expirationDate) 
        : base(price, productionDate, expirationDate) {}

    public Tomato(double price, DateTime productionDate, 
        DateTime expirationDate, Healthiness healthiness) 
        : base(price, productionDate, expirationDate, healthiness) {}

    public override void Consume()
    {
        Console.WriteLine("Tomato is consumed");
        Console.WriteLine(IsExpired()
            ? "You`ve been poisoned by a rotten tomato."
            : "That was a good specimen of a tomato.");
    }

    public override void Sell()
    {
        Console.WriteLine(IsExpired() 
            ? "You sold someone a rotten tomato for ${0}"
            : "You sold someone a tomato for ${0}", _price);
    }
    
    public new string TasteVegetable() =>
        $"Tomato should be nutritious. This one is {Healthiness.ToString().ToLower()}. ";
}