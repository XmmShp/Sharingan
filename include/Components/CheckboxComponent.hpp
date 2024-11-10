#ifndef CHECKBOXCOMPONENT_H
#define CHECKBOXCOMPONENT_H

#include "ImGuiDialogComponent.h"
#include "imgui.h"

template <typename TParam>
class CheckboxComponent : public ImGuiDialogComponent<TParam>
{
    using typename ImGuiDialogComponent<TParam>::StringProvider;
    using Binder = typename ImGuiDialogComponent<TParam>::template ParamBinder<bool>;

  public:
    explicit CheckboxComponent(std::shared_ptr<TParam> param, const std::string &title, Binder binder)
        : CheckboxComponent(param, [title](auto _) { return title; }, binder)
    {
    }

    explicit CheckboxComponent(std::shared_ptr<TParam> param, StringProvider title, Binder binder)
        : _value(&binder(param)), _title(title), _param(param)
    {
    }

    void Render() override { ImGui::Checkbox(_title(_param).c_str(), _value); }

  private:
    bool *_value;
    StringProvider _title;
    std::shared_ptr<TParam> _param;
};

#endif // CHECKBOXCOMPONENT_H
