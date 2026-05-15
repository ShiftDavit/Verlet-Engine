#pragma once

#include <cmath>

namespace verlet
{
    struct Vec2
    {
        float x;
        float y;

        float magnitude() const
        {
            return std::sqrt(x * x + y * y);
        }

        float distance(const Vec2 &other) const
        {
            float diffX = x - other.x;
            float diffY = y - other.y;

            return std::sqrt(diffX * diffX + diffY * diffY);
        }

        Vec2 unit()
        {
            float mag = magnitude();
            if (mag < 1e-6)
            { // Avoid division by 0
                return Vec2{0, 0};
            }

            return Vec2{x / mag, y / mag};
        }

        inline Vec2 operator+(const Vec2 &other) const
        {
            return Vec2{x + other.x, y + other.y};
        }

        inline Vec2 operator-(const Vec2 &other) const
        {
            return Vec2{x - other.x, y - other.y};
        }

        inline Vec2 &operator-=(const Vec2 &other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        inline Vec2 &operator+=(const Vec2 &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        inline Vec2 operator*(float factor) const
        {
            return Vec2{x * factor, y * factor};
        }

        inline Vec2 operator/(float factor) const
        {
            if (factor == 0)
                factor = 1;
            return Vec2{x / factor, y / factor};
        }
    };
}
