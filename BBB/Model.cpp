#include "pch.h"
#include "Model.h"
#include "Input.h"

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
    case Qualifier::MAX_ROTATION:
        m_max_Rotation = glm::radians(Src);
        break;
    case Qualifier::MIN_ROTATION:
        m_min_Rotation = glm::radians(Src);
        break;
    default:
        break;
    }


}


template<>
void Model::Set(float3 Src, Qualifier Qualify){

    if (m_parent == nullptr) {
        m_scale = Src;
        return;
    }
    std::shared_ptr<Model> parent = m_parent;


    float parentScaleX{1.f};
    float parentScaleY{1.f};
    float parentScaleZ{1.f};

    float3 parentScale{0.f,};

    do{
       parentScale = parent->GetScale();
       parentScaleX *= parentScale.x;
       parentScaleY *= parentScale.y;
       parentScaleZ *= parentScale.z;


        parent = parent->GetParent();
    } while (parent != nullptr);




    float unitScaleX = 1.f / parentScaleX;
    float unitScaleY = 1.f / parentScaleY;
    float unitScaleZ = 1.f / parentScaleZ;



    m_scale = float3{ unitScaleX * Src.x , unitScaleY * Src.y, unitScaleZ * Src.z };
}
void Model::Render(UINT sid){

    


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    
    glm::mat4 inittrans = glm::translate(glm::mat4{ 1.f }, m_pivot);


    
    m_transMatrix = glm::translate(glm::mat4{ 1.f }, m_position);
    
    

    m_rotation.x = std::clamp(m_rotation.x, m_min_Rotation.x, m_max_Rotation.x);
    m_rotation.y = std::clamp(m_rotation.y, m_min_Rotation.y, m_max_Rotation.y);
    m_rotation.z = std::clamp(m_rotation.z, m_min_Rotation.z, m_max_Rotation.z);




    m_rotationMatrix = glm::yawPitchRoll(m_rotation.y,m_rotation.x, m_rotation.z);



    m_scaleMatrix = glm::scale(glm::mat4{1.f},glm::vec3{m_scale.x , m_scale.y, m_scale.z});




    


    m_WorldMatrix = m_transMatrix * m_rotationMatrix * m_scaleMatrix;



    glm::mat4 finalMatrix = glm::mat4{ 1.f };
    glm::mat4 parentMatrix = glm::mat4{ 1.f };

    if (m_parent != nullptr) {
            

        m_WorldMatrix = m_parent->GetWorldMat() * m_WorldMatrix;
        //m_transMatrix *= m_parent->GetTransMat();
        //m_rotationMatrix *= m_parent->GetRotMat();
        //m_scaleMatrix *= m_parent->GetScaleMat();

    }
  

    


    finalMatrix = m_WorldMatrix * inittrans;
    


    glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(finalMatrix));
    glBindVertexArray(m_vao);
   
    glUseProgram(sid);

    
    glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, 0);

}

void Model::Update(float dt){


    m_rotation += glm::radians( m_rotateDir * dt );
    
}
