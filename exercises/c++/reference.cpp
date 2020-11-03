#include <iostream>

void increment(int value){ // want a lvalue or rvalue
    value++;
    std::cout << "(value) value = " << value << "\n";
}

void increment(int& value){ // want a reference to an lvalue
    value++;
    std::cout << "(reference) value = " << value << "\n";
}

void print_value(const int& value){ // want a lvalue or rvalue
    std::cout << "value = " << value << "\n";
}

void increment(int* value){
    (*value)++;
    std::cout << "(pointer) value = " << *value << "\n";
}

int main(){

    int a = 5;
    int c = 8;

    int& b = a; 
    // b is a reference to a, it is an alias, so same object with different names
    // moreover b is not a real variable it's a reference to another object 
    // (so here we have just two variables: a and c).

    increment(std::move(a)); // from lvalue to rvalue -> go for increment(int value);
    // increment(a); // ERROR: doens't know which increment have to be called
    std::cout << "a = " << a << "\n";

    increment(&a); // pass the address, so need a pointer -> go for increment(int* value);
    std::cout << "a = " << a << "\n";

    b = c; // a = 8, c = 8 so b is not a alias for c but just copy the value of c in a

    std::cout << "--- check ---\n\n";

    std::cout << "address a = " << &a << "\n";
    std::cout << "address b = " << &b << "\n";
    std::cout << "address c = " << &c << "\n";

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n";

    return 0;
}