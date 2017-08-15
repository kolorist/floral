#include "Win32App.h"

#include <iostream>

Win32App::Win32App()
{
}

Win32App::~Win32App()
{
}

void Win32App::FooFunc()
{
    std::cout << __FUNCTION__ << "\n";
}
