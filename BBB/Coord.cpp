#include "pch.h"
#include "Coord.h"
#include "Random.h"



Coord::Coord(){

	float3 color1 = Random::Rand(float3{ 0.f,0.f,0.f }, float3{ 1.f,1.f,1.f });
	float3 color2 = Random::Rand(float3{ 0.f,0.f,0.f }, float3{ 1.f,1.f,1.f });
	float3 color3 = Random::Rand(float3{ 0.f,0.f,0.f }, float3{ 1.f,1.f,1.f });
	float3 color4 = Random::Rand(float3{ 0.f,0.f,0.f }, float3{ 1.f,1.f,1.f });



	const float Color[3 * 3 * 2] = {
		color1.x, color1.y, color1.z,
		color2.x, color2.y, color2.z,
		color3.x, color3.y, color3.z,


		color1.x, color1.y, color1.z,
		color4.x, color4.y, color4.z,
		color2.x, color2.y, color4.z

	};




	const float LineColor[18] = {
		0.f,1.f,0.f,
		0.f,1.f,0.f,

		1.f,0.f,0.f,
		1.f,0.f,0.f,

		0.f,0.f,1.f,
		0.f,0.f,1.f

	};


	glGenVertexArrays(1, &m_vaoXZ);
	glBindVertexArray(m_vaoXZ);


	UINT vbo[2];
	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), Vertex, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 , 0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), Color, GL_STATIC_DRAW);




	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);









}

void Coord::Render(UINT sid){

	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLuint TransitionLocation = glGetUniformLocation(sid, "transform");
	glUniformMatrix4fv(TransitionLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));



	glBindVertexArray(m_vaoXZ);
	glDrawArrays(GL_TRIANGLES, 0, 18);

}
