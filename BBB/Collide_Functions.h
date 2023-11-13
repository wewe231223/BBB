#pragma once


bool AABB(glm::vec3& Position,const float3 Box1_Left_Bottom, const float3 Box1_Right_Top,
	const float3 Box2_Left_Bottom,const float3 Box2_Right_Top);



void RayCastHit(glm::vec3 Movement, const float3 Box_Right_Top, const float3 Box_Left_Bottom);