// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

#include <common/shader.hpp>

const int K_ITERATIONS = 300;
const float PI = 3.1416;

bool render_cycle_exit_cond() {
    return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0;
}

int main() {
    if (!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow( 1024, 768, "Animation", NULL, NULL);
    if (window == NULL) {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glDisable(GL_CULL_FACE);

    GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader",
                                    "SimpleFragmentShader.fragmentshader" );

    static const GLfloat g_vertex_buffer_data[] = {
            -0.4f, -0.5f, 0.0f,
            0.4f, -0.5f, 0.0f,
            -0.8f,  0.75f, 0.0f,

            -0.4f, -0.5f, 0.0f,
            0.4f, -0.5f, 0.0f,
            0.8f,  0.75f, 0.0f,
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    static const GLfloat g_color_buffer_data[] = {
            0.8f, 0.0f, 0.0f, 1.0f,
            0.8f, 0.0f, 0.0f, 1.0f,
            0.8f, 0.0f, 0.0f, 0.5f,

            0.8f, 0.8f, 0.0f, 0.5f,
            0.8f, 0.8f, 0.0f, 0.5f,
            0.8f, 0.8f, 0.0f, 1.0f,
    };

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 Model = glm::mat4(1.0f);

    glm::vec4 initial_eye = glm::vec4(1.0f, 1.0f, 2.0f, 1.0f);
    glm::vec3 rotation_axis = glm::vec3(0.0f, 1.0f, 0.0f);

    while (render_cycle_exit_cond()) {
        for (int i = 0; i < K_ITERATIONS && render_cycle_exit_cond(); ++i) {
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(programID);

            float angle = static_cast<float>(i) * 2 * PI / K_ITERATIONS;
            glm::mat4 rotation_mat = glm::rotate(angle, rotation_axis);
            glm::vec3 rotated_eye = glm::vec3(rotation_mat * initial_eye);

            glm::mat4 View = glm::lookAt(
                    rotated_eye,
                    glm::vec3(0, 0, 0),
                    glm::vec3(0, 1, 0)
            );
            glm::mat4 mvp = Projection * View * Model;

            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    0,                  // must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*) 0            // array buffer offset
            );

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
            glVertexAttribPointer(
                    1,                  // must match the layout in the shader.
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*) 0            // array buffer offset
            );

            glDrawArrays(GL_TRIANGLES, 0, 6);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    glfwTerminate();

    return 0;
}

