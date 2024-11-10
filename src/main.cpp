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
        auto canvas = CanvasManager::GetInstance()->CreateCanvas("Test Window"); // 创建窗口
        auto dialog = canvas->Create<ImGuiDialog<>>("Title");                    // 创建不具有状态的对话框
        dialog->Create<ButtonComponent>(
            "Click me", [](auto _) { std::cout << "I was clicked" << std::endl; }); // 添加一个具有自定义回调函数的按钮
        auto dialog2 = canvas->Create<ImGuiDialog<MyState>>(
            [](auto p) { return p->Title; }); // 创建具有自定义状态，并且根据状态切换标题的对话框
        dialog2->GetState()->Title = "Test";  // 设置初始标题
        dialog2->Create<SliderFloatComponent>(
            "Slider", [](auto p) -> auto & { return p->Value; }, 114.f, 514.f); // 添加一个绑定到状态的滑动条
        dialog2->Create<ButtonComponent>(
            "Text", [](auto p) { p->Title = std::to_string(p->Value); }); // 添加一个按下后会切换标题的按钮
    }
    return CanvasManager::GetInstance()->Run();
}