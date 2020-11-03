#include<iostream>

using namespace std;

/*
    Templates are not compiled 'cause they are not real code (they are inserted), 
    so even if you put some errors inside it
    we may have not any warning from the compiler.
    Templetes appears only when they are called from someone else: in practicse, the
    compiler copies and pastes the templated methods, removes the template specifying
    the type of the input taken from the argument of the functions.
    During compile-time the compiler add the pieces of codes where templates are used.
*/

template<typename TT, int N>
class Array{

    private:

    TT m_Array[N];

    public:

    int const&& GetSize() const {return N;}
};

/*
class Array{

    private:

    double m_Array[5];

    public:

    int const& GetSize() const {return 5;}
};
*/


template<typename T>
void printf(const T& other) {
    cout << other << "\n";
}

/*
void printf(const string& other) {
    cout << other << "\n";
}
*/

int main(){

    printf<string>("hello");
    printf(2.3);

    Array<double, 5> array;
    cout << "array size = " << array.GetSize() << endl;

    int a = 5;
    int*p1 = &a;

    int *p2 = &(*p1);


    return 0;
}