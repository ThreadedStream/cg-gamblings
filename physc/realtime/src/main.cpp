#include <shared/defs.hpp>
#include <glad.h>

#include <GLFW/glfw3.h>

#include <include/renderer.h>
#include <include/vertices.h>

class GlobalFrameManager;

static GlobalFrameManager *instance_;

class GlobalFrameManager {
public:
    static GlobalFrameManager *getInstance() {
        if (!instance_) {
            instance_ = new GlobalFrameManager();
        }
        return instance_;
    }


    [[nodiscard]] inline const float dt() const noexcept { return dt_; }

private:
    GlobalFrameManager() : dt_{1 / 60.0f} {};

    float dt_;
};


void onFramebufferResized(GLFWwindow* window, int32_t width, int32_t height) {
    glViewport(0, 0, width, height);
}

void onKeyPressed(GLFWwindow *window, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
}


int main(int argc, const char *argv[]) {
    // NOTE(threadedstream): initializing glfwInit in main thread, so to avoid
    // unnecessary terminations
    GLFWwindow* window;


    if (!glfwInit()){
        return -1;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "I don't know math", nullptr, nullptr);


    if (!window) {
        spdlog::error("failed to initialize a window");
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, onFramebufferResized);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("failed to load gl procs");
        glfwTerminate();
        return -1;
    }

    Renderer renderer;

    const auto drawingFunc = renderer.drawTexturedCube();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2, 0.4, 0.2, 0.5);
        glClear(GL_COLOR_BUFFER_BIT);

        drawingFunc();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    renderer.destroy();
    // NOTE(threadedstream): should be called in main thread
    glfwTerminate();
    return 0;
}


