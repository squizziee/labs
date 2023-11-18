using System.Collections;

namespace _253504_Lianha_Lab1.Interfaces
{
    internal interface ICustomCollection<T> : IEnumerable<T>, IEnumerable
    {
        T this[int index] { get; set; }
        void Reset();
        void Next();
        T Current();
        int Count { get; }
        void Add(T item);
        void Remove(T item);
        T RemoveCurrent();
    }
}