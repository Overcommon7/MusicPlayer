#pragma once
#include "Defines.h"

class UI
{
    UI() = delete;
    UI(const UI& u) = delete;
    UI& operator= (const UI& u) = delete;

    struct Button
    {
        bool colliding;
        Rectangle collider;
        std::function<void()> OnClickMethod;       
        Button(const Button& b)
        {
            collider = b.collider;
            colliding = b.colliding;
            OnClickMethod = b.OnClickMethod;
        }
        Button(const bool& Colliding, const Rectangle& Collider, const std::function<void()>& onClickMethod)
        {
            collider = Collider;
            colliding = Colliding;
            OnClickMethod = onClickMethod;
        }
    };

    struct Slider
    {
        Rectangle bar;
        Rectangle position;        
        bool scrubbing;
    };

    struct Scrollbar
    {
        Color color;
        Rectangle bar;
        bool adjusting;
    };

    struct TextBar
    {
        bool typing;
        string textureKey; 
        Rectangle collider;
        bool empty;
    };

   

    inline static string timeLeft = "0", timePlayed = "0";
    static void LoopMethod();
    static void NextMethod();
    static void PrevMethod();
    static void UpdateButtons();
    static void UpdateSlider(float& currentTime, const float& songTime, const Music* currentSong);
    static void UpdateVolume(const Music* currentSong);
    static void UpdateScrollBar();
    static void RegisterKeystrokes(float& currentTime, const float& songTime, const Music* currentSong);
    static void SortMethod();
    static void SortSelectionMenuLogic(GameScreen& cs);
    static void SortSelectionMenuDraw();
    static void SearchDraw();
    static void SearchLogic();
    static void Type(string& str);
     
        
    inline static unordered_map<string, pair<string, Button>> buttons = {};
    inline static Slider slider = { { 50, 55, SCREEN_WIDTH - 100, 5.f }, {51, 53, 3, 10}, false };
    inline static Slider volume = { {SCREEN_WIDTH - 25, 5.f, 5.f, 45.f}, {SCREEN_WIDTH - 28, 5.f, 12, 3.f}, false };

    inline static Scrollbar scrollbar = { DARKGRAY, {}, false };
    inline static TextBar searchBar = { false, K_ICON_SEARCH, {} };
    inline static int mouseCursor;

public:
    static void Draw();
    static void Update(float& currentTime, const float& songTime, const Music* currentSong, GameScreen& cs);
    static void Initialize();
    static void PausePlayMethod();
    

};
