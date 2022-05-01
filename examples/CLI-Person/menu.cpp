#include "include/menu.hpp"

Menu::Menu(std::string title, std::vector<MenuItem> menuItems, bool loop)
    : _title(std::move(title)), _menuItems(std::move(menuItems)), _loop(loop)
{
}

auto Menu::getTitle() const noexcept
{
    return _title;
}

bool Menu::isEmpty() const
{
    return _menuItems.empty();
}

size_t Menu::size() const
{
    return _menuItems.size();
}

void Menu::setTitle(const std::string &t)
{
    _title = t;
}

void Menu::setLoop(bool loop)
{
    _loop = loop;
}

void Menu::show()
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

bool Menu::remove(size_t index)
{
    if (index < _menuItems.size())
    {
        _menuItems.erase(_menuItems.begin() + index);
        return true;
    }

    return false;
}

bool Menu::append(const MenuItem &menuItem)
{
    _menuItems.emplace_back(menuItem);
    return true;
}

bool Menu::insert(size_t index, const MenuItem &menuItem)
{
    if (index < _menuItems.size())
    {
        _menuItems.insert(_menuItems.begin() + index, menuItem);
        return true;
    }

    return false;
}

size_t Menu::menuChoice()
{
    auto userChoice = COM::getNum<size_t>("");
    while (userChoice > this->_menuItems.size())
    {
        userChoice = COM::getNum<size_t>("You didn't get that option did you?\nTry again: ");
    }
    return userChoice;
}

void Menu::writeOut()
{
    std::ostringstream ssMenu;

    ssMenu << "\n-----------------------------------\n";
    ssMenu << "\n" << this->getTitle() << "\n" << std::endl;

    for (size_t i = 0U; i < this->_menuItems.size(); ++i)
        ssMenu << i + 1 << ")  " << this->_menuItems[i].name << "\n";

    ssMenu << "0)  Back/Exit\n\nChoose option:";

    std::cout << ssMenu.str();
}

void Menu::execute(size_t menuChoice)
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
