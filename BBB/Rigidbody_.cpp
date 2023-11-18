#include "pch.h"
#include "Rigidbody_.h"

#include "Mesh.h"
#include "Collide_Functions.h"


constexpr auto GRAVITY_SCALE = 9.8f;


void Rigidbody::Rotate(glm::vec3 rotation) {

    glm::mat4 RotateMatrix = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);


}

void Rigidbody::Movement(glm::vec3 movement) {
    m_position += movement;

}


float fmax3(float f1, float f2, float f3) {

    float max{};
    if (f1 > f2) {
        max = f1;
    }
    else {
        max = f2;
    }

    if (f3 > max) {
        max = f3;
    }

    return max;

}


glm::vec3 vmax3(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {

    float v1l = glm::length(v1);
    float v2l = glm::length(v2);
    float v3l = glm::length(v3);

    if (v1l < v2l) {
        if (v2l < v3l) {
            std::cout << "z" << std::endl;
            return v3;
        }
        else {
            std::cout << "y" << std::endl;

            return v2;
        }
    }
    else {
        if (v1l < v3l) {
            std::cout << "z" << std::endl;

            return v3;
        }
        else {
            std::cout << "x" << std::endl;

            return v1;
        }

    }



}





void Rigidbody::Update(float dt) {




    glm::vec3 RotateFactor = glm::radians(m_rotate);

    m_axisX = glm::yawPitchRoll(RotateFactor.y, RotateFactor.z, RotateFactor.x) * glm::vec4{ m_axisX,1.f };
    m_axisY = glm::yawPitchRoll(RotateFactor.y, RotateFactor.z, RotateFactor.x) * glm::vec4{ m_axisY,1.f };
    m_axisZ = glm::yawPitchRoll(RotateFactor.y, RotateFactor.z, RotateFactor.x) * glm::vec4{ m_axisZ,1.f };


    m_axisX = glm::normalize(m_axisX);
    m_axisY = glm::normalize(m_axisY);
    m_axisZ = glm::normalize(m_axisZ);


    float dx{ m_deltaPosition.x };
    float dy{ m_deltaPosition.y };
    float dz{ m_deltaPosition.z };
    

    glm::vec3 prev_position = m_position - m_deltaPosition;



    for (auto& other : m_collides) {


        prev_position = m_position - m_deltaPosition;

        if (OBB(m_position,other->GetPosition(),MakeOBBParameter(),other->MakeOBBParameter())) {





            
            if (OBB(glm::vec3{ prev_position.x + dx, prev_position.y ,prev_position.z }, other->m_position, MakeOBBParameter(), other->MakeOBBParameter())) {
                m_position.x -= dx;



            }

            
            if (OBB(glm::vec3{ prev_position.x ,prev_position.y ,prev_position.z + dz }, other->m_position, MakeOBBParameter(), other->MakeOBBParameter())) {

                m_position.z -= dz;
            }
            

            






            if (OBB(glm::vec3{ prev_position.x,prev_position.y + dy,prev_position.z }, other->m_position, MakeOBBParameter(), other->MakeOBBParameter())) {


                m_position.y -= dy;
                

                



                

                // temporary code 
                dy = 0.f;
            }

        }


    


    }



    
}





bool SeparatePlaneExistance(glm::vec3 Posvec, glm::vec3 Plane, OBB_PARAMETER Box1, OBB_PARAMETER Box2)
{

    
    return
        (std::fabs(glm::dot(Posvec, Plane)) >
            std::fabs(glm::dot(std::get<0>(Box1) * std::get<3>(Box1), Plane)) +
            std::fabs(glm::dot(std::get<1>(Box1) * std::get<4>(Box1), Plane)) +
            std::fabs(glm::dot(std::get<2>(Box1) * std::get<5>(Box1), Plane)) +

            std::fabs(glm::dot(std::get<0>(Box2) * std::get<3>(Box2), Plane)) +
            std::fabs(glm::dot(std::get<1>(Box2) * std::get<4>(Box2), Plane)) +
            std::fabs(glm::dot(std::get<2>(Box2) * std::get<5>(Box2), Plane)));
}







bool OBB(glm::vec3 rigid1_Position,glm::vec3 rigid2_Position,OBB_PARAMETER rigid1,OBB_PARAMETER rigid2)
{

    glm::vec3 PosVector = rigid2_Position - rigid1_Position;


    glm::vec3 rigid1_AxisX = std::get<0>(rigid1);
    glm::vec3 rigid1_AxisY = std::get<1>(rigid1);
    glm::vec3 rigid1_AxisZ = std::get<2>(rigid1);


    glm::vec3 rigid2_AxisX = std::get<0>(rigid2);
    glm::vec3 rigid2_AxisY = std::get<1>(rigid2);
    glm::vec3 rigid2_AxisZ = std::get<2>(rigid2);


    if (SeparatePlaneExistance(PosVector, rigid1_AxisX, rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, rigid1_AxisY, rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, rigid1_AxisZ, rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, rigid2_AxisX, rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, rigid2_AxisY, rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, rigid2_AxisZ, rigid1, rigid2)) return false;
    




    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1_AxisX, rigid2_AxisX), rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1_AxisX, rigid2_AxisY), rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1_AxisX, rigid2_AxisZ), rigid1, rigid2)) return false;
    
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1_AxisY, rigid2_AxisX), rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1_AxisY, rigid2_AxisY), rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1_AxisY, rigid2_AxisZ), rigid1, rigid2)) return false;

    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1_AxisZ, rigid2_AxisX), rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1_AxisZ, rigid2_AxisY), rigid1, rigid2)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1_AxisZ, rigid2_AxisZ), rigid1, rigid2)) return false;


    return true;


}



// p0 == plane's point, n == plane normal l0 = ray startpoint l = lay vector 
bool PlaneRayIntersection(glm::vec3 p0, glm::vec3 n, glm::vec3 l0, glm::vec3 l) {


    float denom = glm::dot(l, n);

    float t{};

    if (denom > FLT_EPSILON) {

        glm::vec3 p0l0 = l0 - p0;
        
        t = glm::dot(p0l0, n) / denom;

        return (t >= 0.f);


    }

    return false;

}



//
// 
// 
// 
//Ray Raycast() {
//
//
//
//    return 
//
//}
//
//
//bool RaycastHit(Ray r) {
//
//
//
//
//}