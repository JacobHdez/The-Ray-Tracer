#include "GLCore.h"
#include "SandboxLayer.h"

using namespace GLCore;

class Sandbox : public Application
{
public:
	Sandbox(const std::string& filepath)
	{
		PushLayer(new SandboxLayer(filepath));
	}
};

int main(int argc, char const* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " scrip_filepath" << std::endl;
		system("Pause");
		return -1;
	}

	std::unique_ptr<Sandbox> app = std::make_unique<Sandbox>(argv[1]);
	app->Run();

	system("Pause");
	return 0;
}