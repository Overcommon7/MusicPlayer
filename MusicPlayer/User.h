#pragma once
enum class SortMethod
{
   Name,
   Length,
   Date
};

enum class TypingEvent
{
	Append,
	Delete,
	Nothing
};

class User
{
	User() = delete;
	User(const User& u) = delete;
	User& operator= (const User& u) = delete;
	inline static bool withinUIBounds = false;
	inline static bool paused = true;
	inline static bool loop = false;
	inline static bool next = false;
	inline static bool prev = false;
	inline static bool sortSongs = false;
	inline static KeyboardKey keyPressed = KEY_NULL;
	inline static float volume = 1.f;
	inline static short numOfSongs = 0.f;
	inline static SortMethod sortMethod = SortMethod::Length;
	inline static string songSearch = "";
	inline static TypingEvent typingEvent = TypingEvent::Nothing;

public:
	static const bool& WithinUIBounds() { return withinUIBounds; }
	static const bool& IsPaused() { return paused; }
	static const bool& Looping() { return loop; }
	static const bool& Next() { return next; }
	static const bool& Prev() { return prev; }
	static const float& GetVolume() { return volume; }
	static const KeyboardKey& GetKeyClicked() { return keyPressed; }
	static const short& NumberOfSongs() { return numOfSongs; }
	static const SortMethod& GetSortMethod() { return sortMethod; }
	static const bool& IsSortSongsRequested() { return sortSongs; }
	static const TypingEvent& GetTypingEvent() { return typingEvent; }
	static const string& GetSongSearchString() { return songSearch; }

	static void SetPaused(const bool& isPaused) { paused = isPaused; }
	static void SetLoop(const bool& doLoop) { loop = doLoop; }
	static void SetNext() { next = true; }
	static void SetPrev() { prev = true; }
	static void SetVolume(const float& newVol) { volume = newVol; }
	static void SetNumberOfSongs(const short& NumOfSongs) { numOfSongs = NumOfSongs; }
	static void SetSortMethod(const SortMethod& s) { sortMethod = s; }
	static void SetSortSongs(const bool& b) { sortSongs = b; }
	static void SetTypingEvent(const TypingEvent& t) { typingEvent = t; }
	static void SetSongSearch(const string& s) { songSearch = s; }
	
	
	static void Update();

};

