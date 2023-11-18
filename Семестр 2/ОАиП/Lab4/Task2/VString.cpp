#pragma once
#include "UPointer.h"
#include <algorithm>
#include <string>

char* cst_strcat(char* s1, const char* s2);
char* cst_strncat(char* s1, const char* s2, size_t n);
size_t cst_strlen(const char* s);
void* cst_memcpy(void* s1, const void* s2, size_t n)
{
    char* dest = static_cast<char*>(s1);
    const char* src = static_cast<const char*>(s2);

    for (size_t i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }

    return s1;
}
int cst_strcmp(const char* s1, const char* s2)
{
    while (*s1 != '\0' || *s2 != '\0') {
        if (*s1 != *s2) {
            return (*s1 < *s2) ? -1 : 1;
        }
        s1++;
        s2++;
    }
    return 0;
}
char* cst_strcpy(char* s1, const char* s2)
{
    char* dest = s1;
    while (*s2 != '\0')
    {
        *dest++ = *s2++;
    }
    *dest = '\0';
    return s1;
}

class cst_string
{
    UPointer data;

public:
    cst_string() : data(make_unique_array(1))
    {
        reserve(1000);
        data[0] = '\0';
    }

    cst_string(const char* str) : data(make_unique_array(strlen(str) + 1000))
    {
        reserve(1000);
        cst_strcpy(data.get(), str);
    }

    cst_string(const cst_string& other) : data(make_unique_array(other.size() + 1000))
    {
        reserve(1000);
        cst_strcpy(data.get(), other.c_str());
    }

    cst_string(cst_string&& other) : data(std::move(other.data)) {}

    ~cst_string() {}

    cst_string& operator=(const char* str)
    {
        data = make_unique_array(cst_strlen(str) + 1000);
        //reserve(10000);
        cst_strcpy(data.get(), str);
        return *this;
    }

    cst_string& operator=(const cst_string& other)
    {

        if (this != &other)
        {
            reserve(1000);
            data = make_unique_array(other.size() + 1000);
            cst_strcpy(data.get(), other.c_str());
        }
        return *this;
    }

    cst_string& operator=(cst_string&& other)
    {
        if (this != &other)
        {
            data = std::move(other.data);
        }
        return *this;
    }

    char& operator[](size_t index)
    {
        return data[index];
    }

    const char& operator[](size_t index) const
    {
        return data[index];
    }

    const char* c_str() const
    {
        return data.get();
    }

    char* c_str()
    {
        return data.get();
    }

    size_t size() const
    {
        return data.size() - 1;
    }

    bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        data.reset(make_unique_array(1).release());
        data[0] = '\0';
    }

    void reserve(size_t new_capacity);

    cst_string& operator+=(const cst_string& str)
    {
        size_t old_size = size();
        data = make_unique_array(old_size + str.size() + 1);
        cst_strcpy(data.get(), c_str());
        cst_strcpy(data.get() + old_size, str.c_str());
        return *this;
    }

    friend cst_string operator+(cst_string l, const cst_string& r)
    {
        l += r;
        return l;
    }

    friend bool operator==(const cst_string& l, const cst_string& r)
    {
        return cst_strcmp(l.c_str(), r.c_str()) == 0;
    }

    friend bool operator!=(const cst_string& l, const cst_string& r)
    {
        return !(l == r);
    }

    friend bool operator<(const cst_string& l, const cst_string& r)
    {
        return cst_strcmp(l.c_str(), r.c_str()) < 0;
    }

    friend bool operator<=(const cst_string& l, const cst_string& r)
    {
        return cst_strcmp(l.c_str(), r.c_str()) <= 0;
    }

    friend bool operator>(const cst_string& l, const cst_string& r)
    {
        return cst_strcmp(l.c_str(), r.c_str()) > 0;
    }

    friend bool operator>=(const cst_string& l, const cst_string& r)
    {
        return cst_strcmp(l.c_str(), r.c_str()) >= 0;
    }
};

int cst_strcoll(const char* s1, const char* s2)
{
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 != *s2)
        {
            unsigned char c1 = (unsigned char)*s1;
            unsigned char c2 = (unsigned char)*s2;

                if (tolower(c1) != tolower(c2))
                {
                    return tolower(c1) - tolower(c2);
                }
                else
                {
                    return c1 - c2;
                }
        }

        s1++;
        s2++;
    }

    return *s1 - *s2;
}


void cst_string::reserve(size_t new_capacity)
{
    if (new_capacity <= size())
    {
        return;
    }

    UPointer new_data = make_unique_array(new_capacity);
    cst_memcpy(new_data.get(), data.get(), size() + 1);
    data = std::move(new_data);
}

size_t cst_strlen(const char* s)
{
    size_t len = 0;
    while (*s != '\0')
    {
        s++;
        len++;
    }
    return len;
}

char* cst_strncpy(char* s1, const char* s2, size_t n)
{
    size_t i;
    for (i = 0; i < n && s2[i] != '\0'; i++)
        s1[i] = s2[i];
    for (; i < n; i++)
        s1[i] = '\0';

    return s1;
}

char* cst_strtok(char* s1, const char* s2)
{
    static char* last_token = NULL;
    char* token = NULL;

    if (s1 == NULL)
    {
        s1 = last_token;
    }

    s1 += strspn(s1, s2);

    if (*s1 != '\0')
    {
        token = s1;
        s1 = strpbrk(token, s2);
        if (s1 != NULL)
        {
            *s1 = '\0';
            last_token = s1 + 1;
        }
        else
        {
            last_token = NULL;
        }
    }

    return token;
}

size_t cst_strxfrm(char* s1, const char* s2, size_t n)
{
    size_t len = cst_strlen(s2);

    if (len < n)
    {
        cst_strcpy(s1, s2);
        return len;
    }
    else
    {
        cst_strncpy(s1, s2, n - 1);
        s1[n - 1] = '\0';
        return n - 1;
    }
}

int cst_strncmp(const char* s1, const char* s2, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (s1[i] != s2[i])
        {
            return (s1[i] < s2[i]) ? -1 : 1;
        }
        else if (s1[i] == '\0')
        {
            return 0;
        }
    }

    return 0;
}

void* cst_memset(void* s, int c, size_t n)
{
    unsigned char* p = (unsigned char*)s;
    unsigned char v = (unsigned char)c;

    for (size_t i = 0; i < n; i++)
    {
        p[i] = v;
    }

    return s;
}

void* cst_memmove(void* s1, const void* s2, size_t n)
{
    char* dest = static_cast<char*>(s1);
    const char* src = static_cast<const char*>(s2);

    if (src < dest && src + n > dest)
    {
        src += n;
        dest += n;
        while (n--)
        {
            *(--dest) = *(--src);
        }
    }
    else
    {
        while (n--)
        {
            *(dest++) = *(src++);
        }
    }

    return s1;
}

char* cst_strncat(char* s1, const char* s2, size_t n)
{
    size_t s1_length = cst_strlen(s1);
    size_t i;

    for (i = 0; i < n && s2[i] != '\0'; i++)
    {
        s1[s1_length + i] = s2[i];
    }

    s1[s1_length + i] = '\0';

    return s1;
}

int cst_memcmp(const void* s1, const void* s2, size_t n)
{
    const unsigned char* p1 = static_cast<const unsigned char*>(s1);
    const unsigned char* p2 = static_cast<const unsigned char*>(s2);

    for (size_t i = 0; i < n; i++)
    {
        if (p1[i] < p2[i])
        {
            return -1;
        }
        else if (p1[i] > p2[i])
        {
            return 1;
        }
    }

    return 0;
}

char* cst_strcat(char* s1, const char* s2)
{
    char* p = s1;
    while (*p != '\0')
    {
        p++;
    }
    while (*s2 != '\0')
    {
        *p = *s2;
        p++;
        s2++;
    }

    *p = '\0';
    /* UPointer new_data = make_unique_array(cst_strlen(s1) + cst_strlen(s2) + 1);
     cst_memcpy(new_data.get(), s1, cst_strlen(s1) + 1);
     *s1 = std::move(new_data);*/
    return s1;
}

char* cst_strerror(int errnum)
{
    char* msg;

    switch (errnum) {
    case EACCES:
        msg = (char*)"Permission denied";
        break;
    case EEXIST:
        msg = (char*)"File exists";
        break;
    case ENOENT:
        msg = (char*)"No such file or directory";
        break;

    default:
        msg = (char*)"Unknown error";
        break;
    }

    return msg;
}