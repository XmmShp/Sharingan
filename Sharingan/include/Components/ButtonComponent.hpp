#ifndef BUTTONCOMPONENT_HPP
#define BUTTONCOMPONENT_HPP

#include "ImGuiDialogComponent.h"
#include <imgui.h>

template <typename TState>
class ButtonComponent : public ImGuiDialogComponent<TState>
{
    using typename ImGuiDialogComponent<TState>::Callback;
    using typename ImGuiDialogComponent<TState>::StringProvider;

  public:
    explicit ButtonComponent(std::shared_ptr<TState> state, const std::string &title, const Callback &callback = {})
        : ButtonComponent(state, [title](auto _) { return std::string(title); }, callback)
    {
    }
    explicit ButtonComponent(std::shared_ptr<TState> state, StringProvider title, Callback callback = {})
        : _title(std::move(title)), _callback(callback), _state(state)
    {
    }
    void Render() override
    {
        if (ImGui::Button(_title(_state).c_str()))
        {
            if (_callback) _callback(_state);
        }
    }

  private:
    StringProvider _title;
    Callback _callback;
    std::shared_ptr<TState> _state;
};

#endif // BUTTONCOMPONENT_HPP
