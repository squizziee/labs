namespace Lab8.Interfaces
{
    public interface IClient
    {
        void AddToDeposit(double sum);

        void TakeFromDeposit(double sum);

        IDeposit GetDeposit();
    }
}
