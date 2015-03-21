#include "../core/RigidBody.h"

#include <iostream.h>

using namespace solid::core;
int main()
{
	RigidBody	rb;
	std::cout << rb.linearMomentum << std::endl;
	std::cout << rb.inertia << std::endl;
	std::cout << rb.force<< std::endl;
	return 0;
}
