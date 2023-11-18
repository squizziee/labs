#pragma once

class UPointer {
    char* ptr;
    size_t size_;
public:
    operator bool() const {
        return ptr != nullptr;
    }

    UPointer() : ptr(nullptr), size_(0) {}
    UPointer(char* ptr, size_t size) : ptr(ptr), size_(size) {}

    ~UPointer()
    {
        delete[] ptr;
    }

    UPointer(UPointer&& other) : ptr(other.ptr), size_(other.size_)
    {
        other.ptr = nullptr;
        other.size_ = 0;
    }

    UPointer(const UPointer& other) = delete;

    UPointer& operator=(UPointer& other) = delete;

    UPointer& operator=(UPointer&& other) noexcept
    {
        if (&other == this)
            return *this;

        delete[] ptr;

        ptr = other.ptr;
        size_ = other.size_;
        other.ptr = nullptr;
        other.size_ = 0;

        return *this;
    }

    char* release() {
        char* releasedPtr = ptr;
        ptr = nullptr;
        size_ = 0;
        return releasedPtr;
    }

    void reset(char* newPtr = nullptr, size_t newSize = 0) {
        char* oldPtr = ptr;
        ptr = newPtr;
        size_ = newSize;
        delete[] oldPtr;
    }

    char& operator[](int index) const {
        return ptr[index];
    }

    char* get() const
    {
        return ptr;
    }

    bool is_null() const {
        return ptr == nullptr;
    }

    size_t size() const {
        return size_;
    }
};

UPointer make_unique_array(size_t size)
{
    return UPointer(new char[size](), size);
}