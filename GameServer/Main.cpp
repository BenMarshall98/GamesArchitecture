#include "../GameEngine/SceneManager.h"
#include "../GameEngine/ServerNetworkingManager.h"
#include "../GameEngine/ThreadingManager.h"
#include "../GameEngine/Win32Window.h"
#include "PyramidServerScene.h"

int WINAPI wWinMain(const HINSTANCE pHInstance, HINSTANCE, LPWSTR, const int pCmdShow)
{
	const auto server = ServerNetworkingManager::Instance();

	IpAddress address(7500);

	const auto recieveFunction = [](const std::string & pMessage, ListeningSocket * pSocket)
	{
		const auto type = pMessage.substr(0, 4);

		if (type == "NetT")
		{
			const auto val = pMessage.substr(4, 8);

			int num = strtoul(val.c_str(), nullptr, 16);

			const auto time = *((float*)&num);

			pSocket->SetTargetTime(time);
		}
		
		return false;
	};

	server->SetRecieveMessageFunction(recieveFunction);
	
	if (!server->StartListening(address))
	{
		return -1;
	}
	
	const auto window = Win32Window::Instance(pHInstance, pCmdShow);
	window->Run();

	SceneManager::Instance()->Run(std::make_shared<PyramidServerScene>());

	server->CloseServer();
	
	delete window;
	delete server;

	ThreadingManager::Instance()->CloseAllThreads();
	delete ThreadingManager::Instance();

	return 0;
}
