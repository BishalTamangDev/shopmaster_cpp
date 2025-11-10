#include <iostream>
#include <string>
#include <vector>
#include <any>

// include user-defined files
#include "utils.h"
#include "file_setup.h"

#ifndef SHOPMASTER_SHOP_H
#define SHOPMASTER_SHOP_H

class Shop
{
private:
    std::string name;
    std::string pan;
    std::string contact_number;
    std::string currency;
    std::string district;
    std::string municipality;
    std::string tole_village;
    int ward;

public:
    // constructor
    Shop()
    {
        name = "";
        pan = "";
        contact_number = "";
        currency = "";
        district = "";
        municipality = "";
        tole_village = "";
        ward = 0;
    }

    // setters
    void setName(std::string &);
    void setPan(std::string &);
    void setContactNumber(std::string &);
    void setCurrency(std::string &);
    void setDistrict(std::string &);
    void setMunicipality(std::string &);
    void setToleVillage(std::string &);
    void setWard(int &);
    void setAddress(std::string &, std::string &, std::string &, int &); // set full address
    bool setByLineData(std::vector<std::any> &);

    // getters
    std::string getName();
    std::string getPan();
    std::string getContactNumber();
    std::string getAddress(); // get full address
    std::string getCurrency();
    std::string getDistrict();
    std::string getMunicipality();
    std::string getToleVillage();
    int getWard();

    bool isRegistered(); // check for shop registration
    bool registerShop(); // register shop
    bool fetch();        // fetch shop details
    bool update();       // update shop details
};

// setters
// setter :: name
void Shop::setName(std::string &name)
{
    utils::convertToWordCase(name);
    this->name = name;
}

bool Shop::setByLineData(std::vector<std::any> &data)
{
    bool status = false;
    try
    {
        this->name = std::any_cast<std::string>(data[0]);
        this->pan = std::any_cast<std::string>(data[1]);
        this->contact_number = std::any_cast<std::string>(data[2]);
        this->currency = std::any_cast<std::string>(data[3]);
        this->district = std::any_cast<std::string>(data[4]);
        this->municipality = std::any_cast<std::string>(data[5]);
        this->tole_village = std::any_cast<std::string>(data[6]);
        this->ward = std::stoi(std::any_cast<std::string>(data[7]));

        status = true;
    }
    catch (const char *e)
    {
#ifdef DEBUG_MODE
        std::cerr << "\n\nError: " << e << "\n";
        utils::pauseScreen();
#endif
        status = false;
    }
    return status;
}

// setter :: pan
void Shop::setPan(std::string &pan)
{
    utils::convertToWordCase(pan);
    this->pan = pan;
}

// setter :: contact number
void Shop::setContactNumber(std::string &contact_number)
{
    utils::convertToWordCase(contact_number);
    this->contact_number = contact_number;
}

// setter :: currency
void Shop::setCurrency(std::string &currency)
{
    utils::convertToUpperCase(currency);
    this->currency = currency;
}

// setter :: district
void Shop::setDistrict(std::string &district)
{
    this->district = district;
}

// setter :: municipality
void Shop::setMunicipality(std::string &municipality)
{
    this->municipality = municipality;
}

// setter :: tole village
void Shop::setToleVillage(std::string &tole_village)
{
    this->tole_village = tole_village;
}

// setter :: ward
void Shop::setWard(int &ward)
{
    this->ward = ward;
}

// setter :: address
void Shop::setAddress(std::string &district, std::string &municipality, std::string &tole_village, int &ward)
{
    utils::convertToWordCase(district);
    utils::convertToWordCase(municipality);
    utils::convertToWordCase(tole_village);

    this->district = district;
    this->municipality = municipality;
    this->tole_village = tole_village;
    this->ward = ward;
}

// getters
// getter :: name
std::string Shop::getName()
{
    return this->name;
}

// getter :: pan
std::string Shop::getPan()
{
    return this->pan;
}

// getter :: contact number
std::string Shop::getContactNumber()
{
    return this->contact_number;
}

// getter :: currency
std::string Shop::getCurrency()
{
    return this->currency;
}

// getter :: district
std::string Shop::getDistrict()
{
    return this->district;
}

// getter :: municipality
std::string Shop::getMunicipality()
{
    return this->municipality;
}

// getter :: tole/village
std::string Shop::getToleVillage()
{
    return this->tole_village;
}

// getter :: ward
int Shop::getWard()
{
    return this->ward;
}

// get address
std::string Shop::getAddress()
{
    std::string address = this->tole_village + ", " + this->municipality + " - " + std::to_string(this->ward) + ", " + this->district;
    return address;
}

// check for shop registration
bool Shop::isRegistered()
{
    std::string line;
    std::vector<std::any> data;
    std::ifstream file(app_files::filenames["shop"]);

    std::getline(file, line); // healine
    std::getline(file, line); // get shop details
    file.close();             // close file

    return line.length() != 0;
}

// register shop
bool Shop::registerShop()
{
    std::ofstream file(app_files::filenames["shop"], std::ios::app);

    file << this->name << "," << this->pan << "," << this->contact_number << "," << this->currency << "," << this->district << "," << this->municipality << "," << this->tole_village << "," << this->ward << "\n";

    file.close();

    return file.good();
}

// fetch shop details
bool Shop::fetch()
{
    std::string line;

    std::ifstream file(app_files::filenames["shop"]);

    std::getline(file, line); // heading
    std::getline(file, line); // shop details

    if (!file.good())
    {
        file.close();
        return false;
    }

    std::vector<std::any> data = utils::getLineData(line);

    return this->setByLineData(data);
}

// update shop details
bool Shop::update()
{
    std::fstream file;
    std::string headline;

    // open shop file and get headline
    file.open(app_files::filenames["shop"], std::ios::in);
    std::getline(file, headline); // get headline
    file.close();

    // write new data
    file.open(app_files::filenames["shop"], std::ios::out);
    file << headline << "\n";
    file << this->name << "," << this->pan << "," << this->contact_number << "," << this->currency << "," << this->district << "," << this->municipality << "," << this->tole_village << "," << this->ward << "\n";

    bool status = file.good();

    file.close();

    return status;
}

#endif