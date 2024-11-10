#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "IDrawable.h"
#include "ImGuiDialog.hpp"
#include "imgui.h"
#include <concepts>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <memory>
#include <queue>
#include <string>
#include <vector>

class Canvas final
{
  public:
    explicit Canvas(const std::string &title) : Canvas(title, 800, 600) {}
    explicit Canvas(const std::string &title, const int width, const int height)
        : _title(title), _width(width), _height(height)
    {
        _window = CreateWindow(title.c_str(), _width, _height);
        _guiContext = ImGui::CreateContext();

        ImGui::SetCurrentContext(_guiContext);
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(_window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    ~Canvas() { glfwDestroyWindow(_window); }

    void RenderFrame()
    {
        ApplyRemove();
        glfwPollEvents();
        glfwMakeContextCurrent(_window);
        ImGui::SetCurrentContext(_guiContext);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // I don't know why when I use range-based loop here, the program will be crashed.
        for (const auto &_drawableObject : _drawableObjects) { _drawableObject->Draw(); }

        // for (auto it = _drawableObjects.begin(), end = _drawableObjects.end(); it != end; ++it) { (*it)->Render(); }
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(_window);
    }

    template <typename TDrawableObject, typename... Args>
        requires std::derived_from<TDrawableObject, IDrawable>
    std::shared_ptr<TDrawableObject> Create(Args &&...args)
    {
        auto obj = std::make_shared<TDrawableObject>(std::forward<Args>(args)...);
        _drawableObjects.emplace_back(obj);
        return obj;
    }

    void Add(const std::shared_ptr<IDrawable> &object) { _drawableObjects.emplace_back(object); }
    void Remove(const std::shared_ptr<IDrawable> &object) { _toBeRemovedObjects.emplace(object); }

    [[nodiscard]] GLFWwindow *GetWindow() const { return _window; }

  private:
    std::string _title;
    int _width, _height;
    GLFWwindow *_window;
    ImGuiContext *_guiContext;
    std::vector<std::shared_ptr<IDrawable>> _drawableObjects{};
    std::queue<std::shared_ptr<IDrawable>> _toBeRemovedObjects{};

    void ApplyRemove()
    {
        while (!_toBeRemovedObjects.empty())
        {
            auto obj = _toBeRemovedObjects.front();
            _toBeRemovedObjects.pop();
            std::erase(_drawableObjects, obj);
        }
    }

    static GLFWwindow *CreateWindow(const char *title, const int width, const int height)
    {
        const auto window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            throw std::runtime_error("Failed to initialize GLAD");
        }
        glfwSwapInterval(1); // 启用垂直同步
        return window;
    }
};

#endif // CANVAS_HPP
