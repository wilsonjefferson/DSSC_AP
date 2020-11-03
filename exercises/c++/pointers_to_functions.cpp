#include <iostream>

void PrintHello()
{
    std::cout << "Hello World!" << std::endl;
}

void Foo(int a)
{
    std::cout << "a = " << a << std::endl;
}

int main()
{
    // <return type>(*<pointer name>)(<incoming args if any>) = <function name>
    // void(* pointer_func)() = PrintHello; 

    // or we may define a typedef (an alias) for all of it...
    typedef void(*PointerFunc)();
    typedef void(*PointerFuncVal)(int);

    PointerFunc p_0 = PrintHello;
    p_0(); // calling funciton through its pointer

    PointerFuncVal p_1 = Foo;
    p_1(4);

    return(0);
}
