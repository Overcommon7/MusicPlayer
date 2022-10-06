#pragma once
#include "Defines.h"

class MusicButtons
{
	string name;
	string filepath;
	Rectangle collider;
	bool colliding;
	long songLength;
	inline static Color BGColor = { 120 };
	inline static float fontSize = 12.f;
public:
	MusicButtons(const string& FilePath, const string& Name, const float& y) : name(Name), filepath(FilePath), collider({ 0, y, SCREEN_WIDTH - 7.f, MUSIC_BUTTON_HEIGHT }), colliding(false)
	{
		std::bitset<4> b;

		unsigned char temp1;
		fstream in(filepath);
		in.seekg(2);
		in >> temp1;
		in.close();
		b = temp1;
		int bitRate = (b.to_ulong() - 10) + 160;
		songLength = (std::filesystem::file_size(filepath) / bitRate);
	}
	MusicButtons(const MusicButtons& m) = default;
	friend bool operator< (const MusicButtons& m1, const MusicButtons& m2);
	friend bool operator== (const MusicButtons& m1, const MusicButtons& m2);

	void Draw() const;
	bool Update();

	void SetYPosition(const float& y) { collider.y = y; }

	const string& GetFilePath() const { return filepath; }
	const float& GetYPosition() const { return collider.y; }
	const string& GetName() const { return name; }
	

};

