#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include "ImGuiDialogComponent.h"

#include <imgui.h>

template <typename TParam>
class TextComponent : public ImGuiDialogComponent<TParam>
{
    using typename ImGuiDialogComponent<TParam>::StringProvider;

  public:
    explicit TextComponent(std::shared_ptr<TParam> param, const std::string &content)
        : TextComponent(param, [content](auto _) { return content; })
    {
    }
    explicit TextComponent(std::shared_ptr<TParam> param, StringProvider contentProvider)
        : _content(std::move(contentProvider)), _param(param)
    {
    }
    void Render() override { ImGui::Text(_content(_param).c_str()); }

  private:
    StringProvider _content;
    std::shared_ptr<TParam> _param;
};

#endif // TEXTCOMPONENT_HPP
