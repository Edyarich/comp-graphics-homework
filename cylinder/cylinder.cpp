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

const int K_ITERATIONS = 1000;
const float PI = 3.1416;

static const GLfloat G_VERTEX_BUFFER_DATA[] = {
        1.0, 0.0, 0.0,
        1.0, 0.0, 1.0,
        0.809, 0.588, 1.0,
        1.0, 0.0, 0.0,
        0.809, 0.588, 0.0,
        0.809, 0.588, 1.0,
        0.809, 0.588, 0.0,
        0.809, 0.588, 1.0,
        0.309, 0.951, 1.0,
        0.809, 0.588, 0.0,
        0.309, 0.951, 0.0,
        0.309, 0.951, 1.0,
        0.309, 0.951, 0.0,
        0.309, 0.951, 1.0,
        -0.309, 0.951, 1.0,
        0.309, 0.951, 0.0,
        -0.309, 0.951, 0.0,
        -0.309, 0.951, 1.0,
        -0.309, 0.951, 0.0,
        -0.309, 0.951, 1.0,
        -0.809, 0.588, 1.0,
        -0.309, 0.951, 0.0,
        -0.809, 0.588, 0.0,
        -0.809, 0.588, 1.0,
        -0.809, 0.588, 0.0,
        -0.809, 0.588, 1.0,
        -1.0, 0.0, 1.0,
        -0.809, 0.588, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 1.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 1.0,
        -0.809, -0.588, 1.0,
        -1.0, 0.0, 0.0,
        -0.809, -0.588, 0.0,
        -0.809, -0.588, 1.0,
        -0.809, -0.588, 0.0,
        -0.809, -0.588, 1.0,
        -0.309, -0.951, 1.0,
        -0.809, -0.588, 0.0,
        -0.309, -0.951, 0.0,
        -0.309, -0.951, 1.0,
        -0.309, -0.951, 0.0,
        -0.309, -0.951, 1.0,
        0.309, -0.951, 1.0,
        -0.309, -0.951, 0.0,
        0.309, -0.951, 0.0,
        0.309, -0.951, 1.0,
        0.309, -0.951, 0.0,
        0.309, -0.951, 1.0,
        0.809, -0.588, 1.0,
        0.309, -0.951, 0.0,
        0.809, -0.588, 0.0,
        0.809, -0.588, 1.0,
        0.809, -0.588, 0.0,
        0.809, -0.588, 1.0,
        1.0, 0.0, 1.0,
        0.809, -0.588, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 1.0,

        0.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        0.809, 0.588, 0.0,
        0.0, 0.0, 0.0,
        0.809, 0.588, 0.0,
        0.309, 0.951, 0.0,
        0.0, 0.0, 0.0,
        0.309, 0.951, 0.0,
        -0.309, 0.951, 0.0,
        0.0, 0.0, 0.0,
        -0.309, 0.951, 0.0,
        -0.809, 0.588, 0.0,
        0.0, 0.0, 0.0,
        -0.809, 0.588, 0.0,
        -1.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -0.809, -0.588, 0.0,
        0.0, 0.0, 0.0,
        -0.809, -0.588, 0.0,
        -0.309, -0.951, 0.0,
        0.0, 0.0, 0.0,
        -0.309, -0.951, 0.0,
        0.309, -0.951, 0.0,
        0.0, 0.0, 0.0,
        0.309, -0.951, 0.0,
        0.809, -0.588, 0.0,
        0.0, 0.0, 0.0,
        0.809, -0.588, 0.0,
        1.0, 0.0, 0.0,

        0.0, 0.0, 1.0,
        1.0, 0.0, 1.0,
        0.809, 0.588, 1.0,
        0.0, 0.0, 1.0,
        0.809, 0.588, 1.0,
        0.309, 0.951, 1.0,
        0.0, 0.0, 1.0,
        0.309, 0.951, 1.0,
        -0.309, 0.951, 1.0,
        0.0, 0.0, 1.0,
        -0.309, 0.951, 1.0,
        -0.809, 0.588, 1.0,
        0.0, 0.0, 1.0,
        -0.809, 0.588, 1.0,
        -1.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        -1.0, 0.0, 1.0,
        -0.809, -0.588, 1.0,
        0.0, 0.0, 1.0,
        -0.809, -0.588, 1.0,
        -0.309, -0.951, 1.0,
        0.0, 0.0, 1.0,
        -0.309, -0.951, 1.0,
        0.309, -0.951, 1.0,
        0.0, 0.0, 1.0,
        0.309, -0.951, 1.0,
        0.809, -0.588, 1.0,
        0.0, 0.0, 1.0,
        0.809, -0.588, 1.0,
        1.0, 0.0, 1.0,
};

static const GLfloat G_COLOR_BUFFER_DATA[] = {
        0.613, 0.357, 0.584,
        0.832, 0.52, 0.816,
        0.523, 0.757, 0.586,
        0.602, 0.438, 0.614,
        0.307, 0.261, 0.169,
        0.957, 0.346, 0.995,
        0.366, 0.661, 0.645,
        0.596, 0.745, 0.397,
        0.121, 0.827, 0.429,
        0.926, 0.638, 0.268,
        0.944, 0.905, 0.868,
        0.626, 0.538, 0.022,
        0.249, 0.621, 0.077,
        0.398, 0.709, 0.74,
        0.965, 0.478, 0.699,
        0.559, 0.084, 0.658,
        0.961, 0.652, 0.206,
        0.063, 0.243, 0.419,
        0.355, 0.972, 0.14,
        0.414, 0.516, 0.267,
        0.871, 0.66, 0.086,
        0.967, 0.387, 0.879,
        0.015, 0.694, 0.201,
        0.862, 0.068, 0.749,
        0.704, 0.76, 0.666,
        0.011, 0.071, 0.365,
        0.34, 0.218, 0.295,
        0.573, 0.693, 0.291,
        0.118, 0.981, 0.197,
        0.198, 0.655, 0.35,
        0.408, 0.651, 0.393,
        0.073, 0.883, 0.028,
        0.644, 0.728, 0.657,
        0.165, 0.086, 0.259,
        0.039, 0.127, 0.986,
        0.09, 0.686, 0.554,
        0.716, 0.571, 0.642,
        0.278, 0.32, 0.622,
        0.412, 0.727, 0.099,
        0.354, 0.105, 0.979,
        0.399, 0.489, 0.554,
        0.059, 0.262, 0.401,
        0.374, 0.225, 0.03,
        0.557, 0.135, 0.071,
        0.028, 0.152, 0.149,
        0.717, 0.819, 0.747,
        0.471, 0.559, 0.114,
        0.51, 0.08, 0.22,
        0.442, 0.76, 0.31,
        0.422, 0.899, 0.719,
        0.171, 0.581, 0.754,
        0.296, 0.209, 0.645,
        0.208, 0.693, 0.624,
        0.929, 0.56, 0.892,
        0.663, 0.232, 0.109,
        0.298, 0.298, 0.53,
        0.428, 0.083, 0.864,
        0.763, 0.021, 0.685,
        0.774, 0.63, 0.312,
        0.21, 0.961, 0.996,
        0.095, 0.12, 0.217,
        0.903, 0.221, 0.675,
        0.787, 0.86, 0.464,
        0.061, 0.259, 0.012,
        0.901, 0.474, 0.313,
        0.092, 0.234, 0.656,
        0.908, 0.852, 0.679,
        0.816, 0.23, 0.192,
        0.336, 0.67, 0.255,
        0.13, 0.341, 0.665,
        0.268, 0.644, 0.046,
        0.631, 0.286, 0.047,
        0.065, 0.465, 0.432,
        0.573, 0.462, 1.0,
        0.603, 0.039, 0.959,
        0.413, 0.301, 0.283,
        0.785, 0.987, 0.14,
        0.916, 0.892, 0.52,
        0.925, 0.41, 0.43,
        0.344, 0.245, 0.254,
        0.782, 0.734, 0.144,
        0.6, 0.514, 0.913,
        0.927, 0.18, 0.011,
        0.182, 0.751, 0.167,
        0.226, 0.556, 0.558,
        0.054, 0.573, 0.974,
        0.262, 0.776, 0.497,
        0.735, 0.334, 0.899,
        0.236, 0.899, 0.082,
        0.141, 0.892, 0.626,
        0.891, 0.045, 0.657,
        0.782, 0.904, 0.284,
        0.991, 0.362, 0.374,
        0.916, 0.096, 0.599,
        0.467, 0.224, 0.175,
        0.864, 0.344, 0.461,
        0.285, 0.125, 0.941,
        0.365, 0.758, 0.225,
        0.851, 0.644, 0.482,
        0.711, 0.882, 0.45,
        0.242, 0.111, 0.694,
        0.197, 0.217, 0.133,
        0.749, 0.591, 0.362,
        0.109, 0.382, 0.536,
        0.281, 0.034, 0.047,
        0.428, 0.471, 0.896,
        0.064, 0.538, 0.03,
        0.98, 0.508, 0.178,
        0.218, 0.002, 0.887,
        0.635, 0.515, 0.24,
        0.094, 0.909, 0.963,
        0.041, 0.995, 0.6,
        0.178, 0.078, 0.431,
        0.745, 0.806, 0.482,
        0.422, 0.863, 0.539,
        0.572, 0.314, 0.577,
        0.244, 0.563, 0.725,
        0.322, 0.999, 0.966,
        0.171, 0.466, 0.763,
        0.12, 0.899, 0.507,
};

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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow( 1024, 768, "Cylinder", NULL, NULL);
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

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader"
                                                                       ".fragmentshader");

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(G_VERTEX_BUFFER_DATA), G_VERTEX_BUFFER_DATA, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(G_COLOR_BUFFER_DATA), G_COLOR_BUFFER_DATA, GL_STATIC_DRAW);

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 Model = glm::mat4(1.0f);

    glm::vec4 initial_eye = glm::vec4(2.0f, -2.0f, 3.0f, 1.0f);
    glm::vec3 rotation_axis = glm::vec3(1.0f, 0.5f, 1.0f);

    while (render_cycle_exit_cond()) {
        for (int i = 0; i < K_ITERATIONS && render_cycle_exit_cond(); ++i) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(programID);

            float angle = static_cast<float>(i) * 2 * PI / K_ITERATIONS;
            glm::mat4 rotation_mat = glm::rotate(angle, rotation_axis);
            glm::vec3 rotated_eye = glm::vec3(rotation_mat * initial_eye);

            glm::mat4 View = glm::lookAt(
                    rotated_eye,
                    glm::vec3(0, 0.0, 0),
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
                    1,                                // must match the layout in the shader.
                    3,                                // size
                    GL_FLOAT,                         // type
                    GL_FALSE,                         // normalized?
                    0,                                // stride
                    (void*) 0                          // array buffer offset
            );

            glDrawArrays(GL_TRIANGLES, 0, 120 * 3);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    glfwTerminate();

    return 0;
}
