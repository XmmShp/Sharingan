#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <utility>

namespace Sharingan
{
template<typename TState>
class TextComponent : public WindowComponent<TState>
{
public:
    TextComponent() = default;

    void Render() override
    {
        if (this->IsVisible()) {
            ImGui::Text("%s", this->GetLabel().c_str());
        }
    }
};

} // namespace Sharingan

#endif // TEXTCOMPONENT_HPP
