#include <iostream>
#include <memory>

template<typename T>
class Vector
{

    private:

    std::unique_ptr<T[]> array;
    std::size_t size;
    
    public:

    Vector () {std::cout << "default ctor\n";}

    Vector (const std::size_t& _size) : array{new T[_size]}, size{_size} 
    {std::cout << "ctor overloaded 1\n";}

    Vector (std::size_t&& _size) : array{new T[_size]}, size{_size} 
    {std::cout << "ctor overloaded 2\n";}

    Vector (std::size_t&& _size, T* _array) : array{std::move(_array)}, size{_size} 
    {std::cout << "ctor overloaded 3\n";}

    Vector (const Vector& other) : array{new T[other.size]}, size{other.size}
    {
        std::cout << "copy ctor\n";
        for(std::size_t i = 0; i < size; i++) {array[i] = other.array[i];}
    }

    Vector (Vector&& other) : array{std::move(other.array)}, size{std::move(other.move)}
    {std::cout << "move ctor\n";}

    ~Vector () {std::cout << "desctor\n";}

    public:

    Vector& operator= (const Vector& other)
    {
        std::cout << "copy assignment operator\n";
        if(this == &other) {return *this;}

        array.reset(); // clear my memory
        Vector tmp = other; // call deep copy ctor
        (*this) = std::move(tmp); // move assignment
        size = std::move(tmp.size); // move size
        
        return *this;
    }

    Vector& operator= (Vector&& other) 
    {
        std::cout << "move assignment operator\n";
        if(this == &other) {return *this;}
        size = std::move(other.size);
        array = std::move(array);

        return *this;
    }

    const T& operator[] (const std::size_t& idx) const
    {
        std::cout << "const lvalue operator[]\n";
        if(idx > 0 && idx < size)
        {
            return array[idx];
        }
        else
        {
            return array[size-1];
        }
    }

    T& operator[] (const std::size_t& idx)
    {
        std::cout << "lvalue operator[]\n";
        if(idx > 0 && idx < size)
        {
            return array[idx];
        }
        else
        {
            return array[size-1];
        }
    }    

    const T& operator[] (std::size_t&& idx) const
    {
        std::cout << "const rvalue operator[]\n";
        if(idx >= 0 && idx < size)
        {
            return array[idx];
        }
        else
        {
            return array[size-1];
        }
    }

    T& operator[] (std::size_t&& idx)
    {
        std::cout << "rvalue operator[]\n";
        if(idx >= 0 && idx < size)
        {
            return array[idx];
        }
        else
        {
            return array[size-1];
        }
    }

    Vector<T> operator+ (const Vector& v1, const Vector& v2)
    {
        std::cout << "+ operator\n";

        assert(v1.size_of() == v2.size_of());
        
        Vector<T> sum{v1.size_of()};
        for(std::size_t i = 0; i < sum.size_of(); ++i)
        {sum[i] = v1[i] + v2[i];}

        return sum;
    }

    public:

    const std::size_t& size_of() const noexcept
    {
        std::cout << "size function\n";
        return this->size;
    }

    friend std::ostream& operator<< (std::ostream& os, const Vector<T>& other) noexcept
    {
        for(std::size_t i = 0; i < other.size; ++i)
        {os << "v[" << i << "] = " << other[i] << std::endl;}

        return os;
    }
};


int main (){

    Vector<int> arr_0{};
    Vector<int> arr_1{10};

    const int idx_0 = 1;
    int val_0 = 5;

    arr_1[0] = 5;
    arr_1[idx_0] = val_0;

    for(auto i = 0u; i < arr_1.size_of(); ++i){arr_1[i] = i;}
    std::cout << arr_1 << std::endl;

    Vector<int> arr_2{arr_1};
    std::cout << arr_2 << std::endl;

    arr_0 = arr_1;
    int* p_0 = new int[10];
    arr_0 = Vector<int>{10, p_0};

    return 0;
}