#include "pch.h"
#include "Collide_Functions.h"

//bool Collision(Object& obj1, Object& obj2) {
//	if (AABB(obj1.lb, rt. obj2.lb. rt)) {
//		obj1.Collision();
//		obj2.Collision();
//		{
//			m_Position += 0.1f;
//			m_moveForce.y = 0.f;
//		}
//	}
//}
//
//bool Object::Collision(Object& other) {
//	if (coolisiton == true) {
//		other.Cllision();
//		Collision()
//	}
//}





bool AABB(glm::vec3& Position,const float3 Box1_Left_Bottom, const float3 Box1_Right_Top, const float3 Box2_Left_Bottom, const float3 Box2_Right_Top)
{

	float delta{};

	if (Box1_Right_Top.y <= Box2_Left_Bottom.y or Box1_Left_Bottom.y  >= Box2_Right_Top.y ) {
		return false;
	}


	
	if (Box1_Right_Top.z <= Box2_Left_Bottom.z or Box1_Left_Bottom.z  >=Box2_Right_Top.z) {
		return false;
	}
	

	if (Box1_Right_Top.x <= Box2_Left_Bottom.x or Box1_Left_Bottom.x >=Box2_Right_Top.x) {
		return false;
	}
	


	if (Box1_Left_Bottom.y  < Box2_Right_Top.y) {

		Position.y += std::fabs(Box2_Right_Top.y - Box1_Left_Bottom.y);

	}
	else {


		Position.y -= std::fabs(Box1_Right_Top.y - Box2_Left_Bottom.y);

	}







	return true;

}

void RayCastHit(glm::vec3 Movement, const float3 Box_Right_Top, const float3 Box_Left_Bottom)
{
	










}

