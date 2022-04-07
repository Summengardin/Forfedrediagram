#include "Menu.hpp"


Menu::Menu(std::string title, std::vector<MenuItem> menuItems):
    _title(std::move(title)),
    _menuItems(std::move(menuItems))
    {}


auto Menu::getTitle() const noexcept
{
    return _title;
}

void Menu::setTitle(const std::string& t)
{
    _title = t;
}

void Menu::show()
{
    show(*this);
}

[[nodiscard]] bool Menu::empty() const
{
    return !_menuItems.empty();
}

[[nodiscard]] size_t Menu::size() const
{
    return _menuItems.size();
}

bool Menu::remove(size_t index)
{
    if (index < _menuItems.size()) {
        _menuItems.erase(_menuItems.begin() + index);
        return true;
    }

    return false;
}

bool Menu::append(const MenuItem& menuItem)
{
    _menuItems.emplace_back(menuItem);
    return true;
}

bool Menu::insert(size_t index, const MenuItem& menuItem)
{
    if (index < _menuItems.size()) {
        _menuItems.insert(_menuItems.begin() + index, menuItem);
        return true;
    }

    return false;
}

void Menu::show(const Menu &m)
{
    const auto menuChoice = [menuCount = m._menuItems.size()](const Menu& menu) {
        std::ostringstream oSStream;

        oSStream << "\n-----------------------------------" << std::endl;
        oSStream << std::endl << menu.getTitle() << std::endl << std::endl;

        for (size_t i = 0U; i < menuCount; ++i)
            oSStream << i + 1 << ")  " << menu._menuItems[i].name << std::endl;

        oSStream << "0)  Tilbake/Avslutt\n\nSkriv inn valg:";

        auto returnValue = COM::getNum<size_t>(oSStream.str());
        while (returnValue >= menuCount)
        {
            returnValue = COM::getNum<size_t>("Å nei du, det valget fikk du ikke.\nPrøv igjen, skriv inn menyvalg:");
        }
        return returnValue;
    };

    for (size_t opt = 0U; (opt = menuChoice(m)) > 0;)
        if (const auto& menuItem = m._menuItems[opt - 1]; std::holds_alternative<std::function<void()>>(menuItem.func))
            std::get<std::function<void()>>(menuItem.func)();
        else {
            std::cout << "Going to another menu" << std::endl;
            show(*std::get<Menu *>(menuItem.func));
        }
}

