#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include "types.hpp"
#include <cstddef>
#include <random>

template<size_t D>
f32 monte_carlo(f32 (*f)(f32 args[D]), f32 a[D], f32 b[D], size_t iterations) {
	std::random_device rand_device;
	auto rand_engine = std::mt19937(rand_device());
	auto distribution = std::uniform_real_distribution<f32>();

	f32 total = 0.0;
	f32 volume = 1.0;
	for (size_t i = 0; i < D; i++) {
		volume *= b[i]-a[i];
	}

	for (size_t i = 0; i < iterations; i++) {
		f32 random_point[D];
		for (size_t j = 0; j < D; j++) {
			random_point[j] = a[j] + (b[j] - a[j]) * distribution(rand_engine);
		}

		total += f(random_point);
	}

	return volume * total / iterations;
}

#endif
