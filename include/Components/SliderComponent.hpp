#ifndef SLIDERCOMPONENT_HPP
#define SLIDERCOMPONENT_HPP

#include "ImGuiDialogComponent.h"

#include <imgui.h>

template <typename TParam>
class SliderFloatComponent : public ImGuiDialogComponent<TParam>
{
    using typename ImGuiDialogComponent<TParam>::StringProvider;
    using Binder = typename ImGuiDialogComponent<TParam>::template ParamBinder<float>;

  public:
    explicit SliderFloatComponent(std::shared_ptr<TParam> param, const std::string &title, Binder binder)
        : SliderFloatComponent(param, title, binder, 0.0f, 100.0f)
    {
    }
    explicit SliderFloatComponent(std::shared_ptr<TParam> param, const std::string &title, Binder binder, float min,
                                  float max)
        : SliderFloatComponent(param, [title](auto _) { return title; }, binder, min, max)
    {
    }

    explicit SliderFloatComponent(std::shared_ptr<TParam> param, StringProvider title, Binder binder)
        : SliderFloatComponent(param, title, binder, 0.0f, 100.0f)
    {
    }

    explicit SliderFloatComponent(std::shared_ptr<TParam> param, StringProvider title, Binder binder, const float min,
                                  const float max)
        : _min(min), _max(max), _value(&binder(param)), _title(title), _param(param)
    {
    }

    void Render() override { ImGui::SliderFloat(_title(_param).c_str(), _value, _min, _max); }

  private:
    float _min, _max;
    float *_value;
    StringProvider _title;
    std::shared_ptr<TParam> _param;
};

template <typename TParam>
class SliderIntComponent : public ImGuiDialogComponent<TParam>
{
    using typename ImGuiDialogComponent<TParam>::StringProvider;
    using Binder = typename ImGuiDialogComponent<TParam>::template ParamBinder<int>;

  public:
    explicit SliderIntComponent(std::shared_ptr<TParam> param, const std::string &title, Binder binder)
        : SliderIntComponent(param, title, binder, 0, 100)
    {
    }
    explicit SliderIntComponent(std::shared_ptr<TParam> param, const std::string &title, Binder binder, int min,
                                int max)
        : SliderIntComponent(param, [title](auto _) { return title; }, binder, min, max)
    {
    }

    explicit SliderIntComponent(std::shared_ptr<TParam> param, StringProvider title, Binder binder)
        : SliderIntComponent(param, title, binder, 0, 100)
    {
    }

    explicit SliderIntComponent(std::shared_ptr<TParam> param, StringProvider title, Binder binder, const float min,
                                const float max)
        : _min(min), _max(max), _value(&binder(param)), _title(title), _param(param)
    {
    }

    void Render() override { ImGui::SliderInt(_title(_param).c_str(), _value, _min, _max); }

  private:
    int _min, _max;
    int *_value;
    StringProvider _title;
    std::shared_ptr<TParam> _param;
};

#endif // SLIDERCOMPONENT_HPP