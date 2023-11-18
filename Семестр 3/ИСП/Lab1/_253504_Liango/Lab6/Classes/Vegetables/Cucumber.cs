namespace Lab6.Classes.Vegetables;

public sealed class Cucumber : Vegetable
{
    public Cucumber(double price, DateTime productionDate, 
        DateTime expirationDate) 
        : base(price, productionDate, expirationDate) {}

    public Cucumber(double price, DateTime productionDate, 
        DateTime expirationDate, Healthiness healthiness) 
        : base(price, productionDate, expirationDate, healthiness) {}

    public override void Consume()
        {
            Console.WriteLine("Cucumber is consumed");
            Console.WriteLine(IsExpired()
                ? "You`ve been poisoned by a rotten cucumber."
                : "That was a good specimen of a cucumber.");
        }
    
        public override void Sell()
        {
            Console.WriteLine(IsExpired() 
                ? "You sold someone a rotten cucumber for ${0}"
                : "You sold someone a cucumber for ${0}", _price);
        }
}