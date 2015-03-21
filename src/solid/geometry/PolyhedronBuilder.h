#ifndef POLYHEDRONBUILDER_H_
#define POLYHEDRONBUILDER_H_

namespace solid
{
	namespace geometry
	{
		// A modifier creating a triangle with the incremental builder.
		template<class HDS>
		class PolyhedronBuilder : public CGAL::Modifier_base<HDS>
		{
		public:
			std::vector<double> &coords;
			std::vector<int> &tris;
			PolyhedronBuilder(std::vector<double> &_coords, std::vector<int> &_tris) :
					coords(_coords), tris(_tris)
			{
			}
			void operator()(HDS& hds)
			{
				typedef typename HDS::Vertex Vertex;
				typedef typename Vertex::Point Point;

				// create a cgal incremental builder
				CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);
				B.begin_surface(coords.size() / 3, tris.size() / 3);

				// add the polyhedron vertices
				for (int i = 0; i < (int) coords.size(); i += 3)
				{
					B.add_vertex(Point(coords[i + 0], coords[i + 1], coords[i + 2]));
				}

				// add the polyhedron triangles
				for (int i = 0; i < (int) tris.size(); i += 3)
				{
					B.begin_facet();
					B.add_vertex_to_facet(tris[i + 0]);
					B.add_vertex_to_facet(tris[i + 1]);
					B.add_vertex_to_facet(tris[i + 2]);
					B.end_facet();
				}

				// finish up the surface
				B.end_surface();
			}
		};
	}
}

#endif /* POLYHEDRONBUILDER_H_ */
