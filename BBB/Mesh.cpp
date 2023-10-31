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
