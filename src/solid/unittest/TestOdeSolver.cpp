//#include <iostream.h>
//#include <array>
#include <boost/numeric/odeint.hpp>

typedef boost::array<double, 2> state_type;

class oscillator
{
public:
	oscillator()
	{
		driving_strength = 0;
		driving_frequency = 0;
	}
	;
	~oscillator()
	{
	}
	;
	double driving_strength;
	double driving_frequency;

	void operator()(state_type const &x, state_type &dxdt, double t) const
	{
		dxdt[0] = x[1];
		dxdt[1] = -x[0] + driving_strength * sin(driving_frequency * t);
	}
};

static
void observer(const state_type& x, const double t)
{
}
int main()
{
	int a = 2;
	state_type state;
	state[0] = 1;
	state[1] = 2;
	oscillator osc;
	osc.driving_frequency = 1;
	osc.driving_strength = 1;
	boost::numeric::odeint::integrate(osc, state, 0.0, 1.0, 1.0, observer);
	std::cout << "state 0 : " << state[0] << std::endl;
	std::cout << "state 1 : " << state[1] << std::endl;
	return 0;
}
