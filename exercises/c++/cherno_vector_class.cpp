#include<iostream>
#include<memory>
#include<assert.h>

template<typename T>
class Vector
{

    private:

    T* array{nullptr}; // array of type T
    std::size_t size{0}; // actual size
    std::size_t capacity{0}; // dimension of the array

    private:

    /**
     * REALLOC
     * 
     * @brief this function allow to create another array if the main one
     *        is stacked, and so we have to move to a bigger one
     * 
    */
    void realloc(const std::size_t& _capacity)
    {   
        T* tmp_block = new T[_capacity];
        
        if(_capacity < size){size = _capacity;}
        for(std::size_t i = 0; i < size; ++i) {tmp_block[i] = array[i];}
        
        delete[] array;
        array = tmp_block;
        capacity = _capacity;
    }

    public:

    Vector () {realloc(2);} /** < default ctor */
    Vector (const std::size_t& _capacity) : capacity{_capacity}, array{new T[_capacity]} {}
    Vector (std::size_t&& _capacity) : capacity{_capacity}, array{new T[_capacity]} {}

    /** < deep copy ctor */
    Vector (const Vector& other) : capacity{other.capacity}, size{other.size}, array{new T[other.capacity]}
    {for(std::size_t i = 0; i < size; ++i){array[i] = other.array[i];}}

    /** < move ctor */
    Vector (Vector&& other) : capacity{std::move(other.capacity)}, size{std::move(other.size)}, array{std::move(other.array)}
    {other.capacity = 0; other.size = 0; other.array = nullptr;}

    public:

    Vector& operator= (const Vector& other) // copy assignment operator
    {
        if(this == &other) {return *this;}

        delete[] array; // free the main memory

        Vector tmp{other}; // deep copy of a tmp Vector: other is untouched!

        array = std::move(tmp.array); // move tmp array to the main array
        capacity = std::move(tmp.capacity); // move tmp capacity to the main capacity
        size = std::move(tmp.size); // move tmp size to the main size

        //--- leave tmp to a defined state ---//
        tmp.array = nullptr;
        tmp.capacity = 0;
        tmp.size = 0;

        return *this;
    }

    Vector& operator= (Vector&& other) // move assignment operator
    {
        if(this == &other) {return *this;}
        
        delete[] array;

        array = std::move(other.array);
        capacity = std::move(other.capacity);
        size = std::move(other.size);

        other.array = nullptr;
        other.capacity = 0;
        other.size = 0;

        *this;
    }

    const T& operator[] (const std::size_t& idx) const
    {
        assert(idx >= 0 || idx < size); // idx is not out of bound
        return array[idx];
    }

    T& operator[] (std::size_t& idx)
    {
        assert(idx >= 0 || idx < size); // idx is not out of bound

        if(size >= capacity && idx >= size)
        {
            realloc(capacity + capacity / 2);
            ++size;
        }
        
        return array[idx];    
    }    

    T& operator[] (std::size_t&& idx)
    {
        assert(idx >= 0 || idx < size); // idx is not out of bound

        if(size >= capacity && idx >= size)
        {
            realloc(capacity + capacity / 2);
            ++size;
        }
        
        return array[idx];    
    }

    friend Vector operator+ (const Vector& v1, const Vector& v2)
    {
        assert(v1.size == v2.size); // check: v1 and v2 have same size (may different capacity)

        Vector tmp{v1.size};
        tmp.size = v1.size;
        for(std::size_t i = 0; i < tmp.size; ++i){tmp[i] = v1[i] + v2[i];}
        
        return tmp; // return by lvalue 'cause tmp will be out-of-scope...
    }

    friend bool operator== (const Vector& v1, const Vector& v2)
    {
        assert(v1.size == v2.size); // check: v1 and v2 same size

        std::size_t i = 0;
        bool check = true; 

        while((i < v1.size) && check)
        {
            if(v1[i] != v2[i]){check = false;}
            ++i;
        }

        return check;
    }

    friend std::ostream& operator<< (std::ostream& os, const Vector& other) 
    {
        os << "capacity: " << other.capacity << std::endl;
        os << "size: " << other.size << std::endl;
        os << "data: ";
        for(std::size_t i = 0; i < other.size_of(); ++i){os << other[i] << " ";}
        return os;
    }

    public:

    void push_back (const T& value) 
    {
        if(size >= capacity){realloc(capacity + capacity / 2);}
        
        array[size] = value;
        ++size;
    }

    const std::size_t& size_of () const
    {return size;}

    const std::size_t& capacity_of () const
    {return capacity;}

    const T* begin() const
    {
        assert(capacity > 0); // Vector is not empty
        return &array[0];
    }

    T* begin()
    {
        assert(capacity > 0); // Vector is not empty
        return &array[0];
    }

    const T* end() const
    {
        assert(capacity > 0); // Vector is not empty
        return &array[size];
    }

    T* end()
    {
        assert(capacity > 0); // Vector is not empty
        return &array[size];
    }
};


int main()
{

    Vector<int> vec_0{2}; // parametrized ctor
    std::cout << "data capacity: " << vec_0.capacity_of() << "\n";
    std::cout << "data size: " << vec_0.size_of() << "\n";

    vec_0[6] = 1;
    vec_0[1] = 2;

    std::cout << "\nvec_0\n" << vec_0 << std::endl;

    Vector<int> vec_1{}; // default ctor
    
    vec_1.push_back(1);
    vec_1.push_back(2);
    vec_1.push_back(3);
    
    std::cout << "\nvec_1\n" << vec_1 << std::endl;

    Vector<int> vec_2{vec_1}; // copy ctor
    vec_2[1] = 19;
    std::cout << "\nvec_2\n" << vec_2 << std::endl;

    vec_0 = vec_1; // copy assignment ctor
    std::cout << "\nvec_0\n" << vec_0 << std::endl;
    std::cout << "\nvec_1\n" << vec_1 << std::endl;

    if(vec_0 == vec_1)
    {
        std::cout << "they have same info\n";
    }
    else
    {
        std::cout << "they have different into\n";
    }

    Vector<int> vec_3{vec_0 + vec_1};
    std::cout << "\nvec_3\n" << vec_3 << std::endl;

    vec_0 = vec_1 + vec_2;
    std::cout << "\nvec_0\n" << vec_0 << std::endl;

    return(0);
}