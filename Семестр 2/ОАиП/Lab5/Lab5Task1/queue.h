#include <memory>

namespace custom
{
    template<typename T>
    class queue
    {
    protected:
        template<typename N>
        struct Node
        {
            std::shared_ptr<Node<N>> next;
            std::shared_ptr<Node<N>> prev;
            N data;

            Node(N& _data)
            {
                data = _data;
            }

            Node(std::shared_ptr<Node<N>> _next,
                std::shared_ptr<Node<N>> _prev,
                N _data)
            {
                data = _data;
                next = _next;
                prev = _prev;
            }

            Node(std::shared_ptr<Node<N>> _next,
                N _data)
            {
                data = _data;
                next = _next;
            }
        };

        std::shared_ptr<Node<T>> qFront;
        std::shared_ptr<Node<T>> qBack;
        size_t size = 0;

    public:
        void push(T& data)
        {
            push(std::move(data));
        }

        void push(T&& data) {
            if (!qFront)
            {
                qFront = std::make_shared<Node<T>>(
                    Node<T>(data));
                qBack = qFront;
            }
            else
            {
                qBack->prev = std::make_shared<Node<T>>(Node<T>(qBack, data));
                auto tmp = qBack;
                qBack = qBack->prev;
                qBack->next = tmp;
                tmp.reset();
            }
            size++;
        }

        T& front() {
            return qFront->data;
        }

        T& back() {
            return qBack->data;
        }

        void pop() {
            if (!qFront->prev)
            {
                qFront.reset();
                qBack.reset();
                size--;
                return;
            }
            if (!qFront->prev->prev)
            {
                qBack = qFront;
            }
            qFront = qFront->prev;
            size--;
        }

        bool empty() {
            return size == 0;
        }

        void remove_range(size_t begin, size_t end) {
            if (end <= begin) return;
            if (begin == 0)
            {
                int count = 0;
                auto anchor_end = qFront;
                while (count < end)
                {
                    anchor_end = anchor_end->prev;
                    count++;
                }
                qFront = anchor_end;
                qFront->next.reset();
            }
            else if (end == size)
            {
                int count = 0;
                auto anchor_begin = qFront;
                while (count < begin)
                {
                    anchor_begin = anchor_begin->prev;
                    count++;
                }
                qBack = anchor_begin;
                qBack->prev.reset();
            }
            else
            {
                int count = 0;
                auto anchor_begin = qFront;
                while (count < begin)
                {
                    anchor_begin = anchor_begin->prev;
                    count++;
                }
                anchor_begin = anchor_begin->next;
                count = 0;
                auto anchor_end = qFront;
                while (count < end)
                {
                    anchor_end = anchor_end->prev;
                    count++;
                }
                anchor_begin->prev = anchor_end;
                anchor_end->next = anchor_begin;
            }
            size -= end - begin;
        }

        void insert(size_t start, custom::queue<T>& to_insert) {
            auto q = to_insert;
            to_insert.clear();
            if (start == 0)
            {
                q.qBack->prev = qFront;
                qFront->next = q.qBack;
                qFront = q.qFront;
            }
            else if (start == custom::queue<T>::size)
            {
                q.qFront->next = qBack;
                qBack->prev = q.qFront;
                qBack = q.qBack;
            }
            else
            {
                int count = 0;
                auto anchor = qFront;
                while (count < start)
                {
                    anchor = anchor->prev;
                    count++;
                }
                anchor = anchor->next;
                q.qFront->next = anchor;
                q.qBack->prev = anchor->prev;
                anchor->prev->next = q.qBack;
                anchor->prev = q.qFront;
            }
            size += q.size;
        }

        void clear() {
            qFront.reset();
            qBack.reset();
            size = 0;
        }

        size_t get_size() {
            return size;
        }
    };

    template<typename T>
    class insertion_queue : public queue<T>
    {
    public:
        void insert(size_t start, T data)
        {
            if (start == 0) {
                auto newNode = std::make_shared<custom::queue<T>::template Node<T>>(data);
                newNode->prev = custom::queue<T>::qFront;
                custom::queue<T>::qFront->next = newNode;
                custom::queue<T>::qFront = custom::queue<T>::qFront->next;
                custom::queue<T>::size++;
                return;
            }
            if (start == custom::queue<T>::size) {
                auto newNode = std::make_shared<custom::queue<T>::template Node<T>>(data);
                newNode->next = custom::queue<T>::qBack;
                custom::queue<T>::qBack->prev = newNode;
                custom::queue<T>::qBack = custom::queue<T>::qBack->prev;
                custom::queue<T>::size++;
                return;
            }
            int count = 0;
            auto anchor = custom::queue<T>::qFront;
            while (count < start)
            {
                anchor = anchor->prev;
                count++;
            }
            auto newNode = std::make_shared<custom::queue<T>::template Node<T>>(data);
            newNode->next = anchor->next;
            newNode->prev = anchor;
            anchor->next->prev = newNode;
            anchor->next = newNode;
            custom::queue<T>::size++;
        }


    };

}
