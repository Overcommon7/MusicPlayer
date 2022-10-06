#include "pch.h"
#include "UI.h"
#include "Clicker.h"
#include "User.h"
#include "Utils.h"

void UI::LoopMethod()
{
	User::SetLoop(!User::Looping());
	if (User::Looping()) buttons.at(K_ICON_LOOP).first = K_ICON_LOOPING;
	else buttons.at(K_ICON_LOOP).first = K_ICON_LOOP;
}

void UI::PausePlayMethod()
{
	if (User::IsPaused())
	{
		User::SetPaused(false);	
		buttons.at(K_ICON_PLAY).first = K_ICON_PAUSE;		
	}
	else
	{
		User::SetPaused(true);
		buttons.at(K_ICON_PLAY).first = K_ICON_PLAY;
	}	
}


void UI::NextMethod()
{
	User::SetNext();
}

void UI::PrevMethod()
{
	User::SetPrev();
}

void UI::UpdateButtons()
{
	for (auto& b : buttons)
	{
		b.second.second.colliding = CheckCollisionRecs(Clicker::GetPointer(), b.second.second.collider);
		if (!b.second.second.colliding) continue;
		if (!Clicker::LeftClick()) continue;
		b.second.second.OnClickMethod();
		break;
	}
}

void UI::UpdateSlider(float& currentTime, const float& songTime, const Music* currentSong)
{
	float division = currentTime / songTime;
	slider.position.x = slider.bar.x + (slider.bar.width * division);
	timeLeft = Utils::SecondsToTime(songTime - currentTime);
	timePlayed = Utils::SecondsToTime(currentTime);

	if ((slider.scrubbing && Clicker::LeftUp()) 
		|| (Clicker::LeftClick() && CheckCollisionRecs(Clicker::GetPointer(), slider.bar)))
	{	
		if (!currentSong) return;
		slider.scrubbing = false;
		slider.position.x = Clicker::GetPosition().x;
		if (slider.position.x < slider.bar.x + 1)
			slider.position.x = slider.bar.x + 1;
		if (slider.position.x > slider.bar.x + slider.bar.width - 1)
			slider.position.x = slider.bar.x + slider.bar.width - 1;
		division = (slider.position.x - slider.bar.x) / slider.bar.width;
		currentTime = songTime * division;		
		SeekMusicStream(*currentSong, currentTime);
		return;
	}
	if (Clicker::LeftDown() && CheckCollisionRecs(Clicker::GetPointer(), slider.position)) slider.scrubbing = true;
	if (!slider.scrubbing) return;
	slider.position.x = Clicker::GetPosition().x;
	if (slider.position.x < slider.bar.x + 1)
		slider.position.x = slider.bar.x + 1;
	if (slider.position.x > slider.bar.x + slider.bar.width - 1)
		slider.position.x = slider.bar.x + slider.bar.width - 1;
}

void UI::UpdateVolume(const Music* currentSong)
{
	if ((volume.scrubbing && Clicker::LeftUp())
		|| (Clicker::LeftClick() && CheckCollisionRecs(Clicker::GetPointer(), volume.bar)))
	{
		volume.scrubbing = false;
		volume.position.y = Clicker::GetPosition().y; 
		if (volume.position.y < volume.bar.y)
			volume.position.y = volume.bar.y;
		if (volume.position.y > volume.bar.y + volume.bar.height)
			volume.position.y = volume.bar.y + volume.bar.height;
		float vol = (volume.position.y - volume.bar.y) / (volume.bar.height + volume.bar.y);
		vol = abs(vol - 0.9f);
		SetMasterVolume(vol);
	}
	if (Clicker::LeftDown() && CheckCollisionRecs(Clicker::GetPointer(), volume.position)) volume.scrubbing = true;
	if (!volume.scrubbing) return;
	volume.position.y = Clicker::GetPosition().y;
	if (volume.position.y < volume.bar.y)
		volume.position.y = volume.bar.y;
	if (volume.position.y > volume.bar.y + volume.bar.height)
		volume.position.y = volume.bar.y + volume.bar.height;
}

void UI::UpdateScrollBar()
{
	if (scrollbar.adjusting && Clicker::LeftUp())
	{
		scrollbar.bar.y = Clicker::GetPosition().y - (scrollbar.bar.y + scrollbar.bar.height - Clicker::GetPosition().y);
		if (scrollbar.bar.y < SCREEN_HEIGHT - UIBOX.height) scrollbar.bar.y = SCREEN_HEIGHT - UIBOX.height;
		if (scrollbar.bar.y + scrollbar.bar.height > SCREEN_HEIGHT) scrollbar.bar.y = SCREEN_HEIGHT - scrollbar.bar.height;
		scrollbar.adjusting = false;
		scrollbar.color = DARKGRAY;
		return;
	}
	if (Clicker::LeftDown() && CheckCollisionRecs(scrollbar.bar, Clicker::GetPointer())) scrollbar.adjusting = true;
	if (!scrollbar.adjusting) return;
	scrollbar.color = LIGHTGRAY;
	scrollbar.bar.y = Clicker::GetPosition().y - (scrollbar.bar.y + scrollbar.bar.height - Clicker::GetPosition().y);
	if (scrollbar.bar.y < SCREEN_HEIGHT - UIBOX.height) scrollbar.bar.y = SCREEN_HEIGHT - UIBOX.height;
	if (scrollbar.bar.y + scrollbar.bar.height > SCREEN_HEIGHT) scrollbar.bar.y = SCREEN_HEIGHT - scrollbar.bar.height;
	return;
	
}

void UI::RegisterKeystrokes(float& currentTime, const float& songTime, const Music* currentSong)
{
	if (currentSong)
	{
		if (User::GetKeyClicked() == KEY_RIGHT)
		{
			currentTime += 5.f;
			if (currentTime > songTime) currentTime = songTime;
			SeekMusicStream(*currentSong, currentTime);
		}
		else if (User::GetKeyClicked() == KEY_LEFT)
		{
			currentTime -= 5.f;
			if (currentTime < 0.f) currentTime = 0.1f;
			SeekMusicStream(*currentSong, currentTime);
		}
	}
	
	if (User::GetKeyClicked() == KEY_SPACE)
		PausePlayMethod();
	else if (User::GetKeyClicked() == KEY_PAGE_UP)
		NextMethod();
	else if (User::GetKeyClicked() == KEY_PAGE_DOWN)
		PrevMethod();
	else if (User::GetKeyClicked() == KEY_R)
		LoopMethod();
}

void UI::SortMethod()
{
	User::SetSortSongs(true);
}

void UI::SortSelectionMenuLogic(GameScreen& cs)
{
	switch (User::GetKeyClicked())
	{
	case KEY_N:
		User::SetSortMethod(SortMethod::Name);
		break;
	case KEY_L:
		User::SetSortMethod(SortMethod::Length);
		break;
	case KEY_D:
		User::SetSortMethod(SortMethod::Date);		
		break;
	case KEY_ESCAPE:
		User::SetSortSongs(false);
		return;
		break;
	default:
		return;
		break;
	}
	cs = GameScreen::Loading;
}

void UI::SortSelectionMenuDraw()
{
	DrawRectangle(0, 0, SCREEN_WIDTH, UIBOX.y - ((slider.position.y + slider.position.height) - slider.position.y), RAYWHITE);
	DrawTextEx(fonts.at(K_FONT_CANDARA), "Sort By:\nName->N - Song Length->L - Date Added->D", { slider.bar.x + 10.f, 5.f }, 15.f, 1.f, BLACK);
}

void UI::SearchDraw()
{
	DrawTexture(textures.at(K_ICON_SEARCH), searchBar.collider.x, searchBar.collider.y, WHITE);
	DrawTextEx(fonts.at(K_FONT_CANDARA), User::GetSongSearchString().c_str(), { searchBar.collider.x + 7.f, searchBar.collider.y + 10.f }, 13.f, 1.f, BLACK);
}
void UI::Type(string& str)
{
	static bool CapsLock = false;
	int key = User::GetKeyClicked();
	if (key == KEY_CAPS_LOCK)
	{
		CapsLock = !CapsLock;
		return;
	}
	if (key == KEY_BACKSPACE && !str.empty())
	{
		str.pop_back();		
		return;
	}
	if (key < 32) return;
	if (key > 126) return;
	if ((CapsLock || (IsKeyUp(KEY_LEFT_SHIFT) && IsKeyUp(KEY_RIGHT_SHIFT))) && isalpha(key))
			key += ((int)'a' - (int)'A');
	if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && isdigit(key))
		switch (key)
			{
			case '0':
				key = '(';
				break;
			case '1':
				key = ')';
				break;
			case '2':
				key = '@';
				break;
			case '3':
				key = '#';
				break;
			case '4':
				key = '$';
				break;
			case '5':
				key = '%';
				break;
			case '6':
				key = '^';
				break;
			case '7':
				key = '&';
				break;
			case '9':
				key = '(';
				break;
			default:
				return;
				break;
			}
	str += (char)key;
	
}

void UI::SearchLogic()
{
	if (Clicker::LeftClick())
	{
		if (CheckCollisionRecs(searchBar.collider, Clicker::GetPointer())) searchBar.typing = true;
		else searchBar.typing = false;
	}
	if (!searchBar.typing)
	{
		if (mouseCursor != 0)
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
			mouseCursor = 0;
		return;
	}
	if (mouseCursor != 2)
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
	mouseCursor = 2;
	string temp = User::GetSongSearchString();
	Type(temp);
	if (User::GetSongSearchString() == temp)
		User::SetTypingEvent(TypingEvent::Nothing);
	else if (temp.length() < User::GetSongSearchString().length())
		User::SetTypingEvent(TypingEvent::Delete);
	else 
		User::SetTypingEvent(TypingEvent::Append);
	User::SetSongSearch(temp);	
}

void UI::Draw()
{
	if (User::IsSortSongsRequested())
		SortSelectionMenuDraw();
	else
	{
		for (const auto& b : buttons)
		{
			DrawTexture(textures.at(b.second.first), b.second.second.collider.x, b.second.second.collider.y, WHITE);
			if (!b.second.second.colliding) continue;
			Utils::DrawRectangle(b.second.second.collider, { 255, 255, 255, 100 });
		}
		SearchDraw();
	}
		

	Utils::DrawRectangle(slider.bar, LIGHTGRAY);
	Utils::DrawRectangle(slider.position, RED);

	DrawTextEx(fonts.at(K_FONT_CANDARA), timePlayed.c_str(), { slider.bar.x - 30.f, slider.bar.y }, 12.f, 1.f, BLACK);
	DrawTextEx(fonts.at(K_FONT_CANDARA), timeLeft.c_str(), { slider.bar.x + slider.bar.width + 5.f, slider.bar.y }, 12.f, 1.f, BLACK);
	Utils::DrawRectangle(volume.bar, LIGHTGRAY);
	Utils::DrawRectangle(volume.position, RED);	
	Utils::DrawRectangle(scrollbar.bar, scrollbar.color);
}

void UI::Update(float& currentTime, const float& songTime, const Music* currentSong, GameScreen& cs)
{
	if (!searchBar.typing) RegisterKeystrokes(currentTime, songTime, currentSong);
	UpdateSlider(currentTime, songTime, currentSong);
	UpdateVolume(currentSong);
	UpdateScrollBar();	
	if (User::IsSortSongsRequested()) SortSelectionMenuLogic(cs);
	else SearchLogic();
	if (!User::WithinUIBounds()) return;
	UpdateButtons();
	return;
	
}

void UI::Initialize()																						 
{
	{
		const vector<pair<string, std::function<void()>>> keys = 
		{ {K_ICON_LOOP, &LoopMethod} ,{ K_ICON_PREV, &PrevMethod }, { K_ICON_NEXT, &NextMethod }, { K_ICON_PLAY, &PausePlayMethod }, {K_ICON_SORT, &SortMethod } };
		for (float i = 0, x = 75.f; i < keys.size(); i++, x += 55.f)
			buttons.insert({ keys[i].first, pair<string, Button>(keys[i].first, {false, {x, 0, (float)textures.at(keys[i].first).width, (float)textures.at(keys[i].first).height}, keys[i].second}) });
	}

	searchBar.collider = { buttons.end().operator--()->second.second.collider.x + buttons.end().operator--()->second.second.collider.width + 5, 15.f, 
		(float)textures.at(K_ICON_SEARCH).width, (float)textures.at(K_ICON_SEARCH).height };

	scrollbar.bar.y = UIBOX.height;
	if (User::NumberOfSongs() * MUSIC_BUTTON_HEIGHT <= SCREEN_HEIGHT - UIBOX.height) return;
	scrollbar.bar.width = 7.f;
	scrollbar.bar.x = SCREEN_WIDTH - scrollbar.bar.width;
	scrollbar.bar.height = (User::NumberOfSongs() - (User::NumberOfSongs() - ((SCREEN_HEIGHT - UIBOX.height) / MUSIC_BUTTON_HEIGHT))) * MUSIC_BUTTON_HEIGHT;
}
