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

class MyClass {
public:
    // 默认构造函数
    MyClass()
    {
        std::cout << "Default constructor called" << std::endl;
    }

    // 带参数的构造函数
    MyClass(int value)
    {
        std::cout << "Parameterized constructor called with value: " << value << std::endl;
    }

    // 拷贝构造函数
    MyClass(const MyClass& other)
    {
        std::cout << "Copy constructor called" << std::endl;
    }

    // 移动构造函数
    MyClass(MyClass&& other) noexcept
    {
        std::cout << "Move constructor called" << std::endl;
    }

    // 赋值运算符
    MyClass& operator=(const MyClass& other)
    {
        std::cout << "Copy assignment operator called" << std::endl;
        return *this;
    }

    // 移动赋值运算符
    MyClass& operator=(MyClass&& other) noexcept
    {
        std::cout << "Move assignment operator called" << std::endl;
        return *this;
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

    MyClass obj1; // 默认构造函数
    MyClass obj2(42); // 带参数的构造函数
    MyClass obj3 = obj1; // 拷贝构造函数
    MyClass obj4(std::move(obj2)); // 移动构造函数
    obj3 = obj4; // 赋值运算符
    MyClass obj5;
    obj5 = std::move(obj3); // 移动赋值运算符
    
    std::cout << "====END of main====\n";
    return 0;
}