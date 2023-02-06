#pragma once

#ifdef PE_PLATFORM_WINDOWS

extern PE::Application* PE::CreateApplication();

int main(int argc, char** argv)
{
	PE::Log::Init();
	PE_LOG_TRACE("Log Initizalized !");

	auto app = PE::CreateApplication();
	app->Run();
	delete app;
}

#endif