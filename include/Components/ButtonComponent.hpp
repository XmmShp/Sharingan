#ifndef BUTTONCOMPONENT_HPP
#define BUTTONCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <utility>

namespace Sharingan
{
class ButtonComponent : public WindowComponent
{

  public:
    explicit ButtonComponent(StringProvider title, Callback callback)
        : _title(std::move(title)), _callback(std::move(callback))
    {
    }

    void Render() override
    {
        if (ImGui::Button(_title().c_str())) { _callback(); }
    }

  private:
    StringProvider _title;
    Callback _callback;
};
} // namespace Sharingan

#endif // BUTTONCOMPONENT_HPP
