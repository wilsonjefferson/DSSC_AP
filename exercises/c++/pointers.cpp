#include <iostream>

int main(){

    const int f = 5; // const value, cannot change from f
    int* p_1_f; // changeble pointer
    const int* const z = &f; // unchangeble pointer

    p_1_f = (int*)z; // type cast of z
    *p_1_f = 10;

    const int* p_2_f = &f; // const value, cannot change the pointed value from this pointer

    std::cout << "address f = " << &f << "\n";
    std::cout << "address z = " << z << "\n";
    std::cout << "address p_1_f = " << p_1_f << "\n\n";
    std::cout << "address p_2_f = " << p_2_f << "\n\n";
    
    std::cout << "value f = " << f << "\n";
    std::cout << "value z = " << *z << "\n";
    std::cout << "value p_1_f = " << *p_1_f << "\n";
    std::cout << "value p_2_f = " << *p_2_f << "\n";
    
    // different values but same address...

    return 0;
}