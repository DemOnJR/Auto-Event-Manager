#ifndef _METIN_II_TRIVIA_H_
#define _METIN_II_TRIVIA_H_

#include <boost/unordered_map.hpp>

class CHARACTER;

struct sRewardTrivia
{
	DWORD dwVnum;
	DWORD dwCount;
};

bool TriviaAddQuiz(const char* pszQuestion, const char* pszAnswer);
bool TriviaAddReward(int index, DWORD dwVnum, DWORD dwCount);

bool TriviaGiveRewardRandom(LPCHARACTER ch);
bool IsTriviaOpen();
bool TriviaIsEqualAnswer(int index, std::string stMyAnswer);

void SetTriviaStatus(bool bStatus);
void TriviaBroadCastQuiz(int index);

void TriviaClear();
#endif
