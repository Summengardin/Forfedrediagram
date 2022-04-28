#include "Menu.hpp"


Menu::Menu(std::string title, std::vector<MenuItem> menuItems) :
    _title(std::move(title)),
    _menuItems(std::move(menuItems))
{}


auto Menu::getTitle() const noexcept
{
    return _title;
}

void Menu::setTitle(const std::string &t)
{
    _title = t;
}

void Menu::run(bool autoExit)
{
    size_t choice;
    do
    {
        show();
        choice = menuChoice();
        if(choice > 0)
            execute(choice, autoExit);
    } while(choice > 0 && !autoExit);
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

void Menu::show()
{
    std::ostringstream oSStream;

    oSStream << "\n-----------------------------------" << std::endl;
    oSStream << std::endl
             << this->getTitle() << std::endl
             << std::endl;

    for (size_t i = 0U; i < this->_menuItems.size(); ++i)
        oSStream << i + 1 << ")  " << this->_menuItems[i].name << "\n";

    oSStream << "0)  Tilbake/Avslutt\n\nSkriv inn valg:";

    std::cout << oSStream.str();


}
size_t Menu::menuChoice(){
    auto returnValue = COM::getNum<size_t>("");
    while (returnValue > this->_menuItems.size())
    {
        returnValue = COM::getNum<size_t>("Å nei du, det valget fikk du ikke.\nPrøv igjen, skriv inn menyvalg:");
    }
    return returnValue;
}

void Menu::execute(size_t menuChoice, bool autoExit){

    // Sjekker om meny-elementet inneholder en funksjon eller en ny meny.

    if (const auto &menuItem = this->_menuItems[menuChoice - 1]; std::holds_alternative<std::function<void()>>(menuItem.func))
        std::get<std::function<void()>>(menuItem.func)();
    else
    {
        std::get<Menu *>(menuItem.func)->run(autoExit);
    }

}
