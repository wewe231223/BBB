#include "pch.h"
#include "Mesh.h"


Mesh::Mesh(std::string path) {

	const char* c_Path = path.c_str();


	std::fstream file(c_Path);

	if (!file) {
		std::cerr << "OBJ FILE ERROR!" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cerr << c_Path << " is Sucessfully Opened! " << std::endl;
	}

	std::vector<vertex>::iterator uv_Iterator = m_vertex.begin();
	std::vector<vertex>::iterator normal_Iterator = m_vertex.begin();


	while (!file.eof()) {

		std::string head{};


		file >> head;

		if (head._Equal("#")) { std::getline(file, head); continue; }

		if (head._Equal("v")) {
			vertex v{};
			ZeroMemory(&v, sizeof(vertex));

			file >> v.position.x >> v.position.y >> v.position.z;
			v.color = Random::Rand(float4{ 0.f,0.f,0.f,1.f }, float4{ 1.f,1.f,1.f,1.f });


			m_vertex.push_back(v);

			uv_Iterator = m_vertex.begin();
			normal_Iterator = m_vertex.begin();
		}


		if (head._Equal("vn")) {
			if (normal_Iterator != m_vertex.end()) {
				file >> (*normal_Iterator).normal.x >> (*normal_Iterator).normal.y >> (*normal_Iterator).normal.z;
				normal_Iterator++;
			}
		}


		if (head._Equal("vt")) {
			if (uv_Iterator != m_vertex.end()) {
				file >> (*uv_Iterator).texture.x >> (*uv_Iterator).texture.y;
				uv_Iterator++;
			}
		}

		if (head._Equal("f")) {
			std::string Line[3]{};

			GLuint VertexIndex[3]{};
			GLuint UVIndec[3]{};
			GLuint NormalIndex[3]{};

			file >> Line[0] >> Line[1] >> Line[2];



			for (auto i = 0; i < 3; ++i) {
				std::istringstream iss(Line[i]);
				std::string token{};
				GLuint Data[3]{};
				int dataindex = 0;
				if (Line[i].find("//") != std::string::npos) {
					// 있으면

					std::getline(iss, token, '/');
					if (!token.empty())
						m_vertexIndices.push_back(static_cast<UINT>(stoi(token) - 1));


					std::getline(iss, token, '/');
					std::getline(iss, token, '/');

					if (!token.empty())
						m_normalIndices.push_back(static_cast<UINT>(stoi(token) - 1));
				}
				else {
					//없으면 

					std::getline(iss, token, '/');
					if (!token.empty())
						m_vertexIndices.push_back(static_cast<UINT>(stoi(token) - 1));


					std::getline(iss, token, '/');
					if (!token.empty())
						m_uvIndices.push_back(static_cast<UINT>(stoi(token) - 1));


					std::getline(iss, token, '/');
					if (!token.empty())
						m_normalIndices.push_back(static_cast<UINT>(stoi(token) - 1));



				}
			}


		}



	}

	m_vertexCount = m_vertexIndices.size();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)* m_vertex.size(), &(m_vertex[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex,position));
	glEnableVertexAttribArray(0);

	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex,color));
	glEnableVertexAttribArray(1);


	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT)* m_vertexIndices.size(), &(m_vertexIndices[0]), GL_STATIC_DRAW);

}



Mesh::Mesh(std::string path,float3 color) {

	const char* c_Path = path.c_str();


	std::fstream file(c_Path);

	if (!file) {
		std::cerr << "OBJ FILE ERROR!" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cerr << c_Path << " is Sucessfully Opened! " << std::endl;
	}

	std::vector<vertex>::iterator uv_Iterator = m_vertex.begin();
	std::vector<vertex>::iterator normal_Iterator = m_vertex.begin();


	while (!file.eof()) {

		std::string head{};


		file >> head;

		if (head._Equal("#")) { std::getline(file, head); continue; }

		if (head._Equal("v")) {
			vertex v{};
			ZeroMemory(&v, sizeof(vertex));

			file >> v.position.x >> v.position.y >> v.position.z;
			//v.color = Random::Rand(float4{ 0.f,0.f,0.f,1.f }, float4{ 1.f,1.f,1.f,1.f });

			v.color = float4{ color.x,color.y,color.z, 1.f };

			m_vertex.push_back(v);

			uv_Iterator = m_vertex.begin();
			normal_Iterator = m_vertex.begin();
		}


		if (head._Equal("vn")) {
			if (normal_Iterator != m_vertex.end()) {
				file >> (*normal_Iterator).normal.x >> (*normal_Iterator).normal.y >> (*normal_Iterator).normal.z;
				normal_Iterator++;
			}
		}


		if (head._Equal("vt")) {
			if (uv_Iterator != m_vertex.end()) {
				file >> (*uv_Iterator).texture.x >> (*uv_Iterator).texture.y;
				uv_Iterator++;
			}
		}

		if (head._Equal("f")) {
			std::string Line[3]{};

			GLuint VertexIndex[3]{};
			GLuint UVIndec[3]{};
			GLuint NormalIndex[3]{};

			file >> Line[0] >> Line[1] >> Line[2];



			for (auto i = 0; i < 3; ++i) {
				std::istringstream iss(Line[i]);
				std::string token{};
				GLuint Data[3]{};
				int dataindex = 0;
				if (Line[i].find("//") != std::string::npos) {
					// 있으면

					std::getline(iss, token, '/');
					if (!token.empty())
						m_vertexIndices.push_back(static_cast<UINT>(stoi(token) - 1));


					std::getline(iss, token, '/');
					std::getline(iss, token, '/');

					if (!token.empty())
						m_normalIndices.push_back(static_cast<UINT>(stoi(token) - 1));
				}
				else {
					//없으면 

					std::getline(iss, token, '/');
					if (!token.empty())
						m_vertexIndices.push_back(static_cast<UINT>(stoi(token) - 1));


					std::getline(iss, token, '/');
					if (!token.empty())
						m_uvIndices.push_back(static_cast<UINT>(stoi(token) - 1));


					std::getline(iss, token, '/');
					if (!token.empty())
						m_normalIndices.push_back(static_cast<UINT>(stoi(token) - 1));



				}
			}


		}



	}

	m_vertexCount = m_vertexIndices.size();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);



	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * m_vertex.size(), &(m_vertex[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
	glEnableVertexAttribArray(1);


	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT) * m_vertexIndices.size(), &(m_vertexIndices[0]), GL_STATIC_DRAW);

}

void RenderCube(UINT sid,float3 Left_Bottom, float3 Right_Top){

	
	UINT transformLocation = glGetUniformLocation(sid, "transform");

	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4{ 1.f }));



	
	UINT Vao{};
	UINT Vbo{};
	UINT Ebo{};


	




	vertex Verties[8]{};
	UINT Indices[24]{
	0,1,
	1,2,
	2,3,
	3,0,
	0,4,
	1,5,
	2,7,
	3,6,
	4,5,
	5,7,
	7,6,
	6,4
	};


	Verties[0].position = Left_Bottom;
	Verties[1].position = float3{ Right_Top.x,		Left_Bottom.y,		Left_Bottom.z};
	Verties[2].position = float3{ Right_Top.x,		Left_Bottom.y,		Right_Top.z };
	Verties[3].position = float3{ Left_Bottom.x,	Left_Bottom.y,		Right_Top.z};
	
	Verties[4].position = float3{ Left_Bottom.x,	Right_Top.y,		Left_Bottom.z };
	Verties[5].position = float3{ Right_Top.x,		Right_Top.y,		Left_Bottom.z };
	Verties[6].position = float3{ Left_Bottom.x,	Right_Top.y,		Right_Top.z };
	Verties[7].position = Right_Top;







	for (auto i = 0; i < 8; ++i) {
		// color 
		Verties[i].color.x = 1.f;
		Verties[i].color.y = 0.f;
		Verties[i].color.z = 0.f;
		
	}

	
	glGenVertexArrays(1, &Vao);
	glGenBuffers(1, &Vbo);

	glBindVertexArray(Vao);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);

	glGenBuffers(1, &Ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);




	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 8, Verties,GL_STATIC_DRAW);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ARRAY_BUFFER, Vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
	glEnableVertexAttribArray(1);


	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT) * 24, Indices, GL_STATIC_DRAW);



	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);


	glDeleteBuffers(1, &Vbo);
	glDeleteBuffers(1, &Ebo);
	glDeleteVertexArrays(1, &Vao);


}




void RenderCube(UINT sid, glm::vec3 Left_Bottom, glm::vec3 Right_Top) {


	UINT transformLocation = glGetUniformLocation(sid, "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4{ 1.f }));




	UINT Vao{};
	UINT Vbo{};
	UINT Ebo{};







	vertex Verties[8]{};
	UINT Indices[24]{
	0,1,
	1,2,
	2,3,
	3,0,
	0,4,
	1,5,
	2,7,
	3,6,
	4,5,
	5,7,
	7,6,
	6,4
	};


	Verties[0].position = float3{ Left_Bottom.x,	Left_Bottom.y,		Left_Bottom.z};
	Verties[1].position = float3{ Right_Top.x,		Left_Bottom.y,		Left_Bottom.z };
	Verties[2].position = float3{ Right_Top.x,		Left_Bottom.y,		Right_Top.z };
	Verties[3].position = float3{ Left_Bottom.x,	Left_Bottom.y,		Right_Top.z };

	Verties[4].position = float3{ Left_Bottom.x,	Right_Top.y,		Left_Bottom.z };
	Verties[5].position = float3{ Right_Top.x,		Right_Top.y,		Left_Bottom.z };
	Verties[6].position = float3{ Left_Bottom.x,	Right_Top.y,		Right_Top.z };
	Verties[7].position = float3{ Right_Top.x,		Right_Top.y,		Right_Top.z };







	for (auto i = 0; i < 8; ++i) {
		// color 
		Verties[i].color.x = 1.f;
		Verties[i].color.y = 0.f;
		Verties[i].color.z = 0.f;

	}


	glGenVertexArrays(1, &Vao);
	glGenBuffers(1, &Vbo);

	glBindVertexArray(Vao);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);

	glGenBuffers(1, &Ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);




	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 8, Verties, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, Vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, Vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
	glEnableVertexAttribArray(1);


	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT) * 24, Indices, GL_STATIC_DRAW);



	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);


	glDeleteBuffers(1, &Vbo);
	glDeleteBuffers(1, &Ebo);
	glDeleteVertexArrays(1, &Vao);


}

void RenderVector(UINT sid, glm::vec3 Startpoint, glm::vec3 Vector, float3 color) {

	UINT transformLocation = glGetUniformLocation(sid, "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4{ 1.f }));


	UINT Vao{};
	UINT Vbo{};




	vertex V[2]{ vertex{Startpoint},vertex{Startpoint + Vector} };

	V[0].color = float4{ color.x,color.y,color.z,1.f };
	V[1].color = float4{ color.x,color.y,color.z,1.f };



	glGenVertexArrays(1, &Vao);
	glGenBuffers(1, &Vbo);

	glBindVertexArray(Vao);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 2, V, GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
	glEnableVertexAttribArray(1);



	glDrawArrays(GL_LINES, 0, 2);


	glDeleteBuffers(1, &Vbo);
	glDeleteVertexArrays(1, &Vao);

}



void RenderVector(UINT sid,glm::vec3 Startpoint, glm::vec3 Vector) {


	UINT transformLocation = glGetUniformLocation(sid, "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4{ 1.f }));


	UINT Vao{};
	UINT Vbo{};




	vertex V[2]{ vertex{Startpoint},vertex{Vector} };

	
	glGenVertexArrays(1, &Vao);
	glGenBuffers(1, &Vbo);

	glBindVertexArray(Vao);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 2, V, GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
	glEnableVertexAttribArray(1);



	glDrawArrays(GL_LINES, 0, 2);


	glDeleteBuffers(1, &Vbo);
	glDeleteVertexArrays(1, &Vao);

}

