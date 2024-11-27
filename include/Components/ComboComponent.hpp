#ifndef COMBOCOMPONENT_HPP
#define COMBOCOMPONENT_HPP

#include "WindowComponent.hpp"
#include <imgui.h>
#include <string>
#include <vector>
#include <utility>
#include <functional>

namespace Sharingan
{
template<typename TState>
class ComboComponent : public WindowComponent<TState>
{
public:
    ComboComponent() : _label(""), _currentItem(0), _onSelectCallback(nullptr), _visible(true)
    {
    }

    explicit ComboComponent(StringProvider label, std::vector<std::string> items = {}, 
                          std::function<void(int)> onSelectCallback = nullptr)
        : _label(std::move(label))
        , _items(std::move(items))
        , _onSelectCallback(std::move(onSelectCallback))
    {
    }

    void Render() override
    {
        if (_visible(this->_state)) {
            if (ImGui::BeginCombo(_label(this->_state).c_str(), _items[_currentItem].c_str())) {
                for (int i = 0; i < _items.size(); i++) {
                    const bool isSelected = (i == _currentItem);
                    if (ImGui::Selectable(_items[i].c_str(), isSelected)) {
                        _currentItem = i;
                        if (_onSelectCallback) {
                            _onSelectCallback(_currentItem);
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
        _items = items;
        _currentItem = std::min(_currentItem, static_cast<int>(_items.size()) - 1);
        return *this;
    }

    // 设置当前选中项
    ComboComponent& SetCurrentItem(int index) {
        if (index >= 0 && index < _items.size()) {
            _currentItem = index;
        }
        return *this;
    }

    // 设置选择回调
    ComboComponent& SetOnSelectCallback(std::function<void(int)> callback) {
        _onSelectCallback = std::move(callback);
        return *this;
    }

    // 设置可见性
    ComboComponent& SetVisible(std::function<bool(const TState&)> stateFunc) {
        _visible = ValueProvider<bool>(stateFunc);
        return *this;
    }

    // 获取当前选中项索引
    int GetCurrentItem() const { return _currentItem; }

    // 获取当前选中项文本
    std::string GetCurrentItemText() const { 
        return _currentItem >= 0 && _currentItem < _items.size() ? _items[_currentItem] : ""; 
    }

private:
    StringProvider _label;
    std::vector<std::string> _items;
    int _currentItem{0};
    std::function<void(int)> _onSelectCallback;
    ValueProvider<bool> _visible{true};
};

} // namespace Sharingan

#endif // COMBOCOMPONENT_HPP
