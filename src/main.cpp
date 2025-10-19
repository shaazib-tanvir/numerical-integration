#include <cstdlib>
#include <iostream>
#include <types.hpp>
#include <integrator.hpp>
#include <cmath>

const double PI = std::acos(-1);

f32 f(f32 x[1]) {
	return 0.73*std::sin(2*PI*x[0]+1.12)-0.21*std::sin(4*PI*x[0]+4.57)+0.09*std::sin(6*PI*x[0]+2.03)-0.04*std::sin(8*PI*x[0]+5.68);
}

int main() {
	f32 a[1] = {0.0};
	f32 b[1] = {0.2};

	size_t iterations = 1e5;
	f32 result = monte_carlo<1>(f, a, b, iterations);
	std::cout << "=====================================================\n";
	std::cout << "monte carlo\n";
	std::cout << "iterations = " << iterations << " result = " << result << "\n";
	std::cout << "=====================================================\n";
	return EXIT_SUCCESS;
}
