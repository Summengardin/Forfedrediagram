// --------------------------------------------------------------
//
//  Menu class
//  Inspired by "Menu Class - Example of Modern C++ STL features"
//  https://www.cppstories.com/2018/07/menu-cpp17-example/
//
// --------------------------------------------------------------

#pragma once //FORFEDREDIAGRAM_MENU_HPP


#include <iostream>
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
    struct MenuItem{
        std::string name;
        std::variant<std::function<void()>, Menu*> func;
    };

public:
    Menu() = default;
    Menu(std::string, std::vector<MenuItem>);

    [[nodiscard]] auto getTitle() const noexcept;

    void setTitle(const std::string&);

    void show();

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    bool remove(size_t index);

    bool append(const MenuItem& menuItem);

    bool insert(size_t index, const MenuItem& menuItem);

private:
    void show(const Menu& m);

    std::string _title;
    std::vector<MenuItem> _menuItems;
};





//FORFEDREDIAGRAM_MENU_HPP
