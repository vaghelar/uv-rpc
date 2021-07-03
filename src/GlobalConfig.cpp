#include "GlobalConfig.h"
#include <uv.h>
#include <iostream>

namespace robin
{
	// 初始化
	std::shared_ptr<IDispatcher>    GlobalConfig::msgDispatcher;
	std::map<std::string, IWorkPtr> GlobalConfig::workMap;
	std::shared_ptr<IEncoder>       GlobalConfig::msgEncoder;

	uv_loop_t* GlobalConfig::loop = nullptr;


	// 初始化一些相关参数
	void GlobalConfig::init()
	{
		// 设置为64个线程
		_putenv("UV_THREADPOOL_SIZE=64");

		/*
		char *buffer1 = new char[100];
		size_t st = 100;
		_dupenv_s(&buffer1, &st, "UV_THREADPOOL_SIZE");
		delete buffer1;
		*/

		char buffer[260];
		buffer[0] = '\0';
		size_t sz = sizeof(buffer);
		uv_exepath(buffer, &sz);
		string path = buffer;
		string confPath;
#ifdef WIN32
		int off = path.rfind('\\');
		confPath = path.substr(0, off);
		confPath += "\\config.json";
#else
		int off = path.rfind('/');
		confPath = path.substr(0, off);
		confPath += "/config.json";
		
#endif // WIN32
		//std::cout << confPath.c_str() << endl;

		return ;
	}

	uv_loop_t* GlobalConfig::getDefaultLoop()
	{
		if (loop == NULL)
			loop = uv_default_loop();
		return loop;
	}

	void GlobalConfig::setMsgDispatcher(std::shared_ptr<IDispatcher> dispatcher)
	{
		GlobalConfig::msgDispatcher = dispatcher;
	}

	std::shared_ptr<IDispatcher> GlobalConfig::getMsgDispatcher()
	{
		return msgDispatcher;
	}

	void GlobalConfig::setEncoder(std::shared_ptr <IEncoder> encoder)
	{
		GlobalConfig::msgEncoder = encoder;
	}

	std::shared_ptr <IEncoder> GlobalConfig::getEncoder()
	{
		return GlobalConfig::msgEncoder;
	}

	bool GlobalConfig::addWorkType(const string & name, IWorkPtr ptr)
	{
		auto it = workMap.find(name);
		if (it != workMap.end())
			return false;

		workMap.insert(std::pair<string, IWorkPtr>(name, ptr));

		return true;
	}

	IWorkPtr GlobalConfig::getWorkType(const string & name)
	{
		auto it = workMap.find(name);
		if (it != workMap.end())
			return it->second;

		return NULL;
	}
}
