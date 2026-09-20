#include "Rect.h"

Rect::Rect() {
    x = 0; y = 0; w = 0; h = 0;
}

Rect::Rect(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect::~Rect() {}

Rect Rect::SumWithVec(Vec2 v) {
    return Rect(x + v.x, y + v.y, w, h);
}

Vec2 Rect::GetCenter() {
    return Vec2(x + w / 2.0f, y + h / 2.0f);
}

float Rect::DistanceCenter(Rect other) {
    Vec2 c1 = GetCenter();
    Vec2 c2 = other.GetCenter();
    return c1.Distance(c2);
}

bool Rect::IsInside(Vec2 point) {
    return (point.x >= x && point.x <= x + w &&
            point.y >= y && point.y <= y + h);
}