/*
 * Triangulation.h
 *
 *  Created on: 23-Jul-2014
 *      Author: jaideep
 */

#ifndef TRIANGULATION_H_
#define TRIANGULATION_H_

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_3.h>
#include <CGAL/Tetrahedron_3.h>
namespace solid
{
	namespace geometry
	{
		typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
		typedef CGAL::Triangulation_3<K> Triangulation;
		typedef CGAL::Tetrahedron_3<K> Tetrahedron;
		typedef Triangulation::Cell_handle Cell_handle;
		typedef Triangulation::Vertex_handle Vertex_handle;
		typedef Triangulation::Locate_type Locate_type;
		typedef Triangulation::Point Point;
	}
}

#endif /* TRIANGULATION_H_ */
