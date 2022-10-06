#include "pch.h"
#include "MusicButtons.h"
#include "Utils.h"
#include "Clicker.h"
#include "User.h"

void MusicButtons::Draw() const
{
    Utils::DrawRectangle(collider, BGColor);
    DrawTextEx(fonts.at(K_FONT_CANDARA), name.c_str(), { 10.f, collider.y + (MUSIC_BUTTON_HEIGHT * 0.55f) }, fontSize, 1.f, BLACK);
    if (colliding) Utils::DrawRectangle(collider, { 255, 255, 255, 120 });
}

bool MusicButtons::Update()
{
    collider.y += Clicker::GetMouseWheel();        
    if (User::WithinUIBounds()) return false;
    colliding = CheckCollisionRecs(Clicker::GetPointer(), collider);
    return Clicker::LeftClick() && colliding;
}

bool operator<(const MusicButtons& m1, const MusicButtons& m2)
{
    switch (User::GetSortMethod())
    {
    case SortMethod::Name:
        return m1.name < m2.name;
        break;
    case SortMethod::Length:
    {       
        return m1.songLength < m2.songLength;
    }   break;
    case SortMethod::Date:
        std::filesystem::path p1 = m1.filepath;
        std::filesystem::path p2 = m2.filepath;
        return std::filesystem::last_write_time(p1) < std::filesystem::last_write_time(p2);
        break;
    }
    return false;
}

bool operator==(const MusicButtons& m1, const MusicButtons& m2)
{
    return m1.name == m2.name || m1.filepath == m2.filepath;
}
