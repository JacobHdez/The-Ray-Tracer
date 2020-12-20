#include "GLCore.h"
#include "SandboxLayer.h"

#include "MyCore.h"

using namespace GLCore;

class Sandbox : public Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}
};

int main()
{
	/*std::unique_ptr<Sandbox> app = std::make_unique<Sandbox>();
	app->Run();*/
	std::string cmd = "a = 7 + 11";

	lua_State* L = luaL_newstate();

	int r = luaL_dostring(L, cmd.c_str());

	if (r == LUA_OK)
	{
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1))
		{
			float a_in_cpp = (float)lua_tonumber(L, -1);
			std::cout << "a_in_cpp = " << a_in_cpp << std::endl;
		}
	}
	else
	{
		std::string errorMsg = lua_tostring(L, -1);
		std::cout << errorMsg << std::endl;
	}

	system("Pause");
	lua_close(L);

	return 0;
}