#pragma once

struct Vector2
{
    float x;
    float y;

    Vector2() = default;

    Vector2(const Vector2&) = default;
    Vector2& operator=(const Vector2&) = default;

    Vector2(Vector2&&) = default;
    Vector2& operator=(Vector2&&) = default;

    Vector2 operator+(const Vector2& other)
    {
        Vector2 temp;
        temp.x = x + other.x;
        temp.y = y + other.y;

        return temp;
    }

    Vector2 operator-(const Vector2& other)
    {
        Vector2 temp;
        temp.x = x - other.x;
        temp.y = y - other.y;

        return temp;
    }

    Vector2 operator/(const float& value)
    {
        Vector2 temp;
        temp.x = x / value;
        temp.y = y / value;

        return temp;
    }

    Vector2& operator +=(const Vector2 other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vector2& operator -=(const Vector2 other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    constexpr Vector2(float _x, float _y) noexcept 
        : x(_x)
        , y(_y) 
    {
    
    }
    explicit Vector2(_In_reads_(2) const float* pArray)  noexcept 
        : x(pArray[0])
        , y(pArray[1]) 
    {
    
    }
};

typedef Vector2 Pos;
typedef Vector2 Size;