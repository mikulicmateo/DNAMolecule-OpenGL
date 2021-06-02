///////////////////////////////////////////////////////////////////////////////
// Pipe.h
// ======
// base contour following a path
// The contour is a 2D shape on XY plane.
//
// Dependencies: Vector3, Plane, Line, Matrix4
//
//  AUTHOR: Song ho Ahn (song.ahn@gmail.com)
// CREATED: 2016-04-16
// UPDATED: 2016-04-29
///////////////////////////////////////////////////////////////////////////////

#ifndef PIPE_H_DEF
#define PIPE_H_DEF

#include <vector>
#include <glm/glm.hpp>

class Pipe
{
public:
    // ctor/dtor
    Pipe();
    Pipe(const std::vector<glm::vec3>& pathPoints, const std::vector<glm::vec3>& contourPoints);
    ~Pipe() {}

    // setters/getters
    void set(const std::vector<glm::vec3>& pathPoints, const std::vector<glm::vec3>& contourPoints);
    void setPath(const std::vector<glm::vec3>& pathPoints);
    void setContour(const std::vector<glm::vec3>& contourPoints);
    void addPathPoint(const glm::vec3& point);

    int getPathCount() const                                        { return (int)path.size(); }
    const std::vector<glm::vec3>& getPathPoints() const               { return path; }
    const glm::vec3& getPathPoint(int index) const                    { return path.at(index); }
    int getContourCount() const                                     { return (int)contours.size(); }
    const std::vector< std::vector<glm::vec3> >& getContours() const  { return contours; }
    const std::vector<glm::vec3>& getContour(int index) const         { return contours.at(index); }
    const std::vector< std::vector<glm::vec3> >& getNormals() const   { return normals; }
    const std::vector<glm::vec3>& getNormal(int index) const          { return normals.at(index); }

    const std::vector<glm::vec3>& getInterleavedVertices() const {return interleavedVertices;}
    const std::vector<unsigned int> &getIndices() const  { return indices; }


private:
    // member functions
    void generateContours();
    void transformFirstContour();
    std::vector<glm::vec3> projectContour(int fromIndex, int toIndex);
    std::vector<glm::vec3> computeContourNormal(int pathIndex);

    std::vector<glm::vec3> path;
    std::vector<glm::vec3> contour;
    std::vector< std::vector<glm::vec3> > contours;
    std::vector< std::vector<glm::vec3> > normals;
    std::vector<glm::vec3> interleavedVertices;
    std::vector<unsigned int> indices;
};
#endif
