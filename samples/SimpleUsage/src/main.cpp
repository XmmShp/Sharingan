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
        .SetCallback([](auto btn) {
            const_cast<CounterState*>(btn.GetState())->counter++;
        })
        .SetLabel("Increment Counter");

    // 添加文本组件显示计数器
    mainWindow.AddComponent<Sharingan::TextComponent>()
        .SetLabel([](const CounterState& state) {
            return "Counter: " + std::to_string(state.counter);
        })
        .SetVisible([](const CounterState& state){
            return state.showMessage;
        });

    // 添加复选框组件
    mainWindow.AddComponent<Sharingan::CheckboxComponent>()
        .SetValueRoute([](CounterState& state)->bool& { return state.showMessage; })
        .SetOnChangeCallback([](auto _,bool __) {
            std::cout<<"Checkbox changed"<<std::endl; 
        })
        .SetLabel("Show Counter");
        

    // 添加浮点数滑块组件
    mainWindow.AddComponent<Sharingan::SliderFloatComponent>()
        .SetValueRoute([](CounterState& state)->float& { return state.sliderValue; })
        .SetRange(0.0f, 1.0f)
        .SetOnChangeCallback([](auto _, float value) {
            std::cout<<"Slider value changed: "<<value<<std::endl;
        })
        .SetLabel("Float Slider");

    // 添加整数滑块组件
    mainWindow.AddComponent<Sharingan::SliderIntComponent>()
        .SetValueRoute([](CounterState& state)->int& { return state.sliderIntValue; })
        .SetRange(0, 100)
        .SetOnChangeCallback([](auto _,int value) {
            std::cout<<"Slider value changed: "<<value<<std::endl;
        })
        .SetLabel("Int Slider");

    // 添加文本输入组件
    mainWindow.AddComponent<Sharingan::InputTextComponent>()
        .SetValueRoute([](CounterState& state)->std::string& { return state.inputText; })
        .SetOnChangeCallback([](auto _, const std::string& text) {
            std::cout<<"Input text changed: "<<text<<std::endl;
        })
        .SetLabel("Input Text");

    // 添加下拉框组件
    mainWindow.AddComponent<Sharingan::ComboComponent>()
        .SetItems({"Option 1", "Option 2", "Option 3"})
        .SetLabel("Combo Box");

    // 添加颜色选择器组件
    mainWindow.AddComponent<Sharingan::ColorPickerComponent>()
        .SetValueRoute([](CounterState& state)->std::array<float, 4>& { return state.color; })
        .SetLabel("Color Picker");

    // 添加进度条组件
    mainWindow.AddComponent<Sharingan::ProgressBarComponent>()
        .SetFraction([](const CounterState& state) {
            return state.progress;
        })
        .SetOverlayText([](const CounterState& state) {
            return std::to_string(static_cast<int>(state.progress * 100)) + "%";
        })
        .SetLabel("Progress");

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 更新进度条（示例：循环进度）
        static float progress = 0.0f;
        progress += 0.01f;
        if (progress > 1.0f) {
            progress = 0.0f;
        }
        mainWindow.GetState().progress = progress;

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