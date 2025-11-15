// include header file
#include "../include/shop.h"

// setter :: name
void Shop::setName(std::string name)
{
    utility::convertToWordCase(name);
    this->name = name;
}

// setter :: pan
void Shop::setPan(std::string pan)
{
    utility::convertToWordCase(pan);
    this->pan = pan;
}

// setter :: contact number
void Shop::setContactNumber(std::string contact_number)
{
    utility::convertToWordCase(contact_number);
    this->contact_number = contact_number;
}

// setter :: currency
void Shop::setCurrency(std::string currency)
{
    utility::convertToUpperCase(currency);
    this->currency = currency;
}

// setter :: district
void Shop::setDistrict(std::string district)
{
    utility::convertToWordCase(district);
    this->district = district;
}

// setter :: municipality
void Shop::setMunicipality(std::string municipality)
{
    utility::convertToWordCase(municipality);
    this->municipality = municipality;
}

// setter :: tole village
void Shop::setToleVillage(std::string tole_village)
{
    utility::convertToWordCase(tole_village);
    this->tole_village = tole_village;
}

// setter :: ward
void Shop::setWard(int ward)
{
    this->ward = ward;
}

// setter :: address
void Shop::setAddress(std::string district, std::string municipality, std::string tole_village, int ward)
{
    utility::convertToWordCase(district);
    utility::convertToWordCase(municipality);
    utility::convertToWordCase(tole_village);

    this->district = district;
    this->municipality = municipality;
    this->tole_village = tole_village;
    this->ward = ward;
}

bool Shop::setByLineData(std::vector<std::any> data)
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
#endif
        status = false;
    }
    return status;
}

// getters
// getter :: name
std::string Shop::getName() const
{
    return this->name;
}

// getter :: pan
std::string Shop::getPan() const
{
    return this->pan;
}

// getter :: contact number
std::string Shop::getContactNumber() const
{
    return this->contact_number;
}

// getter :: currency
std::string Shop::getCurrency() const
{
    return this->currency;
}

// getter :: district
std::string Shop::getDistrict() const
{
    return this->district;
}

// getter :: municipality
std::string Shop::getMunicipality() const
{
    return this->municipality;
}

// getter :: tole/village
std::string Shop::getToleVillage() const
{
    return this->tole_village;
}

// getter :: ward
int Shop::getWard() const
{
    return this->ward;
}

// get address
std::string Shop::getAddress() const
{
    return this->tole_village + ", " + this->municipality + " - " + std::to_string(this->ward) + ", " + this->district;
}
