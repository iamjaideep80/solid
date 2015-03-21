#include "../core/SimData.h"

#include <iostream.h>

using namespace solid::core;
int main()
{
	SimData dataC;
	{
		SimData dataA;
		dataA.blindValue = 12;
		dataA.numVec.push_back(1.23);
		dataA.numVec.push_back(4.56);
		std::cout << "dataA.blindValue = " << dataA.blindValue << std::endl;
		std::cout << "dataA.numVec0 = " << dataA.numVec[0] << std::endl;
		std::cout << "dataA.numVec1 = " << dataA.numVec[1] << std::endl;
		dataC = dataA;
	}

//	SimData dataB(dataA);
//	std::cout << "dataB.blindValue = " << dataB.blindValue << std::endl;
//	std::cout << "dataB.numVec0 = " << dataB.numVec[0] << std::endl;
//	std::cout << "dataB.numVec1 = " << dataB.numVec[1] << std::endl;


	std::cout << "dataC.blindValue = " << dataC.blindValue << std::endl;
	std::cout << "dataC.numVec0 = " << dataC.numVec[0] << std::endl;
	std::cout << "dataC.numVec1 = " << dataC.numVec[1] << std::endl;
	return 0;
}
