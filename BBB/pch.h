#pragma once 

//stream
#include <iostream>
#include <windows.h>
#include <winnt.h>


// OpenGL 헤더 파일들 추가
#include <gl/glew.h>
#include <gl/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_NATIVE_INCLUDE_NONE
#include <gl/glfw3native.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glm/gtx/vector_angle.hpp>
#include <gl/glm/gtx/euler_angles.hpp>

// STL 헤더 파일들 추가
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <list>

using int32 = __int32;
using int64 = __int64;

using uint8 = unsigned __int8;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;


struct _TAG_WINDOWINFO {
	GLFWwindow* window{ };
	HWND		win32Window{};
	int32		x{ };
	int32		y{ };
	int32		width{ };
	int32		height{ };
	std::string windowTitle{ };
};

struct _TAG_FLOAT2 {
	float x{ };
	float y{ };
};

struct _TAG_FLOAT3 {
	float x{ };
	float y{ };
	float z{ };
};

struct _TAG_FLOAT4 {
	float x{ };
	float y{ };
	float z{ };
	float w{ };
};

struct _TAG_DOUBLE2 {
	double x{};
	double y{};
};

struct _TAG_VERTEX {
	_TAG_FLOAT3 position{ };
	_TAG_FLOAT4 color{ };
	_TAG_FLOAT2 texture{ };
	glm::vec3	normal{ };
};

using float2 = _TAG_FLOAT2;
using float3 = _TAG_FLOAT3;
using float4 = _TAG_FLOAT4;
using double2 = _TAG_DOUBLE2;
using vertex = _TAG_VERTEX;

using WINDOWINFORMATION = _TAG_WINDOWINFO;

enum class KEY_STATE {
	NONE, // 어떤 행동 상태도 아닐 때 
	PRESS, // 계속 누르고 있는 상태 
	DOWN, // 눌렀을 때 그 상태 
	RELEASE // 키를 떼었을때 그 상태 
};


extern std::unique_ptr<class Engine> engine;


#include "Random.h"
