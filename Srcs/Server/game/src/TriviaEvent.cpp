#include "stdafx.h"
#include "constants.h"
#include "config.h"
#include "questmanager.h"
#include "char.h"
#include "char_manager.h"
#include "TriviaEvent.h"
#include "desc.h"
#include <boost/algorithm/string.hpp>
#include "cmd.h"
#include "item.h"
#include "item_manager.h"

typedef std::map<std::string, std::string> trivia_map_quiz;
typedef std::map<DWORD, sRewardTrivia> trivia_map_reward;

trivia_map_quiz m_map_quiz_trivia;
trivia_map_reward m_map_reward_trivia;

void TriviaClear()
{
	m_map_quiz_trivia.clear();
	m_map_reward_trivia.clear();
}

bool TriviaAddQuiz(const char* pszQuestion, const char* pszAnswer)
{
	m_map_quiz_trivia.emplace(pszQuestion, pszAnswer);
	return true;
}

bool TriviaAddReward(int index, DWORD dwVnum, DWORD dwCount)
{
	sRewardTrivia NewReward;
	NewReward.dwVnum = dwVnum;
	NewReward.dwCount = dwCount;
	
	m_map_reward_trivia.emplace(index, NewReward);
	return true;
}

bool TriviaIsEqualAnswer(int index, std::string stMyAnswer)
{
	if (m_map_quiz_trivia.empty() || stMyAnswer.empty())
		return false;
	
	// PM_IN_CHAT_SUBSTR@@
	std::string stAnswer = stMyAnswer;
	std::size_t sPos = stMyAnswer.find("|r");
	
	if (sPos > 0 && sPos < stMyAnswer.size() - 3)
	{
		stAnswer = stMyAnswer.substr(sPos + 3);
	}
	
	if (stAnswer.empty())
		return false;
	// PM_IN_CHAT_SUBSTR

	int iCount = 0;
	for (itertype(m_map_quiz_trivia) it = m_map_quiz_trivia.begin(); it != m_map_quiz_trivia.end(); ++it, ++iCount)
	{
		if (index != iCount)
			continue; // just for same question, continue for the remain
		
		std::string stAnwer = it->second;
		
		if (stAnwer.empty())
			continue; // crash in case of bad input from question
		
		if (boost::iequals(stAnwer, stAnswer))
			return true;
	}

	return false;
}

bool TriviaGiveRewardRandom(LPCHARACTER ch)
{
	if (!ch)
		return false;
	
	if (m_map_reward_trivia.empty() || m_map_reward_trivia.size() == 0)
	{
		sys_err( "CTriviaManager> EMPTY REWARD MAP" );
		return false;
	}
	
	DWORD dwReward = number(0, m_map_reward_trivia.size() - 1); // get a rand() reward.
	itertype(m_map_reward_trivia) iter = m_map_reward_trivia.find(dwReward);
	
	if (iter == m_map_reward_trivia.end())
	{
		sys_err( "CTriviaManager> COULDNT ACCES REWARD MAP" );
		return false;		
	}
	
	LPITEM item = ch->AutoGiveItem(iter->second.dwVnum, iter->second.dwCount);
	
	char szNotice[246+1];

	if (item)
		snprintf(szNotice, sizeof(szNotice), "[Trivia-Winner]: %s a castigat %s.", ch->GetName(), item->GetName());
	else
		snprintf(szNotice, sizeof(szNotice), "[Trivia-Winner]: %s a castigat.", ch->GetName());

	BroadcastNotice(szNotice);
	return true;
}

bool IsTriviaOpen()
{
	if (quest::CQuestManager::instance().GetEventFlag("eveniment_trivia") == 1)
		return true;
	
	return false;
}

void TriviaBroadCastQuiz(int index)
{
	if (m_map_quiz_trivia.empty())
		return;

	int iCount = 0;
	for (itertype(m_map_quiz_trivia) it = m_map_quiz_trivia.begin(); it != m_map_quiz_trivia.end(); ++it, ++iCount)
	{
		if (index != iCount)
			continue; // just for same question, continue for the remain
		
		std::string stQuestion = it->first;
		std::string stAnwer = it->second;

		if (stAnwer.empty() || stQuestion.empty())
			continue;
		
		BroadcastNotice("Raspunde corect (pe chat global) la urmatoarea intrebare pentru a castiga un premiu!");
		
		char szNotice[246+1];
		snprintf(szNotice, sizeof(szNotice), "[TRIVIA]: %s", stQuestion.c_str());
		BroadcastNotice(szNotice);
		
		break;
	}
}

void SetTriviaStatus(bool bStatus)
{
	if (bStatus)
	{
		if (m_map_quiz_trivia.empty())
			return;

		// AUTO_SELECT_QUESTION
		int iRandQuestion = number(0, m_map_quiz_trivia.size() - 1);
		quest::CQuestManager::instance().SetEventFlag("eveniment_trivia_q", iRandQuestion);
		quest::CQuestManager::instance().RequestSetEventFlag("eveniment_trivia_q", iRandQuestion);
		TriviaBroadCastQuiz(iRandQuestion);
		// AUTO_SELECT_QUESTION
		
		quest::CQuestManager::instance().SetEventFlag("eveniment_trivia", 1);
		quest::CQuestManager::instance().RequestSetEventFlag("eveniment_trivia", 1);
	}
	else
	{
		quest::CQuestManager::instance().SetEventFlag("eveniment_trivia", 0);
		quest::CQuestManager::instance().RequestSetEventFlag("eveniment_trivia", 0);
	}
}
