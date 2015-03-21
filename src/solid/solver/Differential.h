/*
 * Differential.h
 *
 *  Created on: 10-May-2014
 *      Author: jaideep
 */

#ifndef DIFFERENTIAL_H_
#define DIFFERENTIAL_H_

#include "../core/CommonTypes.h"
#include "../core/RigidBody.h"
#include <boost/numeric/odeint.hpp>

namespace solid
{
	namespace solver
	{
		typedef boost::array<solid::core::Scalar, 13> state_type;
		class Differential
		{
		public:
			Differential(solid::core::RigidBody* rbdPtr);
			~Differential();
			void operator()(state_type const &x, state_type &dxdt, double t) const;
		private:
			solid::core::RigidBody* rbdPtr;
		};

	} /* namespace solver */
} /* namespace solid */
#endif /* DIFFERENTIAL_H_ */
