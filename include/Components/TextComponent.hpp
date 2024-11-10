#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include "ImGuiDialogComponent.h"

#include <imgui.h>

template <typename TState>
class TextComponent : public ImGuiDialogComponent<TState>
{
    using typename ImGuiDialogComponent<TState>::StringProvider;

  public:
    explicit TextComponent(std::shared_ptr<TState> state, const std::string &content)
        : TextComponent(state, [content](auto _) { return content; })
    {
    }
    explicit TextComponent(std::shared_ptr<TState> state, StringProvider contentProvider)
        : _content(std::move(contentProvider)), _state(state)
    {
    }
    void Render() override { ImGui::Text(_content(_state).c_str()); }

  private:
    StringProvider _content;
    std::shared_ptr<TState> _state;
};

#endif // TEXTCOMPONENT_HPP
