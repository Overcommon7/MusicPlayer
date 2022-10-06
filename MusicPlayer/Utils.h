#pragma once
#include "pch.h"
#include "Defines.h"

namespace Utils
{
    template<typename T>
    static T Random(const T& includedMax, const T& includedMin = 0, const std::pair<T, T>& ExcludeRange = { 0, 0 }, const vector<T>& exclude = {})
    {
        bool range = false;
        bool isValid = true;
        T value{};
        if (ExcludeRange.first != ExcludeRange.second) range = true;
        std::random_device r;

        do
        {
            isValid = true;
            std::mt19937 gen(r());
            std::uniform_int_distribution<T> dist(includedMin, includedMax);
            value = dist(gen);
            for (const auto& i : exclude)
                if (i == value)
                {
                    isValid = false;
                    break;
                }
            if (range && isValid)
                if (value >= ExcludeRange.first && value <= ExcludeRange.second)
                    isValid = false;
        } while (!isValid);
        return value;
    }

    static void DrawRectangle(const Rectangle& r, const Color& c = BLACK)
    {
        DrawRectangle(r.x, r.y, r.width, r.height, c);
    }

    static void DrawRectangleLines(const Rectangle& r, const Color& c = BLACK)
    {
        DrawRectangleLines(r.x, r.y, r.width, r.height, c);
    }

    static bool Equals(const Vector2& v1, const Vector2& v2)
    {
        return v1.x == v2.x && v1.y == v2.y;
    }

    static bool Equals(const Vector3& v1, const Vector3& v2)
    {
        return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    }

    static bool Equals(const Color& v1, const Color& v2)
    {
        return v1.r == v2.r && v1.g == v2.g && v1.b == v2.b && v1.a == v2.a;
    }

    static string SecondsToTime(const float& seconds)
    {
        if (seconds < 1.f) return "0:00";
        float hr = seconds * 0.0002777778f;
        int hours = ((int)hr);
        float minutes = hr - (float)hours;
        minutes *= 60;
        float remainder = minutes - (float)((int)minutes);
        int mins = (int)minutes;
        int secs = (int)(remainder * 60.f);
        string h = to_string(hours);
        string m = to_string(mins);
        string s = to_string(secs);
        if (s.length() < 2) s.insert(0, "0");
        if (hours <= 0) return m + ":" + s;
        if (m.length() < 2) m.insert(0, "0");        
        return h + ":" + m + ":" + s;
    }
}
