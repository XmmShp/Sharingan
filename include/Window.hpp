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
class DefaultState {};

template <typename TState = DefaultState>
class Window
{
public:
    explicit Window(std::string title, const ImGuiWindowFlags flags = 0)
        : _title(std::move(title)), _flags(flags), _state(std::unique_ptr<TState>(new TState()))
    {
    }

    template<template<typename> class TComponent>
    TComponent<TState>& AddComponent() {
        auto component = std::unique_ptr<TComponent<TState>>(new TComponent<TState>());
        component->SetState(_state.get());
        auto& componentRef = *component;
        _components.push_back(std::move(component));
        return componentRef;
    }

    template<typename TComponent>
    TComponent& Add(const TComponent& component) {
        static_assert(std::is_base_of_v<WindowComponent<TState>, TComponent>, 
            "Component must inherit from WindowComponent<TState>");
        auto componentCopy = std::unique_ptr<TComponent>(new TComponent(component));
        componentCopy->SetState(_state.get());
        auto& componentRef = *componentCopy;
        _components.push_back(std::move(componentCopy));
        return componentRef;
    }

    void Draw()
    {
        ImGui::Begin(_title.c_str(), nullptr, _flags);
        for (const auto &component : _components) { 
            component->Render(); 
        }
        ImGui::End();
    }

    TState& GetState() { return *_state; }
    const TState& GetState() const { return *_state; }

private:
    std::string _title;
    ImGuiWindowFlags _flags;
    std::unique_ptr<TState> _state;
    std::vector<std::unique_ptr<WindowComponent<TState>>> _components{};
};

} // namespace Sharingan

#endif // WINDOW_HPP
