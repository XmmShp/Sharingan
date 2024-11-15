#ifndef WINDOWCOMPONENT_HPP
#define WINDOWCOMPONENT_HPP

#include <functional>
#include <string>
#include <utility>

namespace Sharingan
{
using Callback = std::function<void()>;

class WindowComponent
{
  public:
    virtual ~WindowComponent() = default;
    virtual void Render() = 0;
};

class StringProvider
{
  public:
    StringProvider(const char *str) : _provider([str]() { return str; }) {}

    StringProvider(const std::string &str) : _provider([str]() { return str; }) {}

    StringProvider(std::function<std::string()> func) : _provider(std::move(func)) {}

    std::string operator()() const { return _provider(); }

  private:
    std::function<std::string()> _provider;
};
} // namespace Sharingan

#endif // WINDOWCOMPONENT_HPP
