#include "../core/Vector3d.h"

#include <iostream.h>

using namespace solid::core;
int main()
{
	Vector3d vec(1, 0, 0);
	std::cout << "vec : " << vec << std::endl;
	Eigen::Vector3d eigenVec(1, 1, 0);
	Vector3d vec2;
	vec2 = eigenVec;
	std::cout << "vec2 : " << vec2 << std::endl;
	return 0;
}
