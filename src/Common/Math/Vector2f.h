#pragma once

class Vector2f
{
public:
    Vector2f() : x(0.0f), y(0.0f) {}
    Vector2f(float x, float y) : x(x), y(y) {}

public:
    float x;
    float y;
};