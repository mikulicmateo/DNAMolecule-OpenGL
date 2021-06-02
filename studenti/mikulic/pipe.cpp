///////////////////////////////////////////////////////////////////////////////
// Pipe.cpp
// ========
// base contour following a path
//
// Dependencies: Vector3, Plane, Line, Matrix4
//
//  AUTHOR: Song ho Ahn (song.ahn@gmail.com)
// CREATED: 2016-04-16
// UPDATED: 2020-04-22
///////////////////////////////////////////////////////////////////////////////

#include "pipe.h"
#include "matrices.h"
#include "line.h"
#include "plane.h"
#include <glm/glm.hpp>



///////////////////////////////////////////////////////////////////////////////
// ctors
///////////////////////////////////////////////////////////////////////////////
Pipe::Pipe()
{
}

Pipe::Pipe(const std::vector<glm::vec3>& pathPoints, const std::vector<glm::vec3>& contourPoints)
{
    set(pathPoints, contourPoints);
}



///////////////////////////////////////////////////////////////////////////////
// setters
///////////////////////////////////////////////////////////////////////////////
void Pipe::set(const std::vector<glm::vec3>& pathPoints, const std::vector<glm::vec3>& contourPoints)
{
    this->path = pathPoints;
    this->contour = contourPoints;
    generateContours();

    interleavedVertices.clear();
    const int count = getContourCount();
    for(int i = 0; i < count -1 ; ++i)
    {
        const std::vector<glm::vec3> c1 = getContour(i);
        const std::vector<glm::vec3> n1 = getNormal(i);
        const std::vector<glm::vec3> c2 = getContour(i+1);
        const std::vector<glm::vec3> n2 = getNormal(i+1);
        for(int j = 0; j < (int)c1.size(); ++j)
        {
            interleavedVertices.emplace_back(c2[j]);
            interleavedVertices.emplace_back(n2[j]);
            interleavedVertices.emplace_back(c1[j]);
            interleavedVertices.emplace_back(n1[j]);
        }
    }
    indices.clear();
    for(unsigned int i=0; i < interleavedVertices.size()/2; i++)
    {
        indices.emplace_back(i);
//        indices.emplace_back(i+1);
//        indices.emplace_back(i+2);
    }
}

void Pipe::setPath(const std::vector<glm::vec3>& pathPoints)
{
    this->path = pathPoints;
    generateContours();
}

void Pipe::setContour(const std::vector<glm::vec3>& contourPoints)
{
    this->contour = contourPoints;
    generateContours();
}



///////////////////////////////////////////////////////////////////////////////
// add a new path point at the end of the path list
///////////////////////////////////////////////////////////////////////////////
void Pipe::addPathPoint(const glm::vec3& point)
{
    // add it to path first
    path.push_back(point);

    int count = path.size();
    if(count == 1)
    {
        transformFirstContour();
        normals.push_back(computeContourNormal(0));
    }
    else if(count == 2)
    {
        contours.push_back(projectContour(0, 1));
        normals.push_back(computeContourNormal(1));
    }
    else
    {
        // add dummy to match same # of contours/normals and path
        std::vector<glm::vec3> dummy;
        contours.push_back(dummy);
        normals.push_back(dummy);

        // re-project the previous contour
        contours[count-2] = projectContour(count-3, count-2);
        normals[count-2] = computeContourNormal(count-2);

        // compute for new contour
        contours[count-1] = projectContour(count-2, count-1);
        normals[count-1] = computeContourNormal(count-1);
    }
}



///////////////////////////////////////////////////////////////////////////////
// build countour vertex and normal list on each path point
///////////////////////////////////////////////////////////////////////////////
void Pipe::generateContours()
{
    // reset
    contours.clear();
    normals.clear();

    // path must have at least a point
    if(path.size() < 1)
        return;

    // rotate and translate the contour to the first path point
    transformFirstContour();
    contours.push_back(this->contour);
    normals.push_back(computeContourNormal(0));

    // project contour to the plane at the next path point
    int count = (int)path.size();
    for(int i = 1; i < count; ++i)
    {
        contours.push_back(projectContour(i-1, i));
        normals.push_back(computeContourNormal(i));
    }
}



///////////////////////////////////////////////////////////////////////////////
// project a contour to a plane at the path point
///////////////////////////////////////////////////////////////////////////////
std::vector<glm::vec3> Pipe::projectContour(int fromIndex, int toIndex)
{
    glm::vec3 dir1, dir2, normal;
    Line line;

    dir1 = path[toIndex] - path[fromIndex];
    if(toIndex == (int)path.size()-1)
        dir2 = dir1;
    else
        dir2 = path[toIndex + 1] - path[toIndex];

    normal = dir1 + dir2;               // normal vector of plane at toIndex
    Plane plane(normal, path[toIndex]);

    // project each vertex of contour to the plane
    std::vector<glm::vec3>& fromContour = contours[fromIndex];
    std::vector<glm::vec3> toContour;
    int count = (int)fromContour.size();
    for(int i = 0; i < count; ++i)
    {
        line.set(dir1, fromContour[i]);
        toContour.push_back(plane.intersect(line));
    }

    return toContour;
}



///////////////////////////////////////////////////////////////////////////////
// transform the contour at the first path point
///////////////////////////////////////////////////////////////////////////////
void Pipe::transformFirstContour()
{
    int pathCount = (int)path.size();
    int vertexCount = (int)contour.size();
    Matrix4 matrix;

    if(pathCount > 0)
    {
        // transform matrix
        if(pathCount > 1)
            matrix.lookAt(path[1] - path[0]);

        matrix.translate(path[0]);

        // multiply matrix to the contour
        // NOTE: the contour vertices are transformed here
        //       MUST resubmit contour data if the path is resset to 0
        for(int i = 0; i < vertexCount; ++i)
        {
            contour[i] = matrix * contour[i];
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
// return normal vectors at the current path point
///////////////////////////////////////////////////////////////////////////////
std::vector<glm::vec3> Pipe::computeContourNormal(int pathIndex)
{
    // get current contour and center point
    std::vector<glm::vec3>& contour = contours[pathIndex];
    glm::vec3 center = path[pathIndex];

    std::vector<glm::vec3> contourNormal;
    glm::vec3 normal;
    for(int i = 0; i < (int)contour.size(); ++i)
    {
        normal = glm::normalize(contour[i] - center);
        contourNormal.push_back(normal);
    }

    return contourNormal;
}
