// --------------------------------------------------------------
//
//  Menu class
//  Inspired by "Menu Class - Example of Modern C++ STL features"
//  https://www.cppstories.com/2018/07/menu-cpp17-example/
//
// --------------------------------------------------------------

#pragma once // FORFEDREDIAGRAM_MENU_HPP

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
    struct MenuItem
    {
        std::string name;
        std::variant<std::function<void()>, Menu *> action;
    };

  public:
    Menu() = default;

    Menu(std::string, std::vector<MenuItem>, bool loop = true);

    [[nodiscard]] auto getTitle() const noexcept;

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] size_t size() const;

    void setTitle(const std::string &);

    void setLoop(bool);

    void show();

    bool remove(size_t index);

    bool append(const MenuItem &menuItem);

    bool insert(size_t index, const MenuItem &menuItem);

  private:
    size_t menuChoice();

    void writeOut();

    void execute(size_t menuChoice);

    std::string _title;
    std::vector<MenuItem> _menuItems;
    bool _loop;
};

// FORFEDREDIAGRAM_MENU_HPP
