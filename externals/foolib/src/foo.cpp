#include "foo.h"

#include <iostream>

void Foo::TestFunc()
{
    std::cout << __FUNCTION__ << "\n";
}
