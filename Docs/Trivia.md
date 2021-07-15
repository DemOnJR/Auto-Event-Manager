Commands in_game:
/e enable_trivia 1 - For Open Trivia
/e enable_trivia 0 - For Close Trivia (force)

All commands need to be used on ch: 99 (event's channel, be sure in CONFIG it's CHANNEL: 99).

Configuration for open-close trivia (auto_event_manager.cpp):

	if (second == 1 && (minute == 10 || minute == 20 || minute == 30 || minute == 40 || minute == 50 || minute == 59) && !IsTriviaOpen()) // Open-Triviador
	{
		BroadcastNotice("Evenimentul Triviador a fost pornit!");
		SetTriviaStatus(true);
	}

	else if (second == 1 && (minute == 15 || minute == 25 || minute == 35 || minute == 45 || minute == 55 || minute == 5) && IsTriviaOpen()) // Close-Triviador
	{
		BroadcastNotice("Evenimentul Triviador a fost oprit!");
		SetTriviaStatus(false);
	}

// trivia is open:
- minute == 10 || minute == 20 || minute == 30 || minute == 40 || minute == 50 || minute == 59

// trivia is close:
- minute == 15 || minute == 25 || minute == 35 || minute == 45 || minute == 55 || minute == 5

Contact discord: Grimm#3010
