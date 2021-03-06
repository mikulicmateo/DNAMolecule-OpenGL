///////////////////////////////////////////////////////////////////////////////
// Line.h
// ======
// class to construct a line with parametric form
// Line = p + aV (a point and a direction vector on the line)
//
// Dependency: Vector2, Vector3
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2015-12-18
// UPDATED: 2020-07-17
///////////////////////////////////////////////////////////////////////////////

#ifndef LINE_H_DEF
#define LINE_H_DEF

#include <cmath>
#include <glm/glm.hpp>


class Line
{
public:
    // ctor/dtor
    Line() : direction(glm::vec3(0,0,0)), point(glm::vec3(0,0,0)) {}
    Line(const glm::vec3& v, const glm::vec3& p) : direction(v), point(p) {}    // with 3D direction and a point
    Line(const glm::vec2& v, const glm::vec2& p);                               // with 2D direction and a point
    Line(float slope, float intercept);                                     // with 2D slope-intercept form
    ~Line() {};

    // getters/setters
    void set(const glm::vec3& v, const glm::vec3& p);               // from 3D
    void set(const glm::vec2& v, const glm::vec2& p);               // from 2D
    void set(float slope, float intercept);                     // from slope-intercept form
    void setPoint(glm::vec3& p)           { point = p; }
    void setDirection(const glm::vec3& v) { direction = v; }
    const glm::vec3& getPoint() const     { return point; }
    const glm::vec3& getDirection() const { return direction; }
    void printSelf();

    // find intersect point with other line
    glm::vec3 intersect(const Line& line);
    bool isIntersected(const Line& line);

protected:

private:
    glm::vec3 direction;
    glm::vec3 point;
};

#endif

