#ifndef COMBOCOMPONENT_HPP
#define COMBOCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <optional>
#include <algorithm>

namespace Sharingan
{
template<typename TState>
class ComboComponent : public WindowComponent<TState>
{
public:
    using OnSelectCallback = std::function<void(ComboComponent&, int)>;

    ComboComponent() : _label(""), _onSelectCallback(nullptr), _visible(true)
    {
    }

    explicit ComboComponent(StringProvider label, std::vector<std::string> items = {}, 
                          OnSelectCallback onSelectCallback = nullptr)
        : _label(std::move(label))
        , _items(std::move(items))
        , _onSelectCallback(std::move(onSelectCallback))
    {
    }

    void Render() override
    {
        if (!_valueBinder || !_items.has_value()) return;
        if (_visible(this->_state)) {
            int& currentItem = _valueBinder(*const_cast<TState*>(this->_state));
            const auto& items = _items.value()(this->_state);
            currentItem = std::clamp(currentItem, 0, static_cast<int>(items.size()) - 1);
            
            if (ImGui::BeginCombo(_label(this->_state).c_str(), items[currentItem].c_str())) {
                for (int i = 0; i < items.size(); i++) {
                    const bool isSelected = (i == currentItem);
                    if (ImGui::Selectable(items[i].c_str(), isSelected)) {
                        currentItem = i;
                        if (_onSelectCallback) {
                            _onSelectCallback(*this, currentItem);
                        }
                    }
                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }
        }
    }

    // 设置标签
    ComboComponent& SetLabel(const std::string& label) {
        _label = StringProvider(label);
        return *this;
    }

    ComboComponent& SetLabel(std::function<std::string(const TState&)> stateFunc) {
        _label = StringProvider(stateFunc);
        return *this;
    }

    // 设置选项
    ComboComponent& SetItems(const std::vector<std::string>& items) {
        _items = ValueProvider<std::vector<std::string>>(items);
        return *this;
    }

    ComboComponent& SetItems(std::function<std::vector<std::string>(const TState&)> stateFunc) {
        _items = ValueProvider<std::vector<std::string>>(stateFunc);
        return *this;
    }

    // 设置值路由
    ComboComponent& SetValueRoute(std::function<int&(TState&)> valueBinder) {
        _valueBinder = std::move(valueBinder);
        return *this;
    }

    // 设置选择回调
    ComboComponent& SetOnSelectCallback(OnSelectCallback callback) {
        _onSelectCallback = std::move(callback);
        return *this;
    }

    // 设置可见性
    ComboComponent& SetVisible(std::function<bool(const TState&)> stateFunc) {
        _visible = ValueProvider<bool>(stateFunc);
        return *this;
    }

    // 获取当前选中项文本
    std::string GetCurrentItemText() const { 
        if (!_valueBinder || !_items.has_value()) return "";
        const int currentItem = _valueBinder(*static_cast<const TState*>(this->_state));
        const auto& items = _items.value()(*this->_state);
        return currentItem >= 0 && currentItem < items.size() ? items[currentItem] : ""; 
    }

private:
    StringProvider _label;
    OnSelectCallback _onSelectCallback;
    std::function<int&(TState&)> _valueBinder;
    std::optional<ValueProvider<std::vector<std::string>>> _items;
    ValueProvider<bool> _visible{true};
};

} // namespace Sharingan

#endif // COMBOCOMPONENT_HPP
