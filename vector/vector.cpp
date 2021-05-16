#include <iostream>
#include <utility>
#include <new>
#include <exception>
#include <algorithm>

template<typename T>
class myvector final
{
public:
    myvector();
    myvector(int cap);
    myvector(const myvector& rhs);
    myvector(myvector&& rhs) noexcept;
    myvector& operator=(const myvector& rhs);
    myvector& operator=(myvector&& rhs) noexcept;
    ~myvector();

    auto begin() const;
    auto end() const;
    auto begin();
    auto end();  
    void push_back(const T& val);

private:
    int size_ = 0;
    int capacity_ = 0;
    T* data_ = nullptr;

    template<typename Arg>
    void emplace_back(Arg&& arg);
};


int main()
{
    myvector<int> v(2);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    return 0;
}

template<typename T>
myvector<T>::myvector(): capacity_(10), data_(new(std::nothrow) T [capacity_])
{
    if (data_ == nullptr)
    {
        std::cout << "Can't allocate memory\n";
        capacity_ = 0;
    }
}

template<typename T>
myvector<T>::myvector(int cap): capacity_(cap), data_(new(std::nothrow) T [capacity_])
{
    if (data_ == nullptr)
    {
        std::cout << "Can't allocate memory\n";
        capacity_ = 0;
    }
}

template<typename T>
myvector<T>::myvector(const myvector& rhs) : size_(rhs.size_), capacity_(rhs.capacity_)
{
    try
    {
        data_ = new T[capacity_];
        std::copy(rhs.begin(), rhs.begin() + rhs.size_, begin());
    }
    catch (...)
    {
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
    }
}

template<typename T>
myvector<T>::myvector(myvector&& rhs) noexcept: size_(rhs.size_), capacity_(rhs.capacity_), data_(rhs.data_)
{ 
    rhs.size_ = 0;
    rhs.capacity_ = 0;
    rhs.data_ = nullptr;
}

template<typename T>
myvector<T>& myvector<T>::operator=(const myvector& rhs)
{
    if (rhs == *this)
    {
        return *this;
    }

    delete[] data_;
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    try
    {   
        data_ = new T[capacity_];
        std::copy(rhs.begin(), rhs.end(), begin());
    }
    catch (...)
    {
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
    }

    return *this;
}

template<typename T>
myvector<T>& myvector<T>::operator=(myvector&& rhs) noexcept
{
    if (&rhs == this)
    {
        return *this;
    }

    delete[] data_;
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    data_ = rhs.data_;
    rhs.size_ = 0;
    rhs.capacity_ = 0;
    rhs.data_ = nullptr;
    return *this;
}

template<typename T>
myvector<T>:: ~myvector()
{
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
}

template<typename T>
auto myvector<T>::begin() const
{
    return data_;
}

template<typename T>
auto myvector<T>::begin()
{
    return data_;
}

template<typename T>
auto myvector<T>::end() const
{
    return data_[size_ - 1];
}

template<typename T>
auto myvector<T>::end()
{
    return data_[size_ - 1];
}

template<typename T>
void myvector<T>:: push_back(const T& val)
{
    if (size_ == capacity_)
    {
        myvector tmp(size_ * 2 + 1); 
        while (tmp.size_ < size_)
        {
            tmp.emplace_back(std::move(data_[tmp.size_]));
        }
        tmp.emplace_back(std::move(val));
        std::swap(*this, tmp);
    }
}

template<typename T>
template<typename Arg>
void myvector<T>::emplace_back(Arg&& arg)
{
    data_[size_] = std::forward<Arg>(arg);
    size_++;
}