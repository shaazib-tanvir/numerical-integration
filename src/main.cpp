#include <cstdlib>
#include <iostream>
#include <types.hpp>
#include <integrator.hpp>
#include <cmath>

const double PI = std::acos(-1);

f32 f(f32 x[1]) {
	return 0.73*std::sin(2*PI*x[0]+1.12)-0.21*std::sin(4*PI*x[0]+4.57)+0.09*std::sin(6*PI*x[0]+2.03)-0.04*std::sin(8*PI*x[0]+5.68);
}

f32 g(f32 x[2]) {
	return std::sin(x[0]) * std::cos(x[1]);
}

int main() {
	{
		f32 a[1] = {0.0};
		f32 b[1] = {0.2};

		size_t iterations = 1e4;
		f32 monte_carlo_result = monte_carlo<1>(f, a, b, iterations);
		std::cout << "=====================================================\n";
		std::cout << "monte carlo\n";
		std::cout << "dim = 1 iterations = " << iterations << " result = " << monte_carlo_result << "\n";
		std::cout << "=====================================================\n";

		f32 riemann_sum_result = riemann_sum<1>(f, a, b, iterations);
		std::cout << "riemann sum\n";
		std::cout << "dim = 1 iterations = " << iterations << " result = " << riemann_sum_result << "\n";
		std::cout << "=====================================================\n";
	}

	{
		f32 a[2] = {0.0, 0.0};
		f32 b[2] = {1.0, 1.0};

		size_t iterations = 1e4;
		f32 monte_carlo_result = monte_carlo<2>(g, a, b, iterations);
		std::cout << "=====================================================\n";
		std::cout << "monte carlo\n";
		std::cout << "dim = 2 iterations = " << iterations << " result = " << monte_carlo_result << "\n";
		std::cout << "=====================================================\n";

		size_t i = 1e2;
		f32 riemann_sum_result = riemann_sum<2>(g, a, b, i);
		std::cout << "riemann sum\n";
		std::cout << "dim = 2 iterations = " << iterations << " result = " << riemann_sum_result << "\n";
		std::cout << "=====================================================\n";
	}

	return EXIT_SUCCESS;
}
