#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <streambuf>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "shader.hpp"

//________________________________________________CALLBACK_FUNCTIONS_________________________________________________//

static void errorCallback(int error, const char *description)
{
    fputs(description, stderr);
}
static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // close window when ESC has been pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {}
static void mousePositionCallback(GLFWwindow *window, double xpos, double ypos) {}

//_________________________________________________INITIALIZATION____________________________________________________//

GLFWwindow *initialize(int width, int height, std::string title)
{
    GLFWwindow *window;
    glfwSetErrorCallback(errorCallback);

    // initialize glfw window
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // we want to use the opengl 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // actually create the window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    // make sure the window creation was successful
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // initialize glad for loading all OpenGL functions
    if (!gladLoadGL())
    {
        printf("Something went wrong!\n");
        exit(-1);
    }

    // print some information about the supported OpenGL version
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    fprintf(stdout, "Renderer: %s\n", renderer);
    fprintf(stdout, "OpenGL version supported %s\n", version);

    // register user callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mousePositionCallback);

    // set the clear color of the window
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

    return window;
}

GLuint createBuffers()
{
    // specify the layout of the vertex data, being the vertex position followed by the vertex color
    struct Vertex
    {
        glm::vec3 pos;
        glm::vec3 color;
    };

    // we specify a triangle with red, green, blue at the tips of the triangle
    Vertex vertexData[] = {
        Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.f, 0.f, 0.f)},
        Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.f, 1.f, 0.f)},
        Vertex{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.f, 0.f, 1.f)}};

    // create the vertex array object that holds all vertex buffers
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create a vertex buffer that contains all vertex positions and copy the vertex positions into that buffer
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // we need to tell the buffer in which format the data is and we need to explicitly enable it
    // first we specify the layout of the vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(struct Vertex, pos)));
    glEnableVertexAttribArray(0);
    // then we specify the layout of the vertex color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(struct Vertex, color)));
    glEnableVertexAttribArray(1);

    return vao;
}

//______________________________________________________RENDER_______________________________________________________//

void render(GLuint shaderProgram, GLuint vao)
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

//______________________________________________________CLEANUP______________________________________________________//

void cleanup(GLFWwindow *window, GLuint &shaderProgram, GLuint &vao)
{
    // do some custom cleanup here
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &vao);

    // lastly destroy the window and terminate glfw
    glfwDestroyWindow(window);
    glfwTerminate();
}

//_______________________________________________________MAIN________________________________________________________//

int main(void)
{
    // create a window with the specified width, height and title and initialize OpenGL
    GLFWwindow *window = initialize(640, 480, "OpenGL Starter Project");
    auto shader = Shader("shaders/vs.vert", "shaders/fs.frag");
    GLuint shaderProgram = shader.GetId();
    GLuint vao = createBuffers();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // IF using Docking Branch
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // loop until the user presses ESC or the window is closed programatically
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        // render to back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render(shaderProgram, vao);
        glfwSwapBuffers(window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // clean up all created objects
    cleanup(window, shaderProgram, vao);

    // program exits properly
    exit(EXIT_SUCCESS);
}