namespace Lab6.Classes;

public abstract class Product
{
    protected double _price { get; set; }
    private DateTime _productionDate { get; set; }
    private DateTime _expirationDate { get; set; }

    //protected Product() {}
    protected Product(double price, DateTime productionDate,
        DateTime expirationDate)
    {
        if (DateTime.Compare(productionDate, expirationDate) >= 0)
            throw new Exception("Expiration date should be later than production date.");
        _price = price;
        _productionDate = productionDate;
        _expirationDate = expirationDate;
    }

    public bool IsExpired() => 
        DateTime.Compare(DateTime.Today, _expirationDate) >= 0;

    public abstract void Consume();

    public abstract void Sell();
}