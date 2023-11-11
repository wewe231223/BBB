#include "pch.h"
#include "Model.h"
#include "Input.h"

constexpr glm::mat4 UnitMatrix = glm::mat4{ 1.f };

Model::Model(UINT sid,UINT Vao, size_t VertexCount)
{

    m_vao = Vao;
    m_vertexCount = VertexCount;
    m_transformLocation = glGetUniformLocation(sid, "transform");


}


Model& Model::operator=(const Model& other)
{
    return *this;
    // TODO: 여기에 return 문을 삽입합니다.
}

template<>
void Model::Set(const glm::vec3 Src, Qualifier Qualify)
{


    switch (Qualify)
    {
    case Qualifier::POSITION:
        m_position = Src;

        break;
    case Qualifier::PIVOT:

        m_pivot = Src;

        break;
    case Qualifier::ROTATION:
        m_rotation = Src;
        break;
    case Qualifier::SCALE:
    {
        if (m_parent == nullptr) {
            m_scale = Src;
            return;
        }
        std::shared_ptr<Model> parent = m_parent;


        float parentScaleX{ 1.f };
        float parentScaleY{ 1.f };
        float parentScaleZ{ 1.f };

        glm::vec3 parentScale{ 0.f, };

        do {
            parentScale = parent->GetScale();
            parentScaleX *= parentScale.x;
            parentScaleY *= parentScale.y;
            parentScaleZ *= parentScale.z;


            parent = parent->GetParent();
        } while (parent != nullptr);




        float unitScaleX = 1.f / parentScaleX;
        float unitScaleY = 1.f / parentScaleY;
        float unitScaleZ = 1.f / parentScaleZ;



        m_scale = glm::vec3{ unitScaleX * Src.x , unitScaleY * Src.y, unitScaleZ * Src.z };
   }
        break;
    case Qualifier::MAX_ROTATION:
        m_max_Rotation = Src;
        break;
    case Qualifier::MIN_ROTATION:
        m_min_Rotation = Src;
        break;
    default:
        break;
    }


}




void Model::Render(UINT sid){


    glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4{ 0.f }));


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    glm::mat4 inittrans = glm::translate(glm::mat4{ 1.f }, m_pivot);


    m_WorldMatrix = glm::mat4{ 1.f };



    glm::vec3 rotateFactor = glm::radians(m_rotation);



    if (m_parent != nullptr) {


        glm::mat4 scaleMat = m_parent->GetScaleMat();

        glm::vec3 scaleFactor{ scaleMat[0][0] , scaleMat[1][1] , scaleMat[2][2] };




        m_transMatrix = glm::translate(UnitMatrix, glm::vec3{ m_position * scaleFactor  });
        m_rotationMatrix = glm::yawPitchRoll(rotateFactor.y, rotateFactor.z, rotateFactor.x);
        m_scaleMatrix = glm::scale(glm::vec3{ m_scale.x,m_scale.y,m_scale.z });
        m_scaleMatrix = m_parent->GetScaleMat() * m_scaleMatrix;


        std::shared_ptr<Model> parentptr = m_parent;

        m_WorldMatrix = m_transMatrix * m_rotationMatrix * m_scaleMatrix;


        while (parentptr != nullptr) {

            m_WorldMatrix = parentptr->GetTransMat() * parentptr->GetRotMat() * m_WorldMatrix;
            parentptr = parentptr->GetParent();

        }

    }
    else {
        m_transMatrix = glm::translate(UnitMatrix, m_position);

        m_rotationMatrix = glm::yawPitchRoll(rotateFactor.y, rotateFactor.z, rotateFactor.x);



        m_scaleMatrix = glm::scale(glm::vec3{ m_scale.x,m_scale.y,m_scale.z });

        m_WorldMatrix = m_transMatrix * m_rotationMatrix * m_scaleMatrix;
    }


    glm::mat4 finalMatrix = m_WorldMatrix * inittrans;



    glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(finalMatrix));
    glBindVertexArray(m_vao);

    glUseProgram(sid);


    glDrawElements(GL_TRIANGLES, (GLsizei)m_vertexCount, GL_UNSIGNED_INT, 0);

}

void Model::Update(float dt){
    m_rotation.x = std::clamp(m_rotation.x, m_min_Rotation.x, m_max_Rotation.x);
    m_rotation.y = std::clamp(m_rotation.y, m_min_Rotation.y, m_max_Rotation.y);
    m_rotation.z = std::clamp(m_rotation.z, m_min_Rotation.z, m_max_Rotation.z);


    if (m_rotation == m_max_Rotation) {
        m_rotate_dir = Negative;
    }
    else if (m_rotation == m_min_Rotation) {
        m_rotate_dir = Positive;
    }


    m_rotation += m_rotate_dir * m_rotate_speed * dt ;
    
}



