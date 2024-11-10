#ifndef CHECKBOXCOMPONENT_H
#define CHECKBOXCOMPONENT_H

#include "ImGuiDialogComponent.h"
#include "imgui.h"

template <typename TState>
class CheckboxComponent : public ImGuiDialogComponent<TState>
{
    using typename ImGuiDialogComponent<TState>::StringProvider;
    using Binder = typename ImGuiDialogComponent<TState>::template StateBinder<bool>;

  public:
    explicit CheckboxComponent(std::shared_ptr<TState> state, const std::string &title, Binder binder)
        : CheckboxComponent(state, [title](auto _) { return title; }, binder)
    {
    }

    explicit CheckboxComponent(std::shared_ptr<TState> state, StringProvider title, Binder binder)
        : _value(&binder(state)), _title(title), _state(state)
    {
    }

    void Render() override { ImGui::Checkbox(_title(_state).c_str(), _value); }

  private:
    bool *_value;
    StringProvider _title;
    std::shared_ptr<TState> _state;
};

#endif // CHECKBOXCOMPONENT_H
