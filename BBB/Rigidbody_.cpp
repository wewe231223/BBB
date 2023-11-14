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

    m_velocity += m_force;
    m_position += m_velocity * dt;
    m_force.y -= GRAVITY_SCALE;


    for (auto other : m_collides) {




       
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







bool OBB(std::shared_ptr<Rigidbody> rigid1, std::shared_ptr<Rigidbody> rigid2)
{


    glm::vec3 PosVector = rigid2->GetPosition() - rigid1->GetPosition();

    OBB_PARAMETER rigid1_Box = rigid1->MakeOBBParameter();
    OBB_PARAMETER rigid2_Box = rigid2->MakeOBBParameter();

    if (SeparatePlaneExistance(PosVector, rigid1->m_axisX, rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, rigid1->m_axisY, rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, rigid1->m_axisZ, rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, rigid2->m_axisX, rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, rigid2->m_axisY, rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, rigid2->m_axisZ, rigid1_Box, rigid2_Box)) return false;
    




    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1->m_axisX, rigid2->m_axisX), rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1->m_axisX, rigid2->m_axisY), rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1->m_axisX, rigid2->m_axisZ), rigid1_Box, rigid2_Box)) return false;
    



    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1->m_axisY, rigid2->m_axisX), rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1->m_axisY, rigid2->m_axisY), rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1->m_axisY, rigid2->m_axisZ), rigid1_Box, rigid2_Box)) return false;
    



    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1->m_axisZ, rigid2->m_axisX), rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1->m_axisZ, rigid2->m_axisY), rigid1_Box, rigid2_Box)) return false;
    if (SeparatePlaneExistance(PosVector, glm::cross(rigid1->m_axisZ, rigid2->m_axisZ), rigid1_Box, rigid2_Box)) return false;
    


    return true;


}



