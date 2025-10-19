#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include "types.hpp"
#include <cstddef>
#include <cstring>
#include <iostream>
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

template<size_t D, size_t M>
struct RiemannSumHelper {
	static f32 call(f32 (*f)(f32 args[D]), f32 a[D], f32 b[D], f32 x[D], f32 h[D], f32 volume, size_t iterations, f32 args[M]) {
		f32 result = 0.0;
		x[M] = a[M];
		for (size_t i = 0; i < iterations; i++) {
			f32 new_args[M+1];
			std::memcpy(new_args, args, sizeof(f32) * M);
			new_args[M] = x[M];
			result += RiemannSumHelper<D, M+1>::call(f, a, b, x, h, volume, iterations, new_args);
			x[M] += h[M];
		}

		return result;
	}
};

template<size_t D>
struct RiemannSumHelper<D, D> {
	static f32 call(f32 (*f)(f32 args[D]), f32 a[D], f32 b[D], f32 x[D], f32 h[D], f32 volume, size_t iterations, f32 args[D]) {
		return f(args) * volume;
	}
};

template<size_t D>
struct RiemannSumHelper<D, 0> {
	static f32 call(f32 (*f)(f32 args[D]), f32 a[D], f32 b[D], f32 x[D], f32 h[D], f32 volume, size_t iterations) {
		f32 result = 0.0;
		x[0] = a[0];
		for (size_t i = 0; i < iterations; i++) {
			f32 new_args[1];
			new_args[0] = x[0];
			result += RiemannSumHelper<D, 1>::call(f, a, b, x, h, volume, iterations, new_args);
			x[0] += h[0];
		}

		return result;
	}
};

template<size_t D>
f32 riemann_sum(f32 (*f)(f32 args[D]), f32 a[D], f32 b[D], size_t iterations) {
	f32 h[D];
	f32 x[D];
	f32 volume = 1.0f;
	for (size_t i = 0; i < D; i++) {
		h[i] = (b[i] - a[i]) / iterations;
		volume *= h[i];
	}

	return RiemannSumHelper<D, 0>::call(f, a, b, x, h, volume, iterations);
}

#endif
