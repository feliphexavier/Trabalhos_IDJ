#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;
    Rect();
    Rect(float x, float y, float w, float h);
    ~Rect();
    Rect SumWithVec(Vec2 v);
    Vec2 GetCenter();
    float DistanceCenter(Rect other);
    bool IsInside(Vec2 point);
};

#endif