// Add
#ifdef ENABLE_AUTO_EVENTS
	#ifdef ENABLE_TRIVIA
		#include "TriviaEvent.h"
	#endif
#endif

// Search:
	if (CHAT_TYPE_SHOUT == pinfo->type)
	{
		LogManager::instance().ShoutLog(ch->GetName(), buf);
	}
	
// Change like this
	if (CHAT_TYPE_SHOUT == pinfo->type)
	{
		LogManager::instance().ShoutLog(ch->GetName(), buf);
#ifdef ENABLE_TRIVIA
		std::string stAnswer = buf;
		int iQuizTrivia = quest::CQuestManager::instance().GetEventFlag("eveniment_trivia_q");
		if (IsTriviaOpen() && TriviaIsEqualAnswer(iQuizTrivia, stAnswer))
		{
			// if (ch->GetLevel() >= 15) // check level you can uncomment
			// {
				SetTriviaStatus(false);
				TriviaGiveRewardRandom(ch);
			// }
		}
#endif
	}