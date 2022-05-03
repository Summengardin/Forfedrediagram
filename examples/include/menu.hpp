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

#include "helpers.hpp"

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

    Menu(std::string title, std::vector<MenuItem> menuItems, bool loop = true)
        : _title(std::move(title)), _menuItems(std::move(menuItems)), _loop(loop)
    {
    }

    [[nodiscard]] auto getTitle() const noexcept { return _title; }

    [[nodiscard]] bool isEmpty() const { return _menuItems.empty(); }

    [[nodiscard]] size_t size() const { return _menuItems.size(); }

    void setTitle(const std::string &t) { _title = t; }

    void setLoop(bool loop) { _loop = loop; }

    void show()
    {
        size_t userChoice;
        do
        {
            writeOut();
            userChoice = menuChoice();
            if (userChoice > 0)
                execute(userChoice);
        } while (userChoice > 0 && _loop);
    }

    bool remove(size_t index)
    {
        if (index < _menuItems.size())
        {
            _menuItems.erase(_menuItems.begin() + index);
            return true;
        }

        return false;
    }

    bool append(const MenuItem &menuItem)
    {
        _menuItems.emplace_back(menuItem);
        return true;
    }

    bool insert(size_t index, const MenuItem &menuItem)
    {
        if (index < _menuItems.size())
        {
            _menuItems.insert(_menuItems.begin() + index, menuItem);
            return true;
        }

        return false;
    }

  private:
    size_t menuChoice()
    {
        auto userChoice = COM::getNum<size_t>("");
        while (userChoice > this->_menuItems.size())
        {
            userChoice = COM::getNum<size_t>("You didn't get that option did you?\nTry again: ");
        }
        return userChoice;
    }

    void writeOut()
    {
        std::ostringstream ssMenu;

        ssMenu << "\n-----------------------------------\n";
        ssMenu << "\n" << this->getTitle() << "\n" << std::endl;

        for (size_t i = 0U; i < this->_menuItems.size(); ++i)
            ssMenu << i + 1 << ")  " << this->_menuItems[i].name << "\n";

        ssMenu << "0)  Back/Exit\n\nChoose option:";

        std::cout << ssMenu.str();
    }

    void execute(size_t menuChoice)
    {
        // Sjekker om meny-elementet inneholder en funksjon eller en ny meny.

        if (const auto &menuItem = this->_menuItems[menuChoice - 1];
            std::holds_alternative<std::function<void()>>(menuItem.action))
            std::get<std::function<void()>>(menuItem.action)();
        else
        {
            std::get<Menu *>(menuItem.action)->show();
        }
    }

    std::string _title;
    std::vector<MenuItem> _menuItems;
    bool _loop{true};
};

// FORFEDREDIAGRAM_MENU_HPP
