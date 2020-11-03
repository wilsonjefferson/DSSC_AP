#include<iostream>

// compile with -Wall -Wextra -g, run with valgrind --leak-check=full -v ./a.out.

using namespace std;

class Entity{

    private:
    
    int a;
    int b;
    int *c;

    public:

    Entity() = default;

    Entity (int& _a, int& _b, int* _c) : a{_a}, b{_b}, c{_c} { // assigned during compilation (no in run time 'cause it's const)
        cout << "ctor_overloaded_1\t";
    } 

    Entity (const int& _a, const int& _b, int* const _c) : a{_a}, b{_b}, c{_c} {
        cout << "ctor_overloaded_2\t";
    }
    

    Entity (int&& _a, int&& _b, int*& _c) : a{_a}, b{_b}, c{_c} {
        // int*& it's a pointer to the reference of an lvalue (so, _c already exist)

        cout << "create_move_ctor_1\t";
        _a = 0;
        _b = 0;
        _c = nullptr;
    }

    Entity (int&& _a, int&& _b, int*&& _c) : a{_a}, b{_b}, c{_c} {
        // int*&& it's a pointer to the reference of an rvalue (so, _c is a temp obj)

        cout << "create_move_ctor_2\t";
        _a = 0;
        _b = 0;
        _c = nullptr;
    }


    Entity (const Entity& other) noexcept {
        cout << "copy_ctor\t";
        this->a = other.a;
        this->b = other.b;
        this->c = other.c;
    }

    Entity (Entity&& other) noexcept {
        cout << "move_ctor\t";
        this->a = other.a;
        this->b = other.b;
        this->c = other.c;

        // other left in constant state
        other.a = 0; 
        other.b = 0;
        other.c = nullptr;
    }

    Entity& operator= (Entity& other) noexcept {

        cout << "copy_assigment_ctor\t";
        if(this == &other) return *this;
        this->a = other.a;
        this->b = other.b;
        this->c = other.c;

        // other left in constant state
        other.a = 0; 
        other.b = 0;
        other.c = nullptr;

        return *this;
    }

    Entity& operator= (Entity&& other) noexcept {

        cout << "move_assigment_ctor\t";
        if(this == &other) return *this;
        this->a = other.a;
        this->b = other.b;
        this->c = other.c;

        // other left in constant state
        other.a = 0; 
        other.b = 0;
        other.c = nullptr;

        return *this;
    }

    ~Entity(){
        //cout << "dector\t";
        a = 0;
        b = 0;
        c = nullptr;
    }

    const int& GetA() const {
        return a;
    }    

    const int& GetB() const {
        return b;
    }    
};


int main(){

    const int a_0 = 1;
    const int b_0 = 2;
    int c_0 = 3;
    int* const p_0 = &c_0;

    int a_1 = 1;
    int b_1 = 2;
    int* p_1 = &c_0;

    cout << "e_0: "; Entity e_0{a_0, a_0, p_0}; cout << endl;
    cout << "e_1: "; Entity e_1{a_1, b_1, p_1}; cout << endl;

    int *p_2 = nullptr;
    cout << "e_3: "; Entity e_3{move(Entity{1, 2, nullptr})}; cout << endl;
    //cout << "e_3: "; Entity e_3{Entity{1, 2, nullptr}}; cout << endl;

    cout << "e_4: "; Entity e_4{move(Entity{1, 2, p_2})}; cout << endl;
    cout << "e_3: "; e_3 = e_4; cout << endl;
    cout << "e_0: "; e_0 = move(e_1); cout << endl;
    cout << "e_1: "; e_1 = Entity{2, 3, nullptr}; cout << endl;
    cout << "e_1 values: a = " << e_1.GetA() << " b = " << e_1.GetB() << "\n";
    cout << "e_4: "; e_4 = Entity{1, 2, nullptr}; cout << endl;
    cout << "e_5: "; Entity e_5{e_3}; cout << endl;


    return 0;
}
