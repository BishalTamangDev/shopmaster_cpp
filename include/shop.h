#pragma once

// include header file
#include "project_setup.h"

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
    void setName(std::string);
    void setPan(std::string);
    void setContactNumber(std::string);
    void setCurrency(std::string);
    void setDistrict(std::string);
    void setMunicipality(std::string);
    void setToleVillage(std::string);
    void setWard(int);
    void setAddress(std::string, std::string, std::string, int); // set full address
    bool setByLineData(std::vector<std::any>);

    // getters
    std::string getName() const;
    std::string getPan() const;
    std::string getContactNumber() const;
    std::string getAddress() const; // get full address
    std::string getCurrency() const;
    std::string getDistrict() const;
    std::string getMunicipality() const;
    std::string getToleVillage() const;
    int getWard() const;
};