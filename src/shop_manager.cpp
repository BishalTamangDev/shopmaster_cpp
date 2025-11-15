// include header file
#include "../include/shop_manager.h"

// check registration status
bool ShopManager::registrationStatus()
{
    Shop shop;
    
    std::string line;
    std::vector<std::any> data;
    std::ifstream file(project_setup::filenames["shop"]);

    std::getline(file, line); // healine
    std::getline(file, line); // shop data
    file.close();

    if(line.empty())
        return false;
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
    std::string line;

    std::ifstream file(project_setup::filenames["shop"]);

    std::getline(file, line); // heading
    std::getline(file, line); // shop details

    if (!file.good())
    {
        file.close();
        return false;
    }

    std::vector<std::any> data = utility::getLineData(line);

    return shop.setByLineData(data);
}

// update shop details
bool ShopManager::update(Shop shop)
{
    std::fstream file;
    std::string headline;

    // open shop file and get headline
    file.open(project_setup::filenames["shop"], std::ios::in);
    std::getline(file, headline); // get headline
    file.close();

    // write new data
    file.open(project_setup::filenames["shop"], std::ios::out);
    file << headline << "\n";
    file << shop.getName() << "," << shop.getPan() << "," << shop.getAddress() << "," << shop.getCurrency() << "," << shop.getDistrict() << "," << shop.getMunicipality() << "," << shop.getToleVillage() << "," << shop.getWard() << "\n";

    bool status = file.good();

    file.close();

    return status;
}