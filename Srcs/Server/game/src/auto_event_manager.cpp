#include "stdafx.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "utils.h"
#include "config.h"
#include "constants.h"
#include "questmanager.h"

// hmm
#include "cmd.h"
#include "desc.h"
#include "char.h"
#include "char_manager.h"

#ifdef ENABLE_AUTO_EVENTS
#include "auto_event_manager.h"

#ifdef ENABLE_AUTO_NOTICE
#include "AutoNotice.h"
#endif

#ifdef ENABLE_TRIVIA
#include "TriviaEvent.h"
#include "locale_service.h"
#endif

static LPEVENT running_event = NULL;

EVENTINFO(EventsManagerInfoData)
{
	CEventsManager *pEvents;

	EventsManagerInfoData()
	: pEvents(0)
	{
	}
};

EVENTFUNC(automatic_event_timer)
{
	if (event == NULL)
		return 0;

	if (event->info == NULL)
		return 0;

	EventsManagerInfoData* info = dynamic_cast<EventsManagerInfoData*>(event->info);

	if (info == NULL)
		return 0;
	
	CEventsManager* pInstance = info->pEvents;

	if (pInstance == NULL)
		return 0;
	
	CEventsManager::instance().PrepareChecker();
	return PASSES_PER_SEC(1);
}

void CEventsManager::PrepareChecker()
{
	time_t cur_Time = time(NULL);
	struct tm vKey = *localtime(&cur_Time);

	int day = vKey.tm_wday;
	int hour = vKey.tm_hour;
	int minute = vKey.tm_min;
	int second = vKey.tm_sec;

#ifdef ENABLE_AUTO_NOTICE
	CAutoNotice::instance().Check(day, hour, minute, second);
#endif

	CEventsManager::instance().Check(day, hour, minute, second);
}

void CEventsManager::Check(int day, int hour, int minute, int second)
{
#ifdef ENABLE_TRIVIA
	if (g_bChannel == 99)
	{
		if (quest::CQuestManager::instance().GetEventFlag("enable_trivia_refresh") == 1)
		{
			// REFRESH_TABLE_TRIVIADOR
			if (!IsTriviaOpen())
			{
				TriviaClear();

				char script[256];
				snprintf(script, sizeof(script), "%s/trivia.lua", LocaleService_GetBasePath().c_str());
				lua_dofile(quest::CQuestManager::instance().GetLuaState(), script);
				
				quest::CQuestManager::instance().SetEventFlag("enable_trivia_refresh", 0); // stop refresh;
			}
			// REFRESH_TABLE_TRIVIADOR
		}
		
		if (quest::CQuestManager::instance().GetEventFlag("enable_trivia") == 1)
		{
			// REMAINDER_QUESTION
			if (second == 1)
			{
				if (IsTriviaOpen())
				{
					int iRandQuestion = quest::CQuestManager::instance().GetEventFlag("eveniment_trivia_q");
					TriviaBroadCastQuiz(iRandQuestion);
				}
			}
			// REMAINDER_QUESTION

			if (second == 1 && (minute == 10 || minute == 20 || minute == 30 || minute == 40 || minute == 50 || minute == 59) && !IsTriviaOpen()) // Open-Triviador
			{
				//BroadcastNotice("Evenimentul Triviador a fost pornit!");
				SetTriviaStatus(true);
			}
			else if (second == 1 && (minute == 15 || minute == 25 || minute == 35 || minute == 45 || minute == 55 || minute == 5) && IsTriviaOpen()) // Close-Triviador
			{
				//BroadcastNotice("Evenimentul Triviador a fost oprit!");
				SetTriviaStatus(false);
			}
		}
		
		// FORCE_CLOSE_TRIVIA
		if (IsTriviaOpen() && quest::CQuestManager::instance().GetEventFlag("enable_trivia") == 0)
		{
			SendNotice("Evenimentul Triviador a fost oprit fortat!");
			SetTriviaStatus(false);
		}
		// FORCE_CLOSE_TRIVIA
	}
#endif
}

bool CEventsManager::Initialize()
{
	if (running_event != NULL)
	{
		event_cancel(&running_event);
		running_event = NULL;
	}

	EventsManagerInfoData* info = AllocEventInfo<EventsManagerInfoData>();
	info->pEvents = this;

	running_event = event_create(automatic_event_timer, info, PASSES_PER_SEC(30));
	return true;
}

void CEventsManager::Destroy()
{

	if (running_event != NULL)
	{
		event_cancel(&running_event);
		running_event = NULL;
	}
}
#endif