#ifndef IMGUIDIALOG_HPP
#define IMGUIDIALOG_HPP

#include "Components/ImGuiDialogComponent.h"
#include "IDrawable.h"
#include "imgui.h"

#include <memory>
#include <utility>
#include <vector>

class DefaultParam
{
  public:
    std::string Title = " ";
};

template <typename TParam = DefaultParam>
class ImGuiDialog final : public IDrawable
{
    using StringProvider = std::function<std::string(std::shared_ptr<TParam>)>;

  public:
    std::shared_ptr<TParam> GetParam() { return _param; }
    explicit ImGuiDialog(const std::string &title) : ImGuiDialog([title](auto _) { return title; }) {}
    explicit ImGuiDialog(StringProvider title) : ImGuiDialog(title, std::make_shared<TParam>()) {}
    explicit ImGuiDialog(StringProvider title, const std::shared_ptr<TParam> &param)
        : _title(std::move(title)), _param(param)
    {
    }
    template <template <typename> class TComponent, typename... Args>
    void Create(Args &&...args)
    {
        Create<TComponent<TParam>>(_param, std::forward<Args>(args)...);
    }
    void Add(const std::shared_ptr<ImGuiDialogComponent<TParam>> &component) { _components.emplace_back(component); }
    void Remove(const std::shared_ptr<ImGuiDialogComponent<TParam>> &component) { std::erase(_components, component); }
    void Draw() override
    {
        ImGui::Begin(_title(_param).c_str());
        for (const auto &component : _components) { component->Render(); }
        ImGui::End();
    }

  private:
    StringProvider _title;
    std::shared_ptr<TParam> _param;
    std::vector<std::shared_ptr<ImGuiDialogComponent<TParam>>> _components{};

    template <typename TComponent, typename... Args>
        requires std::derived_from<TComponent, ImGuiDialogComponent<TParam>>
    void Create(Args &&...args)
    {
        auto component = std::make_shared<TComponent>(std::forward<Args>(args)...);
        Add(std::make_shared<TComponent>(std::forward<Args>(args)...));
    }
};

#endif // IMGUIDIALOG_HPP
