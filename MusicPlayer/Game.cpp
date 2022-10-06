#include "pch.h"
#include "Game.h"
#include "Defines.h"
#include "IO.h"
#include "User.h"
#include "Utils.h"
#include "UI.h"

#pragma region System
void Game::LoadAllSongs()
{
#ifndef NDEBUG
	string root = "../";
#else
	string root = std::filesystem::current_path().generic_string();
#endif
	string copyPath = std::filesystem::current_path().generic_string() + "/Music/";
	for (const auto& file : std::filesystem::directory_iterator(root))
	{
		string ext = IO::GetFileExtension(file.path().filename().generic_string());
		if (ext == ".mp3"/* || ext == ".wav" || ext == ".ogg"*/)
		{
			string path = file.path().string();
			std::filesystem::copy(path, copyPath, std::filesystem::copy_options::overwrite_existing);
			std::remove(path.c_str());
		}		
	}

	float y = UIBOX.height;
	//for (short i = 0; i < 150; i++)
	for (const auto& file : std::filesystem::directory_iterator("Music/"))
	{
		string ext = IO::GetFileExtension(file.path().filename().generic_string());
		if (ext == ".mp3"/* || ext == ".wav" || ext == ".ogg"*/)
		{
			string path = file.path().string();
			string name = file.path().filename().generic_string();
			songs.push_back(MusicButtons(path, name.substr(0, name.find_last_of('.')), y));
			y += MUSIC_BUTTON_HEIGHT;
		}
	}
	User::SetNumberOfSongs((short)songs.size());
	allSongs = songs;
}

void Game::LoadNewSongs(const bool& songDeleted)
{
#ifndef NDEBUG
	string root = "../";
#else
	string root = std::filesystem::current_path().generic_string();
#endif
	bool newSongs = songDeleted;
	string copyPath = std::filesystem::current_path().generic_string() + "/Music/";
	for (const auto& file : std::filesystem::directory_iterator(root))
	{		
		string path = file.path().string();
		string ext = IO::GetFileExtension(file.path().filename().generic_string());
		if (ext != ".mp3"/* || ext != ".wav" || ext != ".ogg"*/) continue;
		string name = file.path().filename().generic_string();
		newSongs = true;
		try
		{
			std::filesystem::copy(path, copyPath, std::filesystem::copy_options::overwrite_existing);			
		}
		catch (std::exception& e)
		{
			cout << e.what() << '\n';
		}
		std::remove(path.c_str());
	}
	if (!newSongs) return;
	songs.clear();
	float y = UIBOX.height;
	for (const auto& file : std::filesystem::directory_iterator(std::filesystem::path(copyPath)))
	{
		string path = file.path().string();
		if (!IO::CheckFileExtension(path, ".mp3")) continue;
		string name = file.path().filename().generic_string();
		songs.push_back(MusicButtons(path, name.substr(0, name.find_last_of('.')), y));
		y += MUSIC_BUTTON_HEIGHT;
	}
	auto it = songs.begin();
	auto size = songs.size();
	while (it != songs.end())
	{
		if (std::filesystem::exists(it->GetFilePath()))	++it;
		else it = songs.erase(it);
	}
	User::SetNumberOfSongs((short)songs.size());
	allSongs = songs;
	if (size == songs.size()) return;
	y = UIBOX.height;
	for (auto& song : songs)
	{
		song.SetYPosition(y);
		y += MUSIC_BUTTON_HEIGHT;
	}
	
}

void Game::UserEventHandler()
{
	if (User::GetKeyClicked() == KEY_DELETE)
	{
		if (!currentSong) return;
		StopMusicStream(*currentSong);
		UnloadMusicStream(*currentSong);
		currentSong = nullptr;
		cout << std::remove(songs[songIndex].GetFilePath().c_str()) << '\n';
		songs.erase(songs.begin() + songIndex);
		allSongs = songs;
		User::SetNumberOfSongs((short)songs.size());
		songIndex = 0;
	}
	LoadNewSongs(User::GetKeyClicked() == KEY_DELETE);
	if (!currentSong) return;
	currentSong->looping = User::Looping();
	if (User::IsPaused() != UnpauseEvent)
	{
		if (User::IsPaused()) PauseMusicStream(*currentSong);
		else ResumeMusicStream(*currentSong);
		UnpauseEvent = User::IsPaused();
	}

	if (!User::IsPaused())
	{
		songTimePlayed += DT;
		if (!currentSong->looping && songTimePlayed >= songLength)
		{
			if (songIndex + 1 >= songs.size()) songIndex = 0;
			else ++songIndex;
			LoadSong();
		}
	}

	if (User::Next())
	{
		if (songIndex + 1 >= songs.size()) songIndex = 0;
		else ++songIndex;
		LoadSong();
	}
	else if (User::Prev())
	{
		if (songIndex - 1 < 0) songIndex = songs.size() - 1;
		else --songIndex;
		LoadSong();
	}
}

void Game::SongSearchHandler()
{
	if (User::GetSongSearchString().empty())
	{
		if (songs.size() != allSongs.size())
		{
			songs = allSongs;
			User::SetNumberOfSongs((short)songs.size());
		}			
		return;
	}
	if (User::GetTypingEvent() == TypingEvent::Nothing) return;
	else if (User::GetTypingEvent() == TypingEvent::Delete) songs = allSongs;
	songs.erase(std::remove_if(songs.begin(), songs.end(), [&](const MusicButtons& m) {
		return m.GetName().find(User::GetSongSearchString()) == string::npos;
		}), songs.end());
	float y = UIBOX.height;
	for (auto& song : songs)
	{
		song.SetYPosition(y);
		y += MUSIC_BUTTON_HEIGHT;
	}
	User::SetTypingEvent(TypingEvent::Nothing);
	User::SetNumberOfSongs((short)songs.size());
}

void Game::Initialize()
{
	fonts.insert({ K_FONT_DEFAULT, GetFontDefault() });
	fonts.insert({ K_FONT_CANDARA, LoadFont("CandaraBold.ttf")});

	textures.insert({ K_ICON_LOOP, LoadTexture("Images/Loop.png") });
	textures.insert({ K_ICON_LOOPING, LoadTexture("Images/Looping.png") });
	textures.insert({ K_ICON_NEXT, LoadTexture("Images/NextButton.png") });
	textures.insert({ K_ICON_PREV, LoadTexture("Images/PrevButton.png") });
	textures.insert({ K_ICON_PLAY, LoadTexture("Images/PlayButton.png") });
	textures.insert({ K_ICON_PAUSE, LoadTexture("Images/PauseButton.png") });
	textures.insert({ K_ICON_SORT, LoadTexture("Images/Sort.png") });
	textures.insert({ K_ICON_SEARCH, LoadTexture("Images/Search.png") });
	
	LoadAllSongs();
	UI::Initialize();
	
}

void Game::DeInitialize()
{
	for (auto& t : textures)
		UnloadTexture(t.second);
	for (auto& f : fonts)
		UnloadFont(f.second);
	if (!currentSong) return;
	StopMusicStream(*currentSong);
	UnloadMusicStream(*currentSong);
	delete currentSong;
}
#pragma endregion

#pragma region TitleScreen
void Game::TitleScreenLogic(GameScreen& cs)
{

}

void Game::TitleScreenDraw()
{

}
#pragma endregion

#pragma region GamePlay
void Game::LoadSong(const bool& playNew)
{
	if (!currentSong) return;
	StopMusicStream(*currentSong);
	UnloadMusicStream(*currentSong);
	if (playNew)
	{
		*currentSong = LoadMusicStream(songs[songIndex].GetFilePath().c_str());
		songLength = GetMusicTimeLength(*currentSong);
		PlayMusicStream(*currentSong);
		songTimePlayed = 0;
	}
	else
	{
		currentSong = nullptr;
		songIndex = 0;
	}
	User::SetPaused(true); 
	if (playNew) UI::PausePlayMethod();
	UnpauseEvent = User::IsPaused();
}

void Game::GameplayLogic(GameScreen& cs)
{
	SongSearchHandler();
	for (short i = 0; i < songs.size(); i++)
	{
		if (!songs[i].Update()) continue;
		if (!currentSong) currentSong = new Music();
		songIndex = i;
		LoadSong();
		break;
	}
	UI::Update(songTimePlayed, songLength, currentSong, cs);
	UserEventHandler();
	if (!currentSong) return;
	UpdateMusicStream(*currentSong);
}

void Game::GameplayDraw()
{
	for (const auto& m : songs)
	{
		if (m.GetYPosition() < UIBOX.height) continue;
		else if (m.GetYPosition() > SCREEN_HEIGHT) break;
		else m.Draw();
	}
		
	Utils::DrawRectangle(UIBOX, RAYWHITE);
	if (!songs.empty() && songIndex < songs.size())
		DrawTextEx(fonts.at(K_FONT_CANDARA), songs[songIndex].GetName().c_str(), { (SCREEN_WIDTH * 0.5f) - (MeasureTextEx(fonts.at(K_FONT_CANDARA), songs[songIndex].GetName().c_str(), 12.f, 1.f).x * 0.5f)
		,SLIDER_BAR.y + SLIDER_BAR.height + 4.f }, 12.f, 1.f, DARKGREEN);
	UI::Draw();
}
#pragma endregion

#pragma region Loading
void Game::LoadingLogic(GameScreen& cs)
{
	sort(songs.begin(), songs.end());
	float y = UIBOX.height;
	for (auto& s : songs)
	{
		s.SetYPosition(y);
		y += MUSIC_BUTTON_HEIGHT;
	}
	User::SetSortSongs(false);
	cs = GameScreen::Gameplay;
}

void Game::LoadingDraw()
{
	Vector2 textSize = MeasureTextEx(fonts.at(K_FONT_CANDARA), "LOADING...", 30.f, 1.f);
	DrawTextEx(fonts.at(K_FONT_CANDARA), "LOADING...", { (SCREEN_WIDTH * 0.5f) - (textSize.x * 0.5f), SCREEN_HEIGHT * 0.5f }, 30.f, 1.f, BLACK);
}
#pragma endregion