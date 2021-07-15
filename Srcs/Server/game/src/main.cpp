// Add
#ifdef ENABLE_AUTO_EVENTS
#include "auto_event_manager.h"
	#ifdef ENABLE_AUTO_NOTICE
		#include "AutoNotice.h"
	#endif
#endif

// Find
	if (!start(argc, argv)) {
		CleanUpForEarlyExit();
		return 0;
	}

// Add above:
#ifdef ENABLE_AUTO_EVENTS
	CEventsManager	EventManager;
	#ifdef ENABLE_AUTO_NOTICE
		CAutoNotice	AutoNoticeManager;
	#endif
#endif

// Find
PanamaLoad();

// Add bellow:
#ifdef ENABLE_AUTO_EVENTS
	EventManager.Initialize();
#endif

// Find
	building_manager.Destroy();
	
// Add bellow:
#ifdef ENABLE_AUTO_EVENTS
	sys_log(0, "<shutdown> Destroying EventManager::CEventManager...");
	EventManager.Destroy();
#endif
