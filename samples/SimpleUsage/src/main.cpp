#include <glad/glad.h>

#include <iostream>

#include "Components/ButtonComponent.hpp"
#include "Components/TextComponent.hpp"
#include "Components/CheckboxComponent.hpp"
#include "Components/SliderComponent.hpp"
#include "Components/InputTextComponent.hpp"
#include "Components/ComboComponent.hpp"
#include "Components/ColorPickerComponent.hpp"
#include "Components/ProgressBarComponent.hpp"
#include "Window.hpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include <GLFW/glfw3.h>

#include <string>

// 初始化 GLFW 和 ImGui 使用 GLAD 加载 OpenGL
bool initGLFWAndImGui(GLFWwindow *&window)
{
    // 初始化 GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // 创建窗口
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(1280, 720, "ImGui Example", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // 启用 VSync

    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // 初始化 ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // 设置 ImGui 样式
    ImGui::StyleColorsDark();

    // 设置平台和渲染器后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    return true;
}

// 清理资源
void cleanup(GLFWwindow *window)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

// 示例状态
struct CounterState {
    int counter = 0;
    bool showMessage = true;
    float sliderValue = 0.5f;
    int sliderIntValue = 50;
    std::string inputText = "Hello, World!";
    std::array<float, 4> color = {1.0f, 0.0f, 0.0f, 1.0f};  // 红色
    int selectedItem = 0;
    float progress = 0.0f;
};

int main(int, char **)
{
    GLFWwindow* window = nullptr;
    if (!initGLFWAndImGui(window)) {
        return -1;
    }

    // 创建一个带状态的窗口
    Sharingan::Window<CounterState> mainWindow("Sharingan Components Demo");

    // 添加按钮组件
    mainWindow.AddComponent<Sharingan::ButtonComponent>()
        .SetTitle("Increment Counter")
        .SetCallback([&mainWindow]() {
            mainWindow.GetState().counter++;
        });

    // 添加文本组件显示计数器
    mainWindow.AddComponent<Sharingan::TextComponent>()
        .SetText([](const CounterState& state) {
            return "Counter: " + std::to_string(state.counter);
        })
        .SetVisible([](const CounterState& state){
            return state.showMessage;
        });

    // 添加复选框组件
    mainWindow.AddComponent<Sharingan::CheckboxComponent>()
        .SetLabel("Show Counter")
        .SetChecked(true)
        .SetOnChangeCallback([&mainWindow](bool checked) {
            mainWindow.GetState().showMessage = checked;
        });

    // 添加浮点数滑块组件
    mainWindow.AddComponent<Sharingan::SliderFloatComponent>()
        .SetLabel("Float Slider")
        .SetValue(0.5f)
        .SetRange(0.0f, 1.0f)
        .SetFormat("%.2f")
        .SetOnChangeCallback([&mainWindow](float value) {
            mainWindow.GetState().sliderValue = value;
        });

    // 添加整数滑块组件
    mainWindow.AddComponent<Sharingan::SliderIntComponent>()
        .SetLabel("Int Slider")
        .SetValue(50)
        .SetRange(0, 100)
        .SetOnChangeCallback([&mainWindow](int value) {
            mainWindow.GetState().sliderIntValue = value;
        });

    // 添加文本输入组件
    mainWindow.AddComponent<Sharingan::InputTextComponent>()
        .SetLabel("Input Text")
        .SetOnChangeCallback([&mainWindow](const std::string& text) {
            mainWindow.GetState().inputText = text;
        });

    // 添加下拉框组件
    mainWindow.AddComponent<Sharingan::ComboComponent>()
        .SetLabel("Combo Box")
        .SetItems({"Option 1", "Option 2", "Option 3"})
        .SetOnSelectCallback([&mainWindow](int index) {
            mainWindow.GetState().selectedItem = index;
        });

    // 添加颜色选择器组件
    mainWindow.AddComponent<Sharingan::ColorPickerComponent>()
        .SetLabel("Color Picker")
        .SetColor({1.0f, 0.0f, 0.0f, 1.0f})
        .SetOnChangeCallback([&mainWindow](const std::array<float, 4>& color) {
            mainWindow.GetState().color = color;
        });

    // 添加进度条组件
    auto progressBar = mainWindow.AddComponent<Sharingan::ProgressBarComponent>()
        .SetLabel("Progress")
        .SetOverlayText([](const CounterState& state) {
            return std::to_string(static_cast<int>(state.progress * 100)) + "%";
        });

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 更新进度条（示例：循环进度）
        mainWindow.GetState().progress += 0.001f;
        if (mainWindow.GetState().progress > 1.0f) {
            mainWindow.GetState().progress = 0.0f;
        }
        progressBar.SetFraction(mainWindow.GetState().progress);

        mainWindow.Draw();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    cleanup(window);
    return 0;
}