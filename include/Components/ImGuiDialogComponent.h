#ifndef IMGUIDIALOGCOMPONENT_H
#define IMGUIDIALOGCOMPONENT_H

#include <functional>
#include <memory>

template <typename TState>
class ImGuiDialogComponent
{
  protected:
    using StringProvider = std::function<const std::string(std::shared_ptr<TState>)>;
    using Callback = std::function<void(std::shared_ptr<TState>)>;
    template <typename TStateToBind>
    using StateBinder = std::function<TStateToBind &(std::shared_ptr<TState>)>;

  public:
    virtual ~ImGuiDialogComponent() = default;
    virtual void Render() = 0;
};

#endif // IMGUIDIALOGCOMPONENT_H
