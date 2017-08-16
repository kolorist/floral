#include <iostream>

#include <floral.h>

using namespace floral;

int main(void)
{
	std::cout << "floral\n";
	vec2f a(1.2f, 2.3f);
	vec2f b(2.3f, 3.4f);
	a += b;
	std::cout << a.x << "\n";
	std::cout << a.y << "\n";
	return 0;
}
