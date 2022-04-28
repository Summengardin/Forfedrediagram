// --------------------------------------------------------------
//
//  Menu class
//  Inspired by "Menu Class - Example of Modern C++ STL features"
//  https://www.cppstories.com/2018/07/menu-cpp17-example/
//
// --------------------------------------------------------------

#pragma once//FORFEDREDIAGRAM_MENU_HPP


#include <cctype>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "commonFunctions.hpp"


class Menu
{
private:
    struct MenuItem {
        std::string name;
        std::variant<std::function<void()>, Menu *> func;
    };

public:
    Menu() = default;
    Menu(std::string, std::vector<MenuItem>);

    [[nodiscard]] auto getTitle() const noexcept;

    void setTitle(const std::string &);

    void run(bool autoExit = false);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    bool remove(size_t index);

    bool append(const MenuItem &menuItem);

    bool insert(size_t index, const MenuItem &menuItem);

private:
    size_t menuChoice();

    void show();

    void execute(size_t menuChoice, bool autoExit = false);

    std::string _title;
    std::vector<MenuItem> _menuItems;

};


//FORFEDREDIAGRAM_MENU_HPP
