#include "pch.h"
#include "Collide_Functions.h"

bool AABB(const float3 Box1_Left_Bottom, const float3 Box1_Right_Top, const float3 Box2_Left_Bottom, const float3 Box2_Right_Top)
{
	if (Box1_Right_Top.x < Box2_Left_Bottom.x or Box1_Left_Bottom.x >Box2_Right_Top.x) {
		return false;
	}



	if (Box1_Right_Top.y < Box2_Left_Bottom.y or Box1_Left_Bottom.y >Box2_Right_Top.y) {
		return false;
	}



	if (Box1_Right_Top.z < Box2_Left_Bottom.z or Box1_Left_Bottom.z >Box2_Right_Top.z) {
		return false;
	}
	return true;
}
