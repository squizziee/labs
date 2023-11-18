#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <memory>
constexpr size_t START_CAPACITY = 5;
constexpr size_t BLOCK_SIZE = 3;

namespace custom
{
    class deque_out_of_bound_exception : public std::exception {
    public:
        const char* what () {
            return "Deque index is out of bound";
        }
    };

    template<typename T>
    class deque
    {
        template<typename U>
        class deque_iterator {
        private:
            deque<U>* dq;
            size_t counter;
            std::shared_ptr<U> ptr;
        public:
            deque_iterator(deque<U>* dq, size_t index) {
                this->dq = dq;
                counter = index;
                ptr = std::make_shared<U>(dq->at(counter));
            }

            std::shared_ptr<U>& operator++() {
                counter++;
                ptr = std::make_shared<U>(dq->at(counter));
                return ptr;
            }

            std::shared_ptr<U>& operator++(int) {
                auto temp = ptr;
                counter++;
                ptr = std::make_shared<U>(dq->at(counter));
                return temp;
            }

            std::shared_ptr<U> operator+(size_t offset) {
                return std::make_shared<U>(dq->at(counter + offset));
            }

            std::shared_ptr<U> operator-(size_t offset) {
                return std::make_shared<U>(dq->at(counter - offset));
            }

            std::shared_ptr<U>& operator+=(size_t offset) {
                counter += offset;
                ptr = std::make_shared<U>(dq->at(counter));
                return ptr;
            }

            std::shared_ptr<U>& operator-=(size_t offset) {
                counter -= offset;
                ptr = std::make_shared<U>(dq->at(counter));
                return ptr;
            }

            std::shared_ptr<U>& operator--() {
                counter--;
                ptr = std::make_shared<U>(dq->at(counter));
                return ptr;
            }

            bool operator==(const deque_iterator& other) {
                return *ptr == *other.ptr && counter == other.counter;
            }

            bool operator!=(const deque_iterator& other) {
                return *ptr != *other.ptr && counter != other.counter;
            }

            std::shared_ptr<U>& operator*() {
                return ptr;
            }

        };
    private:
        std::shared_ptr<std::shared_ptr<T[]>[]> arr;
        size_t curr_cell_back_index;
        size_t curr_block_back_index;
        size_t curr_cell_front_index;
        size_t curr_block_front_index;
        size_t size;
        size_t capacity;
        size_t left_space;
        size_t right_space;
    public:
        deque() {
            arr = std::shared_ptr<std::shared_ptr<T[]>[]>(new std::shared_ptr<T[]>[START_CAPACITY]);
            for (int i = 0; i < START_CAPACITY; ++i) {
                arr[i] = std::shared_ptr<T[]>(new T[BLOCK_SIZE]);
            }
            size = 0;
            capacity = START_CAPACITY;
        }

        void push_back(T&& data) {
            if (right_space == 0 && size != 0) {
                size_t old_capacity = capacity;
                resize();
                right_space += (capacity - old_capacity) / 2;
                left_space += (capacity - old_capacity) / 2;
                ia_head = capacity * BLOCK_SIZE / 2;
            }
            if (!size) {
                curr_block_front_index = START_CAPACITY / 2;
                curr_cell_front_index = 1;
                curr_block_back_index = START_CAPACITY / 2;
                curr_cell_back_index = 0;
                left_space = START_CAPACITY / 2;
                right_space = START_CAPACITY / 2;
                ia_head = capacity * BLOCK_SIZE / 2;
                //begin = std::make_shared<T>(arr[curr_block_back_index][curr_cell_back_index]);
            }
            if (curr_cell_back_index == BLOCK_SIZE - 1) {
                curr_block_back_index++;
                curr_cell_back_index = -1;
                right_space--;
            }
            curr_cell_back_index++;
            size++;
            arr[curr_block_back_index][curr_cell_back_index] = data;
        }

        void pop_back() {
            if (curr_cell_back_index == 0) {
                curr_block_back_index--;
                curr_cell_back_index = 3;
                right_space++;
            }
            curr_cell_back_index--;
            size--;
        }

        void push_front(T&& data) {
            if (left_space == 0 && size != 0) {
                size_t old_capacity = capacity;
                resize();
                right_space += (capacity - old_capacity) / 2;
                left_space += (capacity - old_capacity) / 2;
            }
            if (!size) {
                curr_block_front_index = START_CAPACITY / 2;
                curr_cell_front_index = 1;
                curr_block_back_index = START_CAPACITY / 2;
                curr_cell_back_index = 0;
                left_space = START_CAPACITY / 2;
                right_space = START_CAPACITY / 2;
            }
            if (curr_cell_front_index == 0) {
                curr_block_front_index--;
                curr_cell_front_index = 3;
                left_space--;
            }
            curr_cell_front_index--;
            size++;
            arr[curr_block_front_index][curr_cell_front_index] = data;
            ia_head = left_space * BLOCK_SIZE + curr_cell_front_index;
        }

        void pop_front() {
            if (curr_cell_front_index == BLOCK_SIZE - 1) {
                curr_block_front_index++;
                curr_cell_front_index = -1;
                left_space++;
            }
            curr_cell_front_index++;
            size--;
            ia_head = left_space * BLOCK_SIZE + curr_cell_front_index;
        }

        void push_back(T& data) {
            push_back(std::move(data));
        }

        void push_front(T& data) {
            push_front(std::move(data));
        }

        bool empty() {
            return size == 0;
        }

        size_t get_size() {
            return size;
        }

        void clear() {
            for (int i = 0; i < capacity; ++i) {
                arr[i].reset();
            }
            curr_cell_back_index = 0;
            curr_block_back_index = 0;
            curr_cell_front_index = 0;
            curr_block_front_index = 0;
            size = 0;
            capacity = START_CAPACITY;
            left_space = 0;
            right_space = 0;
            arr = std::shared_ptr<std::shared_ptr<T[]>[]>(new std::shared_ptr<T[]>[START_CAPACITY]);
            for (int i = 0; i < START_CAPACITY; ++i) {
                arr[i] = std::shared_ptr<T[]>(new T[BLOCK_SIZE]);
            }
        }

        deque_iterator<T> begin() {
            return deque_iterator<T>(this, 0);
        }

        deque_iterator<T> end() {
            return deque_iterator<T>(this, size - 1);
        }

        T& at(size_t index) {
            if (index >= size || index < 0)
                throw deque_out_of_bound_exception();
            return arr[ib_from_ia(ia_from_id(index))]
                [ic_from_ia(ia_from_id(index))];
        }

        T& operator[](size_t index) {
            return at(index);
        }

    private:
        size_t ia_head;

        size_t ia_from_id(size_t id) {
            return (id + ia_head) % (capacity * BLOCK_SIZE);
        }

        size_t ib_from_ia(size_t ia) {
            return ia / BLOCK_SIZE;
        }

        size_t ic_from_ia(size_t ia) {
            return ia % BLOCK_SIZE;
        }

        void resize() {
            auto old_capacity = capacity;
            auto newArr = std::shared_ptr<std::shared_ptr<T[]>[]>(new std::shared_ptr<T[]>[capacity = capacity * 2 + 1]);
            for (int i = 0; i < capacity; ++i) {
                newArr[i] = std::shared_ptr<T[]>(new T[BLOCK_SIZE]);
            }
            size_t start = (capacity - old_capacity) / 2;
            size_t oldCounter = 0;
            for (size_t i = start; i < start + old_capacity; i++) {
                newArr[i] = arr[oldCounter];
                //arr[oldCounter].reset();
                oldCounter++;
            }
            //arr.reset();
            arr = newArr;
            curr_block_back_index = curr_block_back_index + start;
            curr_block_front_index = curr_block_front_index + start;
            //newArr.reset();
        }
    };
}

#endif // DEQUE_H
