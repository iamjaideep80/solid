#include "../core/Matrix3d.h"

#include <iostream.h>

using namespace solid::core;
int main()
{
	Matrix3d mat;
	mat.setIdentity();
	Matrix3d mat2;
	mat2 = 5 * mat;
	std::cout << mat2 << std::endl;
	return 0;
}
