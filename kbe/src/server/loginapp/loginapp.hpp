/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef __LOGINAPP_H__
#define __LOGINAPP_H__
	
// common include	
#include "server/kbemain.hpp"
#include "server/serverapp.hpp"
#include "server/idallocate.hpp"
#include "server/serverconfig.hpp"
#include "cstdkbe/timer.hpp"
#include "network/endpoint.hpp"

//#define NDEBUG
#include <map>	
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif
	
namespace KBEngine{

class Loginapp :	public ServerApp, 
					public TimerHandler, 
					public Singleton<Loginapp>
{
public:
	enum TimeOutType
	{
		TIMEOUT_GAME_TICK,
		TIMEOUT_LOADING_TICK
	};
	
	Loginapp(Mercury::EventDispatcher& dispatcher, 
		Mercury::NetworkInterface& ninterface, 
		COMPONENT_TYPE componentType,
		COMPONENT_ID componentID);

	~Loginapp();
	
	bool run();
	
	void handleTimeout(TimerHandle handle, void * arg);

	/* 初始化相关接口 */
	bool initializeBegin();
	bool inInitialize();
	bool initializeEnd();
	void finalise();

	/** 网络接口
		dbmgr发送初始信息
		startGlobalOrder: 全局启动顺序 包括各种不同组件
		startGroupOrder: 组内启动顺序， 比如在所有baseapp中第几个启动。
	*/
	void onDbmgrInitCompleted(Mercury::Channel* pChannel, int32 startGlobalOrder, int32 startGroupOrder);
protected:
};

}
#endif
