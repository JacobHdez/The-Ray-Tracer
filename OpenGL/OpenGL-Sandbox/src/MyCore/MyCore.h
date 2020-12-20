#pragma once

// Renderer
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"

// Light
#include "Light/Light.h"

// Material
#include "Material/Material.h"

// Mesh
#include "Mesh/Primitive/Primitive.h"
#include "Mesh/Mesh.h"

// Model
#include "Model/Model.h"

// Scene
#include "Scene/Scene.h"

// Lua
#ifndef __LUA_INC_H__
	#define __LUA_INC_H__

	extern "C"
	{
		#include "lua.h"
		#include "lauxlib.h"
		#include "lualib.h"
	}

#endif // !__LUA_INC_H__