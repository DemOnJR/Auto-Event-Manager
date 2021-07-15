// find
#include "DragonSoul.h"

// add bellow:
#ifdef ENABLE_AUTO_EVENTS
#include "auto_event_manager.h"
	#ifdef ENABLE_AUTO_NOTICE
		#include "AutoNotice.h"
	#endif
#endif

// find
#ifdef __AUCTION__
	AuctionManager auctionManager;
#endif

//add bellow:
#ifdef ENABLE_AUTO_EVENTS
	CEventsManager	EventManager;
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
