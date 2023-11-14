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







void Rigidbody::Update(float dt) {
    

    glm::vec3 RotateFactor = glm::radians(m_rotate);

    m_axisX = glm::yawPitchRoll(RotateFactor.y, RotateFactor.z, RotateFactor.x) * glm::vec4{m_axisX,1.f};
    m_axisY = glm::yawPitchRoll(RotateFactor.y, RotateFactor.z, RotateFactor.x) * glm::vec4{ m_axisY,1.f };
    m_axisZ = glm::yawPitchRoll(RotateFactor.y, RotateFactor.z, RotateFactor.x) * glm::vec4{ m_axisZ,1.f };


    m_axisX = glm::normalize(m_axisX);
    m_axisY = glm::normalize(m_axisY);
    m_axisZ = glm::normalize(m_axisZ);



    for (auto& other : m_collides) {

        if (OBB(m_position,other->GetPosition(),MakeOBBParameter(),other->MakeOBBParameter())) {

            m_position -= m_deltaPosition * 1.001f;
            
        }

    }




}





bool SeparatePlaneExistance(glm::vec3 Posvec, glm::vec3 Plane, std::tuple<glm::vec3, glm::vec3, glm::vec3, float, float, float> Box1, std::tuple<glm::vec3, glm::vec3, glm::vec3, float, float, float> Box2)
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



