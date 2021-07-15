// add
#ifdef ENABLE_AUTO_EVENTS
#include "auto_event_manager.h"
	#ifdef ENABLE_AUTO_NOTICE
		#include "AutoNotice.h"
	#endif
#endif

// find
	if (!start(argc, argv)) {
		CleanUpForEarlyExit();
		return 0;
	}

//add above:
#ifdef ENABLE_AUTO_EVENTS
	CEventsManager	EventManager;
	#ifdef ENABLE_AUTO_NOTICE
		CAutoNotice	AutoNoticeManager;
	#endif
#endif

// find
PanamaLoad();

// add bellow:
#ifdef ENABLE_AUTO_EVENTS
	EventManager.Initialize();
#endif

// find
	building_manager.Destroy();
	
//add bellow:
#ifdef ENABLE_AUTO_EVENTS
	sys_log(0, "<shutdown> Destroying EventManager::CEventManager...");
	EventManager.Destroy();
#endif
