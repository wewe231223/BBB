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

void Model::Render(UINT sid){

    


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    
   // glm::mat4 Transform = glm::translate(glm::mat4{1.f},glm::vec3(-4.f, 0.f, 0.f));
    glm::mat4 Transform{ 1.f };

    
    
    Transform = glm::translate(Transform, glm::vec3(0.f,0.f, m_scale.z / 2.f));

    Transform = glm::rotate(Transform, glm::radians(m_rotation.x), glm::vec3(1.f, 0.f, 0.f));
    Transform = glm::rotate(Transform, glm::radians(m_rotation.y), glm::vec3(0.f, 1.f, 0.f));
    Transform = glm::rotate(Transform, glm::radians(m_rotation.z), glm::vec3(0.f, 0.f, 1.f));

  //  Transform = glm::translate(Transform, glm::vec3(10.f, 10.f, 4.f));


//Transform = glm::translate(Transform, glm::vec3(10.f, 0.f, 0.f));

   // Transform = glm::translate(Transform, m_position);

   

   
    if (m_parent != nullptr) {
        //Transform = m_parent->GetMatrix() * Transform;
    }


    m_transform = Transform;
    Transform = glm::scale(Transform, glm::vec3(m_scale.x, m_scale.y, m_scale.z));

    glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(Transform));
    glBindVertexArray(m_vao);
   
    glUseProgram(sid);

    
    glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, 0);

}

void Model::Update(float dt){
    
}
