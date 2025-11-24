// include header file
#include "../include/admin_manager.h"

// check if admin has been already registered
bool AdminManager::registrationStatus()
{
    std::ifstream file(project_setup::filenames["admin"]);

    if (!file)
    {
        return false;
    }

    Admin admin;

    std::string line;

    std::getline(file, line); // skip healine

    std::getline(file, line);

    if (line.length() == 0)
    {
        return false;
    }
    else
    {
        std::vector<std::any> data = utility::getLineData(line);
        return admin.setByLineData(data); // set admin using line data
    }
}

// register
bool AdminManager::registration(Admin admin)
{
    std::ofstream file(project_setup::filenames["admin"], std::ios::app);

    if (!file)
    {
        return false;
    }

    file << admin.getUsername() << "," << admin.getPassword() << "," << admin.getName() << "\n";

    bool status = file.good();

    return status;
}

// login
bool AdminManager::login(std::string username, std::string password)
{
    std::ifstream file(project_setup::filenames["admin"]);

    if (!file)
    {
        return false;
    }

    std::string line;

    std::getline(file, line); // skip healine
    std::getline(file, line);

    if (line.length() == 0)
    {
        return false;
    }
    else
    {
        Admin admin;
        std::vector<std::any> data = utility::getLineData(line);

        if (!admin.setByLineData(data)) 
        {
            return false;
        }

        return username == admin.getUsername() && password == admin.getPassword();
    }
}

// fetch admin details
bool AdminManager::fetch(Admin &admin)
{
    std::ifstream fin(project_setup::filenames["admin"]);

    if (!fin)
    {
        return false;
    }

    bool status = false;

    std::string line;

    std::getline(fin, line); // heading
    std::getline(fin, line); // actual data

    if (!line.empty())
    {
        status = admin.setByLineData(utility::getLineData(line));
    }

    return status;
}

// update username
bool AdminManager::update(Admin admin)
{
    std::fstream file;

    // open file and get headline
    file.open(project_setup::filenames["admin"], std::ios::in);

    if (!file)
    {
        return false;
    }

    std::string heading;
    std::getline(file, heading); // get heading
    file.close();

    // open file and update line
    file.open(project_setup::filenames["admin"], std::ios::out);

    file << heading << "\n"; // write heading
    file << admin.getUsername() << "," << admin.getPassword() << "," << admin.getName() << "\n";

    bool status = file.good();

    return status;
}