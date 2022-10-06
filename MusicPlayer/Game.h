#pragma once
#include "Clicker.h"
#include "MusicButtons.h"

class Game
{
private:
	
	Game() = delete;
	Game(const Game& g) = delete;
	Game& operator= (const Game& g) = delete;

	inline static vector<MusicButtons> songs = {}, allSongs = {};
	inline static Music* currentSong = nullptr;
	inline static short songIndex = 0;
	inline static float songLength = 0, songTimePlayed = 0;
	inline static bool UnpauseEvent = false;

	static void LoadSong(const bool& playNew = true);
	static void LoadAllSongs();
	static void LoadNewSongs(const bool& songDeleted = false);
	static void UserEventHandler();
	static void SongSearchHandler();
public:

	static void Initialize();
	static void DeInitialize();


	static void TitleScreenLogic(GameScreen& cs);
	static void TitleScreenDraw();
	static void GameplayLogic(GameScreen& cs);
	static void GameplayDraw();
	static void LoadingLogic(GameScreen& cs);
	static void LoadingDraw();
	
};

