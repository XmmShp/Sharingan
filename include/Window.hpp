#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <imgui.h>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Components/WindowComponent.hpp"

namespace Sharingan
{
class DefaultState
{
};

template <typename TState = DefaultState>
class Window
{
  public:
    explicit Window(std::string title, const ImGuiWindowFlags flags = 0)
        : _title(std::move(title)), _flags(flags), _state(new TState)
    {
    }
    void Add(WindowComponent *component) { _components.emplace_back(component); }
    void Draw()
    {
        ImGui::Begin(_title.c_str(), nullptr, _flags);
        for (const auto &component : _components) { component->Render(); }
        ImGui::End();
    }
    TState &GetState() { return *_state; }

  private:
    std::string _title;
    ImGuiWindowFlags _flags;
    std::unique_ptr<TState> _state;
    std::vector<std::unique_ptr<WindowComponent>> _components{};
};
} // namespace Sharingan

#endif // WINDOW_HPP
