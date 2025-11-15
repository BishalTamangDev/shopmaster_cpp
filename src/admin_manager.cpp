// include header file
#include "../include/admin_manager.h"

// check if admin has been already registered
bool AdminManager::registrationStatus()
{
    Admin admin;

    std::string line;
    std::vector<std::any> data;
    std::ifstream file(project_setup::filenames["admin"]);

    std::getline(file, line); // healine
    std::getline(file, line);
    file.close(); // close file

    if (line.length() == 0)
        return false;
    else
    {
        data = utility::getLineData(line);
        return admin.setByLineData(data); // set admin using line data
    }
}

// register
bool AdminManager::registration(Admin admin)
{
    std::ofstream file(project_setup::filenames["admin"], std::ios::app);

    file << admin.getUsername() << "," << admin.getPassword() << "," << admin.getName() << "\n";

    bool status = file.good();

    file.close();

    return status;
}

// login
bool AdminManager::login(std::string username, std::string password)
{
    std::string line;
    std::vector<std::any> data;

    std::ifstream file(project_setup::filenames["admin"]);

    std::getline(file, line); // healine
    std::getline(file, line);
    file.close(); // close file

    if (line.length() == 0)
        return false;
    else
    {
        Admin admin;
        data = utility::getLineData(line);
        admin.setByLineData(data); // set admin using line data
        return username == admin.getUsername() && password == admin.getPassword();
    }
}

// fetch admin details
bool AdminManager::fetch(Admin &admin)
{
    bool status = false;

    std::string line;
    std::ifstream file(project_setup::filenames["admin"]);

    std::getline(file, line); // heading
    std::getline(file, line); // actual data
    file.close();

    if (!line.empty())
        status = admin.setByLineData(utility::getLineData(line));

    return status;
}

// update username
bool AdminManager::update(Admin admin)
{
    std::string heading;

    std::fstream file;

    // open file and get headline
    file.open(project_setup::filenames["admin"], std::ios::in);
    std::getline(file, heading);
    file.close();

    // open file and update line
    file.open(project_setup::filenames["admin"], std::ios::out);

    file << heading << "\n"; // write heading
    file << admin.getUsername() << "," << admin.getPassword() << "," << admin.getName() << "\n";

    bool status = file.good();

    file.close();

    return status;
}