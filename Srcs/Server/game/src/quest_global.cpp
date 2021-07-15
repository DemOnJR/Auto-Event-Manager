	// TRIVIA
	
	int _add_trivia_quiz(lua_State* L)
	{
		const char* quiz = lua_tostring(L, 1);
		const char* answer = lua_tostring(L, 2);

		TriviaAddQuiz(quiz, answer);
		return 1;
	}

	int _add_trivia_reward(lua_State* L)
	{
		int index = (int)lua_tonumber(L, 1);
		int vnum = (int)lua_tonumber(L, 2);
		int count = (int)lua_tonumber(L, 3);

		TriviaAddReward(index, vnum, count);
		return 1;
	}
	
	// END_OF_TRIVIA
	
// add in > luaL_reg global_functions[] =

			// TRIVIA
			{	"add_trivia_quiz",			_add_trivia_quiz		},
			{	"add_trivia_reward",		_add_trivia_reward		},
			// END_OF_TRIVIA
