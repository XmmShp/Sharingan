#ifndef BUTTONCOMPONENT_HPP
#define BUTTONCOMPONENT_HPP

#include "ImGuiDialogComponent.h"
#include <imgui.h>

template <typename TParam>
class ButtonComponent : public ImGuiDialogComponent<TParam>
{
    using typename ImGuiDialogComponent<TParam>::Callback;
    using typename ImGuiDialogComponent<TParam>::StringProvider;

  public:
    explicit ButtonComponent(std::shared_ptr<TParam> param, const std::string &title, const Callback &callback = {})
        : ButtonComponent(param, [title](auto _) { return std::string(title); }, callback)
    {
    }
    explicit ButtonComponent(std::shared_ptr<TParam> param, StringProvider title, Callback callback = {})
        : _title(std::move(title)), _callback(callback), _param(param)
    {
    }
    void Render() override
    {
        if (ImGui::Button(_title(_param).c_str()))
        {
            if (_callback) _callback(_param);
        }
    }

  private:
    StringProvider _title;
    Callback _callback;
    std::shared_ptr<TParam> _param;
};

#endif // BUTTONCOMPONENT_HPP
