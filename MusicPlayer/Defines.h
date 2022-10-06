#pragma once
extern unordered_map<string, Texture2D> textures;
extern unordered_map<string, Font> fonts;
extern Rectangle UIBOX;
extern const Rectangle SLIDER_BAR;
extern float DeltaTime;
extern float SCREEN_WIDTH, SCREEN_HEIGHT;
extern float WINDOW_SCALE;
extern const float MAX_WIDTH, MAX_HEIGHT;
extern const bool ReleaseMode;

#define DT DeltaTime
#define MUSIC_BUTTON_HEIGHT 50.f

#define K_FONT_DEFAULT "Default"
#define K_FONT_CANDARA "Candara"

#define K_ICON_LOOP "Loop"
#define K_ICON_NEXT "Next"
#define K_ICON_PREV "Prev"
#define K_ICON_PAUSE "Pause"
#define K_ICON_PLAY "Play"
#define K_ICON_LOOPING "Looping"
#define K_ICON_SORT "Sort"
#define K_ICON_SEARCH "Search"
