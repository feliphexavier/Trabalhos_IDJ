#ifndef VEC2_H
#define VEC2_H
class Vec2{
    public:
    float x, y;
    Vec2();
    Vec2(float x, float y);
    ~Vec2();
    Vec2 Sum(Vec2 v);
    Vec2 Sub(Vec2 v);
    Vec2 Multiply(float scalar);
    float Magnitude();
    Vec2 Versor();                  
    float Distance(Vec2 v);
    float Angle();                   
    static float LineAngle(Vec2 a, Vec2 b);  
    Vec2 Rotate(float angle);  
};
#endif