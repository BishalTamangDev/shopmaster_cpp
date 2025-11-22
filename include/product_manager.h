#pragma once

// include header file
#include "product.h"

class ProductManager
{
public:
    bool add(Product);                              // add new product
    bool fetch(int, Product &);                     // fetch product
    bool update(int, Product);                      // update product details
    bool remove(int);                               // remove product
    bool restock(int, int);                         // restock
    bool searchById(int, Product &);                // search by id
    std::vector<Product> searchByName(std::string); // search by name
    bool isValidProductName(std::string);           // check if the product name is already taken
    int getValidId();                               // get valid id
    bool sellProduct(std::vector<Product>);         // sell product

    static std::vector<Product> fetchAllProducts();                    // fetch all products
    static std::vector<Product> fetchProductsByStatus(PRODUCT_STATUS); // fetch products by status
    static std::vector<Product> fetchSoldProductsBySalesId(int);       // fetch sold products by sales id
    static std::vector<Product> fetchAllSoldProducts();                // fetch all sold products
};
