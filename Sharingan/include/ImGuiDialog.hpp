#ifndef IMGUIDIALOG_HPP
#define IMGUIDIALOG_HPP

#include "Components/ImGuiDialogComponent.h"
#include "IDrawable.h"
#include "imgui.h"

#include <memory>
#include <utility>
#include <vector>

class DefaultState
{
};

template <typename TState = DefaultState>
class ImGuiDialog final : public IDrawable
{
    using StringProvider = std::function<std::string(std::shared_ptr<TState>)>;

  public:
    std::shared_ptr<TState> GetState() { return _state; }
    explicit ImGuiDialog(const std::string &title) : ImGuiDialog([title](auto _) { return title; }) {}
    explicit ImGuiDialog(StringProvider title) : ImGuiDialog(title, std::make_shared<TState>()) {}
    explicit ImGuiDialog(StringProvider title, const std::shared_ptr<TState> &state)
        : _title(std::move(title)), _state(state)
    {
    }
    template <template <typename> class TComponent, typename... Args>
    void Create(Args &&...args)
    {
        Create<TComponent<TState>>(_state, std::forward<Args>(args)...);
    }
    void Add(const std::shared_ptr<ImGuiDialogComponent<TState>> &component) { _components.emplace_back(component); }
    void Remove(const std::shared_ptr<ImGuiDialogComponent<TState>> &component) { std::erase(_components, component); }
    void Draw() override
    {
        ImGui::Begin(_title(_state).c_str());
        for (const auto &component : _components) { component->Render(); }
        ImGui::End();
    }

  private:
    StringProvider _title;
    std::shared_ptr<TState> _state;
    std::vector<std::shared_ptr<ImGuiDialogComponent<TState>>> _components{};

    template <typename TComponent, typename... Args>
        requires std::derived_from<TComponent, ImGuiDialogComponent<TState>>
    void Create(Args &&...args)
    {
        auto component = std::make_shared<TComponent>(std::forward<Args>(args)...);
        Add(std::make_shared<TComponent>(std::forward<Args>(args)...));
    }
};

#endif // IMGUIDIALOG_HPP
