//
// Created by rodrigo on 19/08/24.
//

#ifndef VEC2_H
#define VEC2_H


class Vec2 {
public:
    float x{0};
    float y{0};

    Vec2();
    Vec2(float xin, float yin);

    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator/(const float val) const;
    Vec2 operator*(const float val) const;

    void operator+=(const Vec2& rhs);
    void operator-=(const Vec2& rhs);
    void operator*=(const float val);
    void operator/=(const float val);

    float dist(const Vec2& rhs) const;
    Vec2 normalize();
};



#endif //VEC2_H
