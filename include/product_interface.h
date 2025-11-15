#pragma once

// include product manager
#include "product_manager.h"

namespace product_interface
{
    void menu(); // menu

    void add();     // add new product
    void update();  // update
    void restock(); // restock
    void remove();  // remove

    void searchMenu();   // search menu
    void searchById();   // search by id
    void searchByName(); // search by name

    void viewMenu();               // view menu
    void viewAllProducts();        // view all products
    void viewAvailableProducts();  // view available products
    void viewOutOfStockProducts(); // view out of stock products
    void viewRemovedProducts(); // view removed products
};