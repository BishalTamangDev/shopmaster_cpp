#pragma once

// include header file
#include "admin_manager.h"

namespace admin_interface
{
    void profileMenu();         // profile menu
    bool registration();        // admin registration
    bool login();               // admin login
    void updateName(Admin);     // update admin name
    void updateUsername(Admin); // update username
    void updatePassword(Admin); // update password
};