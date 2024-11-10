#ifndef CANVASMANAGER_HPP
#define CANVASMANAGER_HPP

#include "Canvas.hpp"
#include <map>

class CanvasManager final
{
  public:
    CanvasManager(const CanvasManager &) = delete;
    CanvasManager &operator=(const CanvasManager &) = delete;
    static std::shared_ptr<CanvasManager> GetInstance()
    {
        static auto instance =
            std::shared_ptr<CanvasManager>(new CanvasManager, [](const CanvasManager *ptr) { delete ptr; });
        return instance;
    }
    int Run()
    {
        while (!_canvases.empty())
        {
            ApplyRemove();
            Update();
        }
        return 0;
    }

    std::shared_ptr<Canvas> CreateCanvas(const std::string &title)
    {
        auto canvas = std::make_shared<Canvas>(title);
        AddCanvas(canvas);
        return canvas;
    }

    void AddCanvas(const std::string &title, const int width, const int height)
    {
        AddCanvas(std::make_shared<Canvas>(title, width, height));
    }

    void AddCanvas(const std::shared_ptr<Canvas> &canvas)
    {
        _canvases.emplace_back(canvas);
        glfwSetWindowCloseCallback(canvas->GetWindow(), OnWindowClose);
        glfwSetWindowFocusCallback(canvas->GetWindow(), OnWindowFocus);
        _canvasMap[canvas->GetWindow()] = canvas;
    }

    void RemoveCanvas(const std::shared_ptr<Canvas> &canvas) { _toBeRemovedCanvases.emplace(canvas); }

  private:
    std::shared_ptr<Canvas> _currentCanvas = nullptr;
    std::vector<std::shared_ptr<Canvas>> _canvases;
    std::map<GLFWwindow *, std::shared_ptr<Canvas>> _canvasMap;
    std::queue<std::shared_ptr<Canvas>> _toBeRemovedCanvases;

    CanvasManager()
    {
        if (!glfwInit()) { throw std::runtime_error("Failed to initialize GLFW"); }
    }
    ~CanvasManager()
    {
        glfwTerminate();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    void ApplyRemove()
    {
        while (!_toBeRemovedCanvases.empty())
        {
            auto gui = _toBeRemovedCanvases.front();
            _toBeRemovedCanvases.pop();
            _canvasMap.erase(gui->GetWindow());
            std::erase(_canvases, gui);
        }
    }
    void Update()
    {
        if (_currentCanvas) { _currentCanvas->RenderFrame(); }
        else
        {
            for (const auto &canvas : _canvases) { canvas->RenderFrame(); }
        }
    }
    static void OnWindowClose(GLFWwindow *window)
    {
        const auto instance = GetInstance();
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        if (instance->_currentCanvas == instance->_canvasMap[window]) { instance->_currentCanvas = nullptr; }
        const auto canvas = instance->_canvasMap[window];
        instance->RemoveCanvas(canvas);
    }

    static void OnWindowFocus(GLFWwindow *window, const int focused)
    {
        const auto instance = GetInstance();
        if (focused) { instance->_currentCanvas = instance->_canvasMap[window]; }
    }
};

#endif // CANVASMANAGER_HPP
