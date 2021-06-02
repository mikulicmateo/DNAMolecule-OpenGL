#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <numeric>
#include <vector>
#include <array>

#include "pathconfig.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include <fstream>
#include <sstream>

#include "shader.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexbufferlayout.h"
#include "vertexarray.h"
#include "renderer.h"
#include "pipe.h"
#include "line.h"
#include "matrices.h"
#include "plane.h"

//maknuti iz .gitignore sve foldere prije predaje!!!!!!!!!!!
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

std::vector<glm::vec3> build_circle(float radius, int steps)
{
    std::vector<glm::vec3> points;
    if(steps < 2) return points;

    const float PI2 = acos(-1) * 2.0f;
    float x, y, a;
    for(int i = 0; i <= steps; ++i)
    {
        a = PI2 / steps * i;
        x = radius * cosf(a);
        y = radius * sinf(a);
        points.emplace_back(x, y, 0);
    }
    return points;
}

std::vector<float> linspace(float start_in, float end_in, size_t num_in)
{
    const float dx = (end_in - start_in) / (num_in - 1);
    std::vector<float> linspaced(num_in);
    int iter = 0;
    std::generate(linspaced.begin(), linspaced.end(),
                  [&] { return start_in + (iter++) * dx; });
    return linspaced;
}

float binomial(long n, long i)
{
    long brojnik = 1;
    for (long f = n; f >= n - i + 1; f--)
    {
        brojnik *= f;
    }
    long long nazivnik = 1;
    for (long f = i; f >= 1; f--)
    {
        nazivnik *= f;
    }
    return float(brojnik) / float(nazivnik);
}

float bernstein(long i, long n, float t)
{
    double r = binomial(n, i);
    r*= std::pow(1-t, n-i);
    r*=std::pow(t, i);
    return r;
}

glm::vec3 calc_pt(const std::vector<glm::vec3>& ctrl_pts, const double& t)
{
    glm::vec3 pt(0);
    for(size_t i=0; i<ctrl_pts.size(); ++i)
    {
        const float bm = bernstein(i, ctrl_pts.size()-1, t);
        pt+= bm*ctrl_pts[i];
    }
    return pt;
}

std::vector<glm::vec3> generate_bez_line(const std::vector<glm::vec3>& ctrl_pts,
                                         const unsigned int& pts_num)
{
    std::vector<glm::vec3> curve_points;
    const auto ts = linspace(0, 1, pts_num);
    for(const auto& t : ts)
    {
        const glm::vec3 pt = calc_pt(ctrl_pts, t);
        curve_points.emplace_back(pt);
    }
    return curve_points;
}
std::vector<float> generate_bez_line(const std::vector<glm::vec3>& ctrl_pts,
                                     const unsigned int& pts_num,
                                     const glm::vec3& color)
{
    const std::vector<glm::vec3> curve_points = generate_bez_line(ctrl_pts, pts_num);

    std::vector<float>data;
    for(size_t i=0; i<curve_points.size(); ++i)
    {
        data.emplace_back(curve_points[i].x);
        data.emplace_back(curve_points[i].y);
        data.emplace_back(curve_points[i].z);

        data.emplace_back(color.x);
        data.emplace_back(color.y);
        data.emplace_back(color.z);
    }
    return data;
}

std::vector<glm::vec3> generate_helix(float length, float step){
    std::vector<glm::vec3> generated;
    if(length > 0)
    {
        for (float i = -length; i <= length; i += step)
        {
            generated.emplace_back(glm::vec3(std::cos(5 * i) / 7, i,std::sin(5 * i) / 7));
        }
    }
    else
    {
        for(float i=length;i <= -1 * length;i+=step)
        {
            generated.emplace_back(glm::vec3(-std::cos(5*i) / 7, i , -std::sin(5*i) / 7));
        }
    }
    return generated;
}

void drawNucleotides(std::vector<glm::vec3> helix1, std::vector<glm::vec3> helix2, VertexBufferLayout &layout, Shader &pipe_shader){
    const std::vector<glm::vec3> base_circle = build_circle(0.01f, 32);

    for(int i=2;i<helix1.size() && i<helix2.size();i+=2){
        std::vector<glm::vec3> path = {helix1[i],helix2[i]};
        Pipe pipe_nucleotide;
        pipe_nucleotide.set(path,base_circle);
        VertexBuffer vb(pipe_nucleotide.getInterleavedVertices());
        VertexArray va;
        va.addBuffer(vb,layout);
        IndexBuffer ib(pipe_nucleotide.getIndices());

        Renderer::drawTriangleStrip(va, ib,pipe_shader);
    }

}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "mikulic", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(2);
    unsigned int err = glewInit();
    if(err != GLEW_OK) {std::cout << "error\n"; return -1;}

    std::cout << glGetString(GL_VERSION) << std::endl;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "shaders folder: " << shaders_folder << std::endl;
    const std::string t_vs = shaders_folder + "vert.glsl";
    const std::string t_fs = shaders_folder + "frag.glsl";

    ///////////////////////////////PROFESOROV KOD//////////////////////////////////////////////////////
//    std::vector<glm::vec3> b00_pts{glm::vec3(-1.0f,-1.0f,0),glm::vec3(0, -1.0, 1), glm::vec3(0.1, -0.1, 0),
//                                   glm::vec3(0.0, 0.1, 0), glm::vec3(-0.9, 0.9, 1), glm::vec3 (0,0.7,0)};
    std::vector<glm::vec3> b00_pts = generate_helix(1, 0.1);
    std::vector<glm::vec3> b01_pts = generate_helix(-1,0.1);
    unsigned int pt_num{60};

    const std::string pipe_vs = shaders_folder + "pipe_vert.glsl";
    const std::string pipe_fs = shaders_folder + "pipe_frag.glsl";
    Shader pipe_shader({{GL_VERTEX_SHADER, pipe_vs}, {GL_FRAGMENT_SHADER, pipe_fs}});
    pipe_shader.bind();

    Pipe pipe;
    Pipe pipe1;

    const std::vector<glm::vec3> bez_path_data = generate_bez_line(b00_pts, pt_num);
    const std::vector<glm::vec3> bez_path_data1 = generate_bez_line(b01_pts, pt_num);

    std::cout << bez_path_data.size() << std::endl;
    // sectional contour of pipe
    const std::vector<glm::vec3> circle = build_circle(0.02f, 32); // radius, segments
    pipe.set(bez_path_data, circle);
    pipe1.set(bez_path_data1,circle);

    VertexBuffer pipe_vb(pipe.getInterleavedVertices());
    VertexBuffer pipe_vb1(pipe1.getInterleavedVertices());

    VertexBufferLayout pipe_layout;
    pipe_layout.addFloat(3); // pos
    pipe_layout.addFloat(3); // normals

    VertexArray pipe_va;
    VertexArray pipe_va1;

    pipe_va.addBuffer(pipe_vb, pipe_layout);
    pipe_va1.addBuffer(pipe_vb1,pipe_layout);

    IndexBuffer pipe_ib(pipe.getIndices());
    IndexBuffer pipe_ib1(pipe1.getIndices());


    const glm::vec3 sphereColor(0.894 , 0.894 , 0.631);
    const glm::vec3 lightColor(1., 1., 1.);
    //////////////////////////////////////////////////////////////////////////////////////////////
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
            /* Render here */
            glClearColor(0.f, 0.f, 0.f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Renderer::clear();

            const glm::vec3 lightPos(2, 2, 3);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);
            float camX   = sin(0.5 *glfwGetTime()) * 3;
            float camZ   = cos(0.5 *glfwGetTime()) * 3;
            glm::vec3 view_position = glm::vec3(camX, 1.0f, camZ);
            view = glm::lookAt(view_position,
                               glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));


            projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT,
                                          0.1f, 100.0f);

            pipe_shader.bind();
            pipe_shader.setMat4("model", glm::mat4(1));
            pipe_shader.setMat4("view", view);
            pipe_shader.setMat4("proj", projection);

            pipe_shader.setVec3("objectColor", sphereColor);
            pipe_shader.setVec3("lightColor", lightColor);
            pipe_shader.setVec3("lightPos", lightPos);
            pipe_shader.setVec3("viewPos", view_position);
            Renderer::drawTriangleStrip(pipe_va, pipe_ib, pipe_shader);
            Renderer::drawTriangleStrip(pipe_va1,pipe_ib1,pipe_shader);
            drawNucleotides(bez_path_data,bez_path_data1,pipe_layout,pipe_shader);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
