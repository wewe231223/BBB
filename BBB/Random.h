#pragma once


namespace Random {

	template<typename T>
	T Rand(T max, T min);
	
	template<>
	float Rand(float min, float max);


	template<>
	double Rand(double min, double max);


	template<>
	int Rand(int min, int max);

	template<>
	float3 Rand(float3 min, float3 max);

	template<>
	float4 Rand(float4 min, float4 max);

	bool Random_From_Percentage(float per);


}