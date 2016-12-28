#include "common/DummyClass.h"

using namespace std::literals;

std::string DummyClass::sayHello()    
{
    return "Hello, World!"s;
}

int DummyClass::addNumbers(int a, int b)
{
    return a + b;
}
