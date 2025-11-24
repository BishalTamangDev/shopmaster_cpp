// include header file
#include "../include/shop_manager.h"

// check registration status
bool ShopManager::registrationStatus()
{
    std::ifstream fin(project_setup::filenames["shop"]);

    if (!fin)
    {
        return false;
    }

    Shop shop;

    std::string line;

    std::getline(fin, line); // heading
    std::getline(fin, line); // shop data

    if (line.empty())
    {
        return false;
    }
    else
    {
        return shop.setByLineData(utility::getLineData(line));
    }
}

// register shop
bool ShopManager::registration(Shop shop)
{
    std::ofstream file(project_setup::filenames["shop"], std::ios::app);

    file << shop.getName() << "," << shop.getPan() << "," << shop.getContactNumber() << "," << shop.getCurrency() << "," << shop.getDistrict() << "," << shop.getMunicipality() << "," << shop.getToleVillage() << "," << shop.getWard() << "\n";

    bool status = file.good();

    file.close();

    return status;
}

// fetch shop details
bool ShopManager::fetch(Shop &shop)
{
    std::ifstream fin(project_setup::filenames["shop"]);

    if (!fin)
    {
        return false;
    }

    std::string line;
    std::getline(fin, line); // heading
    std::getline(fin, line); // shop details

    if (!fin)
    {
        return false;
    }

    return shop.setByLineData(utility::getLineData(line));
}

// update shop details
bool ShopManager::update(Shop shop)
{
    std::fstream file;

    file.open(project_setup::filenames["shop"], std::ios::in);

    if (!file)
    {
        return false;
    }

    std::string headline;
    std::getline(file, headline); // get headline
    file.close();

    // write new data
    file.open(project_setup::filenames["shop"], std::ios::out);
    file << headline << "\n";
    file << shop.getName() << "," << shop.getPan() << "," << shop.getContactNumber() << "," << shop.getCurrency() << "," << shop.getDistrict() << "," << shop.getMunicipality() << "," << shop.getToleVillage() << "," << shop.getWard() << "\n";

    bool status = file.good();

    file.close();

    return status;
}

// get currency
std::string ShopManager::getCurrency()
{
    Shop shop;
    ShopManager shopManager;

    return shopManager.fetch(shop) ? shop.getCurrency() + ". " : "";
}