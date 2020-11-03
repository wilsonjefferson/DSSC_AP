#include <iostream>

class Entity{

    private:
        int  m_X, m_Y;
        int* m_Z{&m_X};

    public:

        void Set_Y(int y) {
            m_Y = y;
        };

        // return and int and cannot modify class variable;
        int Get_X() const {
            // m_X = 5; // ERROR: this method is const, you cannot modify CLASS variables;
            return m_X;
        };

        int Get_X() {
            return m_X;
        }

        // return an unchangeble pointer and cannot modify  class variables;
        const int* const Get_Z() const {
            return m_Z;
        };

        const int* const Set_Z(const int* const z){

            std::cout << "address z = " << z << std::endl;
            std::cout << "value of z = " << *z << "\n";

            *m_Z = *z;

            std::cout << "address m_Z = " << m_Z << std::endl;
            std::cout << "value of m_Z = " << *m_Z << std::endl;

            return m_Z;
        };
};

void print_entity(Entity& e){
    // const object can call only const function 'cause we are sure they will not change
    // the content of the object itself.
    // e.Set_Y(2); // ERROR: cannot change the content of a constant object
    std::cout << e.Get_X() << std::endl;
};

int main(){

    const int MAX_AGE = 90; // const value

    int* a = new int; // variable
    *a = 2;
    std::cout << "a = " << *a << std::endl;

    const int* b = new int; // assigned is const
    int const* c = new int; // same of b

    // *b = 4; // ERROR: we cannot change the value pointed
    b = (int*)&MAX_AGE; // we can change the address 
    std::cout << "b = " << *b << std::endl;

    int* const d = (int*)&MAX_AGE; // CHEATING: we ar able to modify the value of MAX_AGE
    // d = (int*)&MAX_AGE; // ERROR: we cannot change the address
    *d = 4; // we can change the value pointed
    std::cout << "d = " << *d << std::endl;

    const int* const e = new int; // this pointer is unchangeble (it's totally const)
    // *e = 5; // ERROR: we cannot change the value pointed
    // e = (int*)&MAX_AGE; // ERROR: we cannot change the address
    std::cout << "e = " << *e << std::endl;

    // if const is before '*' than you cannot change the value pointed but you can change the address
    // if const is after '*' than you cannot change the address but you can change the value pointed

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

    Entity ciccio{};
    ciccio.Set_Z(z);

    return 0;
}
