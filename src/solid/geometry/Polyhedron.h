#ifndef POLYHEDRON_H_
#define POLYHEDRON_H_

#include<CGAL/Simple_cartesian.h>
#include<CGAL/Polyhedron_incremental_builder_3.h>
#include<CGAL/Polyhedron_3.h>

namespace solid
{
	namespace geometry
	{
		typedef CGAL::Simple_cartesian<double> Kernel;
		typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
		typedef Polyhedron::HalfedgeDS HalfedgeDS;
	}
}

#endif /* POLYHEDRON_H_ */
