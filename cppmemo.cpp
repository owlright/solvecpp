#include <iostream>
#include <memory>

class A;
class B;

class A {
public:
    std::shared_ptr<B> b_ptr;

public:
    A()
    {
        std::cout << "A()" << std::endl;
    }
    ~A()
    {
        std::cout << "~A()" << std::endl;
    }
};

class B {
public:
    std::shared_ptr<A> a_ptr;
    ~B()
    {
        std::cout << "B deleted" << std::endl;
    }
};

int main()
{
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->b_ptr = b;
    std::cout << a->b_ptr.use_count() << std::endl;
    b->a_ptr = a;
    std::cout << b->a_ptr.use_count() << std::endl;
    std:: cout << "====END of main====\n";
    return 0;
}