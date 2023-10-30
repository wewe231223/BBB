#include "pch.h"
#include <random>
#include "Random.h"

namespace Random_Engine {
	std::random_device rd;
	std::mt19937 gen(rd());
}


template<typename T>
T Random::Rand(T min, T max) { return T; }

template<>
float Random::Rand(float min, float max) {
	std::uniform_real_distribution<float>rdf(min, max);
	return rdf(Random_Engine::gen);
}

template<>
double Random::Rand(double min, double max)
{
	std::uniform_real_distribution<double>rdd(min, max);
	return rdd(Random_Engine::gen);
}

template<>
int Random::Rand(int min, int max)
{
	std::uniform_int_distribution<int>rdi(min, max);

	return rdi(Random_Engine::gen);
}

template<>
float3 Random::Rand(float3 min, float3 max)
{
	std::uniform_real_distribution<float>rdfx(min.x, max.x);
	std::uniform_real_distribution<float>rdfy(min.y, max.y);
	std::uniform_real_distribution<float>rdfz(min.z, max.z);

	return float3{ rdfx(Random_Engine::gen), rdfy(Random_Engine::gen) , rdfz(Random_Engine::gen) };
}







bool Random::Random_From_Percentage(float per)
{
	std::uniform_int_distribution<>rdi(0, INT_MAX);


	int flag = INT_MAX * (per * 0.01f);


	if (rdi(Random_Engine::gen) <= flag) {
		return true;
	}
	return false;
}
