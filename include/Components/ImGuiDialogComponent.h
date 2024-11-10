#ifndef IMGUIDIALOGCOMPONENT_H
#define IMGUIDIALOGCOMPONENT_H

#include <functional>
#include <memory>

template <typename TParam>
class ImGuiDialogComponent
{
  protected:
    using StringProvider = std::function<const std::string(std::shared_ptr<TParam>)>;
    using Callback = std::function<void(std::shared_ptr<TParam>)>;
    template <typename TParamToBind>
    using ParamBinder = std::function<TParamToBind &(std::shared_ptr<TParam>)>;

  public:
    virtual ~ImGuiDialogComponent() = default;
    virtual void Render() = 0;
};

#endif // IMGUIDIALOGCOMPONENT_H
