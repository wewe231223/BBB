#include "pch.h"
#include <random>
#include "Random.h"

namespace Random_Engine {
	std::random_device rd;
	std::mt19937 gen(rd());
}


float Random::RandFloat(float min, float max)
{
	std::uniform_real_distribution<float>rdf(min, max);
	return rdf(Random_Engine::gen);
}

int Random::RandInt(int min, int max)
{
	std::uniform_int_distribution<int>rdi(min, max);

	return rdi(Random_Engine::gen);
}

double Random::RandDouble(double min, double max)
{
	std::uniform_real_distribution<double>rdd(min, max);
	return rdd(Random_Engine::gen);
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
