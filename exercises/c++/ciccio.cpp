#include <iostream>

class Pietro
{
    public:

    int* var = new int;

    public:

    Pietro(){}
    ~Pietro(){std::cout << "destructor\n";}
};

int main()
{

    Pietro* p_1;

        {
            Pietro* p_0 = new Pietro{};
            p_1 = p_0;
            std::cout << "p_0: " << p_0 << "\n";
        }
    
    delete p_1;

    std::cout << "fine programma\n";
    return 0;
}