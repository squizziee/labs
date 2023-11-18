using _253504_Lianha_Lab1.Interfaces;
using System.Collections;

namespace _253504_Lianha_Lab1.Collections
{
	internal class MyCustomCollection<T> : ICustomCollection<T>
	{
		private class CollectionNode<M>
		{
			public M data;
			public CollectionNode<M>? next;
			public CollectionNode<M>? prev;
			public CollectionNode(M _data, CollectionNode<M>? _prev, CollectionNode<M>? _next) => 
				(data, next, prev) = (_data, _next, _prev);

		}

		private CollectionNode<T>? head;
		private CollectionNode<T>? tail;
		private CollectionNode<T>? curr;

		private int count = 0;

		public T this[int index]
		{
			get
			{
				var temp = head;
				for (int i = 0; i < count; i++)
				{
					if (index == i)
					{
						return temp!.data;
					}
					temp = temp!.next;

				}
				throw new IndexOutOfRangeException();
			}
			set
			{
				var temp = head;
				for (int i = 0; i < count; i++)
				{
					if (index == i)
					{
						temp!.data = value;
					}
					temp = temp!.next;
				}
				throw new IndexOutOfRangeException();
			}
		}

		public int Count => count;

		public void Add(T item)
		{
			if (head is null)
			{
				head = new CollectionNode<T>(item, null, null);
				tail = head;
				curr = head;
				count++;
				return;
			}
			tail!.next = new CollectionNode<T>(item, tail, null);
			tail = tail.next;
			count++;
		}

		public T Current()
		{
			return curr!.data;
		}

		public void Next()
		{
			curr = curr!.next;
		}

		public void Remove(T item)
		{
			var temp = head;
			bool foundItem = false;
			while (temp is not null)
			{
				if (temp!.data!.Equals(item))
				{
					foundItem = true;
					if (temp.next is null && temp.prev is null)
					{
						temp = null;
					}
					else if (temp.next is null)
					{
						temp!.prev!.next = null;

					}
					else if (temp.prev is null)
					{
						temp!.next!.prev = null;
					}
					else
					{
						temp!.prev!.next = temp.next;
						temp!.next!.prev = temp.prev;
					}
					break;
				}
				temp = temp.next;
			}
			if (!foundItem)
			{
				throw new NoSuchElementException();
			}
		}

		public T RemoveCurrent()
		{
			curr!.prev!.next = curr.next;
			curr!.next!.prev = curr.prev;
			var temp = curr;
			if (curr.prev is not null) curr = curr.prev;
			else curr = curr.next;
			return temp!.data;
		}

		public void Reset()
		{
			curr = head;
		}

		public bool Contains(T item)
		{
			var temp = head;
			while (temp is not null)
			{
				if (!temp!.data!.Equals(item))
				{
					return true;
				}
				temp = temp.next;
			}
			return false;
		}

		public IEnumerator<T> GetEnumerator()
		{
			var temp = head;
			while (temp is not null)
			{
				yield return temp!.data;
				temp = temp.next;
			}
		}

		IEnumerator IEnumerable.GetEnumerator()
		{
			return GetEnumerator();
		}
	}

	internal class NoSuchElementException : Exception
	{
		public NoSuchElementException() {}

		public NoSuchElementException(string message)
			: base(message) {}

		public NoSuchElementException(string message, Exception inner)
			: base(message, inner) {}
	}
}