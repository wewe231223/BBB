#include "pch.h"
#include "Model.h"

Model::Model(UINT Vao, size_t VertexCount)
{

    m_vao = Vao;
    m_vertexCount = VertexCount;



}

Model::Model(const Model& other){
     
    m_vao = other.m_vao;
    m_vertexCount = other.m_vertexCount;
}

Model& Model::operator=(const Model& other)
{
    return *this;
    // TODO: 여기에 return 문을 삽입합니다.
}

void Model::Render(float sid){




    glUseProgram(sid);

    glBindVertexArray(m_vao);

    glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, (void*)0);

    glUseProgram(0);
}

void Model::Update(float dt){
}
