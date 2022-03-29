
//
//  Menu class
//  Inspired
//
//
//



#ifndef FORFEDREDIAGRAM_MENU_HPP
#define FORFEDREDIAGRAM_MENU_HPP

#include <iostream>
#include <any>
#include <string>
#include <utility>
#include <variant>
#include <vector>
#include <type_traits>
#include <optional>
#include <sstream>
#include <limits>
#include <cctype>
#include <functional>

#include "commonFunctions.hpp"


class Menu {
private:

    struct MenuItem
    {
        std::string name;
        std::variant<std::function<void()>, Menu*> func;
    };

    using vecMenuItems = std::vector<MenuItem>;

public:
    Menu() = default;
    Menu(std::string title, vecMenuItems  menuItems) : _title(std::move(title)), _menuItems(std::move(menuItems)) {}

    auto title() const noexcept
    {
        return _title;
    }

    void title(const std::string& t)
    {
        _title = t;
    }

    void show()
    {
        show(*this);
    }


    [[nodiscard]] bool isEmpty() const{
        return !_menuItems.empty();
    }


    [[nodiscard]] size_t size() const{
        return _menuItems.size();
    }


    bool erase(size_t indx)
    {
        if (indx < _menuItems.size()) {
            _menuItems.erase(_menuItems.begin() + indx);
            return true;
        }

        return false;
    }

    bool append(const MenuItem& mi)
    {
        _menuItems.emplace_back(mi);
        return true;
    }

    bool insert(size_t indx, const MenuItem& mi)
    {
        if (indx < _menuItems.size()) {
            _menuItems.insert(_menuItems.begin() + indx, mi);
            return true;
        }

        return false;
    }

private:
    void show(const Menu& m)
    {
        const auto menuChoice = [menuCount = m._menuItems.size()](const Menu& menu) {
            std::ostringstream oSStream;

            oSStream << std::endl << menu.title() << std::endl << std::endl;

            for (size_t i = 0U; i < menuCount; ++i)
                oSStream << i + 1 << ")  " << menu._menuItems[i].name << std::endl;

            oSStream << "0)  Exit meny\n\nSkriv inn menyvalg";
            return COM::getNum<size_t>(oSStream.str());

        };

        for (size_t opt = 0U; (opt = menuChoice(m)) > 0;)
            if (const auto& menuItem = m._menuItems[opt - 1]; std::holds_alternative<std::function<void()>>(menuItem.func))
                std::get<std::function<void()>>(menuItem.func)();
            else {
                std::cout << "Going to another menu" << std::endl;
                show(*std::get<Menu *>(menuItem.func));
            }
    }

    std::string _title;
    vecMenuItems _menuItems;
};





#endif //FORFEDREDIAGRAM_MENU_HPP
