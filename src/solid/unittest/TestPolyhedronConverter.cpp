#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

#include<CGAL/Simple_cartesian.h>
#include<CGAL/Polyhedron_incremental_builder_3.h>
#include<CGAL/Polyhedron_3.h>
#include<CGAL/IO/Polyhedron_iostream.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Polyhedron::HalfedgeDS HalfedgeDS;

// A modifier creating a triangle with the incremental builder.
template<class HDS>
class polyhedron_builder : public CGAL::Modifier_base<HDS>
{
public:
	std::vector<double> &coords;
	std::vector<int> &tris;
	polyhedron_builder(std::vector<double> &_coords, std::vector<int> &_tris) :
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

// reads the first integer from a string in the form
// "334/455/234" by stripping forward slashes and
// scanning the result
int get_first_integer(const char *v)
{
	int ival;
	std::string s(v);
	std::replace(s.begin(), s.end(), '/', ' ');
	sscanf(s.c_str(), "%d", &ival);
	return ival;
}

// barebones .OFF file reader, throws away texture coordinates, normals, etc.
// stores results in input coords array, packed [x0,y0,z0,x1,y1,z1,...] and
// tris array packed [T0a,T0b,T0c,T1a,T1b,T1c,...]
void load_obj(const char *filename, std::vector<double> &coords, std::vector<int> &tris)
{
	double x, y, z;
	char line[1024], v0[1024], v1[1024], v2[1024];

	// open the file, return if open fails
	FILE *fp = fopen(filename, "r");
	if (!fp)
		return;

	// read lines from the file, if the first character of the
	// line is 'v', we are reading a vertex, otherwise, if the
	// first character is a 'f' we are reading a facet
	while (fgets(line, 1024, fp))
	{
		if (line[0] == 'v')
		{
			sscanf(line, "%*s%lf%lf%lf", &x, &y, &z);
			coords.push_back(x);
			coords.push_back(y);
			coords.push_back(z);
		}
		else if (line[0] == 'f')
		{
			sscanf(line, "%*s%s%s%s", v0, v1, v2);
			tris.push_back(get_first_integer(v0) - 1);
			tris.push_back(get_first_integer(v1) - 1);
			tris.push_back(get_first_integer(v2) - 1);
		}
	}
	fclose(fp);
}

int main()
{
	// two vectors to hold point coordinates and
	// triangle vertex indices
	std::vector<double> coords;
	std::vector<int> tris;

	// load the input file
	load_obj("input.obj", coords, tris);
	if (coords.size() == 0)
		return 1;

	// build a polyhedron from the loaded arrays
	Polyhedron P;
	polyhedron_builder<HalfedgeDS> builder(coords, tris);
	P.delegate(builder);

	// write the polyhedron out as a .OFF file
	std::ofstream os("dump.off");
	os << P;
	os.close();

	return 0;
}
