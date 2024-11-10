#ifndef SLIDERCOMPONENT_HPP
#define SLIDERCOMPONENT_HPP

#include "ImGuiDialogComponent.h"

#include <imgui.h>

template <typename TState>
class SliderFloatComponent : public ImGuiDialogComponent<TState>
{
    using typename ImGuiDialogComponent<TState>::StringProvider;
    using Binder = typename ImGuiDialogComponent<TState>::template StateBinder<float>;

  public:
    explicit SliderFloatComponent(std::shared_ptr<TState> state, const std::string &title, Binder binder)
        : SliderFloatComponent(state, title, binder, 0.0f, 100.0f)
    {
    }
    explicit SliderFloatComponent(std::shared_ptr<TState> state, const std::string &title, Binder binder, float min,
                                  float max)
        : SliderFloatComponent(state, [title](auto _) { return title; }, binder, min, max)
    {
    }

    explicit SliderFloatComponent(std::shared_ptr<TState> state, StringProvider title, Binder binder)
        : SliderFloatComponent(state, title, binder, 0.0f, 100.0f)
    {
    }

    explicit SliderFloatComponent(std::shared_ptr<TState> state, StringProvider title, Binder binder, const float min,
                                  const float max)
        : _min(min), _max(max), _value(&binder(state)), _title(title), _state(state)
    {
    }

    void Render() override { ImGui::SliderFloat(_title(_state).c_str(), _value, _min, _max); }

  private:
    float _min, _max;
    float *_value;
    StringProvider _title;
    std::shared_ptr<TState> _state;
};

template <typename TState>
class SliderIntComponent : public ImGuiDialogComponent<TState>
{
    using typename ImGuiDialogComponent<TState>::StringProvider;
    using Binder = typename ImGuiDialogComponent<TState>::template StateBinder<int>;

  public:
    explicit SliderIntComponent(std::shared_ptr<TState> state, const std::string &title, Binder binder)
        : SliderIntComponent(state, title, binder, 0, 100)
    {
    }
    explicit SliderIntComponent(std::shared_ptr<TState> state, const std::string &title, Binder binder, int min,
                                int max)
        : SliderIntComponent(state, [title](auto _) { return title; }, binder, min, max)
    {
    }

    explicit SliderIntComponent(std::shared_ptr<TState> state, StringProvider title, Binder binder)
        : SliderIntComponent(state, title, binder, 0, 100)
    {
    }

    explicit SliderIntComponent(std::shared_ptr<TState> state, StringProvider title, Binder binder, const float min,
                                const float max)
        : _min(min), _max(max), _value(&binder(state)), _title(title), _state(state)
    {
    }

    void Render() override { ImGui::SliderInt(_title(_state).c_str(), _value, _min, _max); }

  private:
    int _min, _max;
    int *_value;
    StringProvider _title;
    std::shared_ptr<TState> _state;
};

#endif // SLIDERCOMPONENT_HPP