// Add this include:

#include "TriviaEvent.h"

// Search:

	if (CHAT_TYPE_SHOUT == pinfo->type)
	{
		LogManager::instance().ShoutLog(ch->GetName(), buf);
	}

// Add in if statement:

		// TRIVIA
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
		// END_OF_TRIVIA
