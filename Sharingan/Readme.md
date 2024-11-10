# Sharingan

基于 [glad](https://github.com/Dav1dde/glad)，[glfw](https://github.com/glfw/glfw) 与 [imgui](https://github.com/ocornut/imgui) 的 UI 库

## 为什么要写这个库

因为我正在写一个图形界面(某一门课程的大作业)，但是发现 glfw 与 imgui 的 API 太复杂了，不仅复杂，而且既不 C++，也不 OOP，于是就把这些东西做了一层封装，让他更符合人类的使用习惯。

## 设计亮点

1. 毫无门槛的多窗口：可以轻松的创建多个窗口，不需要繁琐的设置。
2. 更舒适的 UI 开发体验：将原本 PO 的 Dear ImGui 封装为各种 OO 的组件，更符合现代开发习惯。
3. 更好的状态管理：每个 `ImGuiDialog` (ImGui 窗体)都有自己的状态，并且可以很方便的通过状态来控制组件的行为。
4. 几乎可以称为 **响应式** 的窗体设计：所有组件都可以通过自身的状态来控制组件的渲染。
5. 良好的接口设计：用户可以通过继承 `ImGuiDialogComponent<TParam>` 来实现自己的复合组件，更可以实现 `IDrawableOject` 来方便的将现有的渲染方案与 `Sharingan` 集成。

## 为什么要叫 Sharingan

Sharingan 来自 “万花筒写轮眼”，希望这个库能让人沉浸在 UI 的幻术中，因此就叫了这个名字

## 快速开始

要使用 Sharingan 非常简单，只需要在你的 CMake 项目中加上

```cmake
add_subdirectory("./PATH/TO/Sharingan")
target_link_libraries(YouProjectName Sharingan)
```

然后在 C++ 中只需要

```cpp
#include <Sharingan.h>
```

## 示例

> 你可以在 sample/basicusage 分支中找到直接可以编译的 CMake 工程

```cpp
#include <Sharingan.h>
#include <iostream>

struct MyState
{
    std::string Title;
    float Value{};
};

// 主函数
int main()
{
    {
        // 注意：这个作用域是必需的，否则窗口无法正常关闭，这是因为内部使用 shared_ptr 管理窗口的生命周期

        auto canvas = CanvasManager::GetInstance()->CreateCanvas("Test Window");                                  // 创建窗口
        auto dialog = canvas->Create<ImGuiDialog<>>("Title");                                                     // 创建不具有状态的对话框
        dialog->Create<ButtonComponent>("Click me", [](auto _) { std::cout << "I was clicked" << std::endl; });   // 添加一个具有自定义回调函数的按钮

        auto dialog2 = canvas->Create<ImGuiDialog<MyState>>([](auto p) { return p->Title; });                     // 创建具有自定义状态，并且根据状态切换标题的对话框
        dialog2->GetState()->Title = "Test";                                                                      // 设置初始标题

        dialog2->Create<SliderFloatComponent>("Slider", [](auto p) -> auto & { return p->Value; }, 114.f, 514.f); // 添加一个绑定到状态的滑动条
        dialog2->Create<ButtonComponent>("Text", [](auto p) { p->Title = std::to_string(p->Value); });            // 添加一个按下后会切换标题的按钮
    }
    return CanvasManager::GetInstance()->Run();
}
```

## 贡献

欢迎各种类型的贡献，包括但不限于 Star ，Issue 和 PR。
