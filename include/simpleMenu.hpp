//
// Created by simen on 3/28/2022.
//

#ifndef FORFEDREDIAGRAM_SIMPLEMENU_HPP
#define FORFEDREDIAGRAM_SIMPLEMENU_HPP

#include <iostream>
#include <any>
#include <string>
#include <variant>
#include <vector>
#include <type_traits>
#include <optional>
#include <sstream>
#include <limits>
#include <cctype>

#include "commonFunctions.hpp"


class Menu {
private:
    using f_type = void(*)(std::any& param);

    struct MenItm
    {
        std::string name;
        std::variant<f_type, Menu*> func;
    };

    using vmi = std::vector<MenItm>;

public:
    Menu() = default;
    Menu(const std::string& t, const vmi& vm) : _title(t), _menuItems(vm) {}

    auto title() const noexcept
    {
        return _title;
    }

    void title(const std::string& t)
    {
        _title = t;
    }

    void menu(std::any& param)
    {
        menu(*this, param);
    }

    bool erase(size_t indx)
    {
        if (indx < _menuItems.size()) {
            _menuItems.erase(_menuItems.begin() + indx);
            return true;
        }

        return false;
    }

    bool append(const MenItm& mi)
    {
        _menuItems.emplace_back(mi);
        return true;
    }

    bool insert(size_t indx, const MenItm& mi)
    {
        if (indx < _menuItems.size()) {
            _menuItems.insert(_menuItems.begin() + indx, mi);
            return true;
        }

        return false;
    }

private:
    void menu(const Menu& m, std::any& param)
    {
        const auto show = [menuCount = m._menuItems.size()](const Menu& mu) {
            std::ostringstream oss;

            oss << std::endl << mu.title() << std::endl << std::endl;

            for (size_t i = 0U; i < menuCount; ++i)
                oss << i + 1 << ")  " << mu._menuItems[i].name << std::endl;

            oss << "0)  Exit m\n\nSkriv inn menyvalg";
            return COM::getUserInput<size_t>(oss.str());
        };

        for (size_t opt = 0U; (opt = show(m)) > 0;)
            if (const auto& mi = m._menuItems[opt - 1]; std::holds_alternative<Menu::f_type>(mi.func))
                std::get<Menu::f_type>(mi.func)(param);
            else
                menu(*std::get<Menu*>(mi.func), param);
    }

    std::string _title;
    vmi _menuItems;
};





#endif //FORFEDREDIAGRAM_SIMPLEMENU_HPP
