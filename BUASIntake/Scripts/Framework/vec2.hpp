//---------------------------------------------------//
// vec2.hpp                                          //
//                                                   //
// Simple utility header for the sf::Vector2f class. //
//---------------------------------------------------//

#pragma once

#include <math.h>
#include <SFML/System/Vector2.hpp>

#define PI      3.14159265359
#define RAD2DEG 57.2957795056
#define DEG2RAD 0.01745329252

typedef sf::Vector2f Vec2;


//Vector2f equals check
struct Vector2fEquals {
    bool operator()(const Vec2& vecA, const Vec2& vecB) const {
        return std::tie(vecA.x, vecA.y) < std::tie(vecB.x, vecB.y);
    }
};

// Returns a random point inside an arbitrary circle
static Vec2 RandomPointInCircle(float xCenter, float yCenter, float radius) {
    float angle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f * PI;
    float randomRadius = std::sqrt(static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * radius;

    float x = randomRadius * std::cos(angle) + xCenter;
    float y = randomRadius * std::sin(angle) + yCenter;

    return Vec2(x, y);
}

// Returns a random point on the edge of an arbitrary circle
static Vec2 RandomPointOnCircleEdge(float xCenter, float yCenter, float radius) {
    float angle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f * PI;

    float x = radius * std::cos(angle) + xCenter;
    float y = radius * std::sin(angle) + yCenter;

    return Vec2(x, y);
}

//Clamp helper function
static inline Vec2 ClampVec2(const sf::Vector2f& vector, const sf::Vector2f& min, const sf::Vector2f& max) {
    float clampedX = std::max(min.x, std::min(vector.x, max.x));
    float clampedY = std::max(min.y, std::min(vector.y, max.y));

    return sf::Vector2f(clampedX, clampedY);
}

/**
 * @brief dot
 * @param a vector
 * @param b vector
 * @return a . b
 */
static inline float dot(const Vec2& a, const Vec2& b)
{
    return a.x * b.x + a.y * b.y;
}

/**
 * @brief magnitudeSq
 * @param v vector
 * @return |v|^2
 */
static inline float magnitudeSq(const Vec2& v)
{
    return v.x * v.x + v.y * v.y;
}

/**
 * @brief magnitude
 * @param v vector
 * @return |v|
 */
static inline float magnitude(const Vec2& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}


/**
 * @brief normalize
 * @param v vector
 * v' = v / |v|
 */
static inline void normalize(Vec2& v)
{
    float len = sqrt(v.x * v.x + v.y * v.y);
    if (len != 0) {
        v.x = v.x / len;
        v.y = v.y / len;
    }
}

/**
 * @brief normalized (faster)
 * @param res vector
 * @param v vector
 * res = v / |v|
 */
static inline void normalized(Vec2& res, const Vec2& v)
{
    float len = sqrt(v.x * v.x + v.y * v.y);
    if (len != 0) {
        res.x = v.x / len;
        res.y = v.y / len;
    }
}

/**
 * @brief normalized
 * @param v vector
 * @return res = v / |v|
 */
static inline Vec2 normalized(const Vec2& v)
{
    Vec2 res;
    normalized(res, v);
    return res;
}

/**
 * @brief truncate (faster)
 * @param res vector
 * @param v vector
 * @param max magnitude
 * res = max * v / |v|
 */
static inline void truncate(Vec2& res, const Vec2& v, float max)
{
    float len = sqrt(v.x * v.x + v.y * v.y);
    if (len > max)
    {
        res = normalized(v);
        res *= max;
    }
    else {
        res = v;
    }
}

/**
 * @brief truncate
 * @param v vector
 * @param max magnitude
 * @return res = max * v / |v|
 */
static inline Vec2 truncate(const Vec2& v, float max)
{
    Vec2 res;
    truncate(res, v, max);
    return res;
}

/**
 * @brief lerp (faster)
 * @param res vector
 * @param a vector
 * @param b vector
 * @param t alpha value
 * res = (1-t)*a + t*b
 */
static inline void lerp(Vec2& res, const Vec2& a, const Vec2& b, float t)
{
    res.x = (1 - t) * a.x + t * b.x;
    res.y = (1 - t) * a.y + t * b.y;
}

/**
 * @brief lerp
 * @param a vector
 * @param b vector
 * @param t alpha value
 * @return res = (1-t)*a + t*b
 */
static inline Vec2 lerp(const Vec2& a, const Vec2& b, float t)
{
    Vec2 res;
    lerp(res, a, b, t);
    return res;
}

/**
 * @brief rotate
 * @param res vector
 * @param v vector
 * @param angle
 * R   = |cos -sin|
 *       |sin  cos|
 * res =  v * R
 */
static inline void rotate(Vec2& res, const Vec2& v, float angle)
{
    const float rad = DEG2RAD * angle;
    const float sin0 = sin(rad);
    const float cos0 = cos(rad);
    res.x = v.x * cos0 + v.y * -sin0;
    res.y = v.x * sin0 + v.y * cos0;
}

/**
 * @brief rotate
 * @param v vector
 * @param angle
 * @return res = v * R
 */
static inline Vec2 rotate(Vec2& v, float angle)
{
    Vec2 res;
    rotate(res, v, angle);
    return res;
}