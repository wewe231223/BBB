#pragma once

enum class CoordRenderFlag {
	RenderAll,
	RenderLineOnly,
	RenderXZOnly
};

constexpr auto CoordScale = 1000.f;

class Coord
{
public:

	Coord();

private:

	const GLfloat Vertex[3 * 3 * 2] = {
		-CoordScale,0.f,-CoordScale, // 1
		CoordScale,0.f,CoordScale,   // 2
		-CoordScale,0.f,CoordScale,  // 3

		-CoordScale,0.f,-CoordScale, // 1
		CoordScale,0.f,-CoordScale,  // 4
		CoordScale,0.f,CoordScale    // 2
	};



	const GLfloat Line[18] = {
		0.f,CoordScale,0.f,
		0.f,-CoordScale,0.f,


		CoordScale,0.1f,0.f,
		-CoordScale,0.1f,0.f,

		0.f,0.1f,CoordScale,
		0.f,0.1f,-CoordScale
	};


	UINT m_vaoXZ{};
	UINT m_vaoLine{};

	CoordRenderFlag m_renderFlag = CoordRenderFlag::RenderAll;


public:

	void Render(UINT sid);


};

