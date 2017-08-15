#include "Win32App.h"

#include <foo.h>
#include <bar.h>

int main(void)
{
    Win32App app;
    app.FooFunc();

    Foo foo;
    Bar bar;
    foo.TestFunc();
    bar.TestFunc();
    return 0;
}
