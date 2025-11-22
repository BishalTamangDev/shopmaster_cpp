// include header file
#include "../include/inventory_interface.h"

// sell
void inventory_interface::sell(int current_emp_id)
{
    int id, qty, max_qty;
    bool product_found, already_added;
    double net_amount, discount, gross_amount, tender, change;

    std::string buffer;
    const std::vector<int> spaces = {6, 25, 12, 7, 10};

    Sales sales;
    Customer customer;

    std::vector<Product> cart;
    std::vector<Product> available_products = ProductManager::fetchProductsByStatus(PRODUCT_STATUS::AVAILABLE);

    if (available_products.empty())
    {
        utility::header("SELL PRODUCT");
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "No product available!\n");
        std::cout << "\nPress any key to continue...";
        utility::pauseScreen();
        return;
    }

    utility::header("SELL PRODUCT");

    utility::showLine(spaces, {"ID", "Name", "Rate", "Qty"});

    for (Product product : available_products)
        utility::showLine(spaces, {std::to_string(product.getId()), product.getName(), utility::getFormattedDouble(product.getRate()), std::to_string(product.getQuantity())});

    while (true)
    {
        id = 0;
        qty = 0;

        product_found = false;
        already_added = false;
        net_amount = 0.0;
        discount = 0.0;
        gross_amount = 0.0;
        tender = 0.0;
        change = 0.0;

        std::cout << "\nEnter product ID to sell :: ";
        std::getline(std::cin, buffer);

        try
        {
            id = std::stoi(buffer);
        }
        catch (const std::invalid_argument &e)
        {
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nInvalid input!");
        }

        if (id != 0)
        {
            // check of the product id is valid
            for (Product product : available_products)
            {
                if (product.getId() == id)
                {
                    max_qty = product.getQuantity();
                    product_found = true;
                    break;
                }
            }

            if (!product_found)
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo product found with this ID!");
            else
            {
                // check if the product is already added
                for (Product product : cart)
                {
                    if (product.getId() == id)
                    {
                        already_added = true;
                        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nThis product is already added!");
                        break;
                    }
                }

                // check for available products
                if (!already_added)
                {
                    // get quantity from user
                    while (true)
                    {
                        std::cout << "\nEnter quantity :: ";

                        std::getline(std::cin, buffer);

                        // input validation
                        try
                        {
                            qty = std::stoi(buffer);

                            // input quantity = 0
                            if (qty <= 0)
                            {
                                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nInvalid quantity!\n");
                                continue;
                            }

                            // input quantity > available quantity
                            if (qty > max_qty)
                            {
                                std::string msg = "\nSorry, only " + std::to_string(max_qty) + " available!\n";
                                utility::showMessage(utility::MESSAGE_TYPE::INFO, msg);
                                continue;
                            }

                            break;
                        }
                        catch (const std::invalid_argument &e)
                        {
                            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nInvalid input!\n");
                            continue;
                        }
                    }

                    // quantity validation
                    for (Product product : available_products)
                    {
                        if (product.getId() == id)
                        {
                            product.setQuantity(qty);
                            cart.push_back(product);
                            std::cout << "\nProduct added!";
                            break;
                        }
                    }
                }
            }
        }

        std::cout << "\n\nDo you want to add more products [y/n]? :: ";
        std::getline(std::cin, buffer);

        if (buffer == "y" || buffer == "Y")
            continue;
        else
        {
            if (cart.empty())
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo product added!");
                std::cout << "\n\nPress any key to continue...";
                utility::pauseScreen();
                break;
            }

            // show cart
            utility::header("SELL PRODUCT");

            std::cout << "CART DETAILS\n\n";

            utility::showLine(spaces, {"ID", "Name", "Rate", "Qty", "Total"});

            for (Product product : cart)
            {
                double total = product.getRate() * product.getQuantity();
                net_amount += total;
                utility::showLine(spaces, {std::to_string(product.getId()), product.getName(), utility::getFormattedDouble(product.getRate()), std::to_string(product.getQuantity()), utility::getFormattedDouble(total)});
            }
        }

        std::cout << "\nNet amount    :: " << net_amount;

        while (true)
        {
            std::cout << "\n\nDiscount (%)  :: ";
            std::getline(std::cin, buffer);

            if (buffer.empty())
            {
                discount = 0.0;
                break;
            }
            else
            {
                try
                {
                    discount = std::stod(buffer);

                    if (discount < 0 || discount > 100)
                    {
                        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nInvalid input!");
                        continue;
                    }

                    break;
                }
                catch (const std::invalid_argument &e)
                {
                    utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nInvalid input!");
                }
            }
        }

        gross_amount = net_amount - (discount / 100) * net_amount;

        // ask for proceeding to checkout
        std::cout << "\nProceed to checkout [y/n]? :: ";
        std::getline(std::cin, buffer);

        if (buffer != "y" && buffer != "Y")
        {
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nCheckout cancelled!");
            std::cout << "\n\nPress any key to continue...";
            utility::pauseScreen();
            break;
        }

        // tender
        while (true)
        {
            std::cout << "\nGross amount  :: " << gross_amount << "\n";
            std::cout << "\nTender amount :: ";
            std::getline(std::cin, buffer);

            try
            {
                tender = std::stod(buffer);

                if (tender < gross_amount || tender <= 0)
                {
                    utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nInsufficient amount!\n");
                    continue;
                }

                change = tender - gross_amount;
                break;
            }
            catch (const std::invalid_argument &e)
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nInvalid amount!\n");
            }
        }

        int sales_id = SalesManager::generateId(); // get sales id

        // set sales id to all products
        for (Product &product : cart)
            product.setSalesId(sales_id);

        // get customer details
        // name
        std::cout << "\nCustomer name :: ";
        std::getline(std::cin, buffer);

        // set customer details
        buffer.empty() ? customer.setName("Unknown") : customer.setName(buffer);
        customer.setSalesId(sales_id); // set sales id to customer

        // set sales details
        sales.setSalesId(sales_id);
        sales.setEmployeeId(current_emp_id);
        sales.setNetAmount(net_amount);
        sales.setDiscount(discount);
        sales.setGrossAmount(gross_amount);
        sales.setChange(change);
        sales.setTender(tender);
        sales.setDate(utility::getCurrentDateTime());

        saveInvoice(sales, cart, customer); // save sales
        showInvoice(sales, cart, customer); // show invoide

        break;
    }
}

// show invoice
void inventory_interface::showInvoice(Sales sales, std::vector<Product> cart, Customer customer)
{
    const std::vector<int> spaces = {6, 25, 12, 7, 10};

    utility::header("INVOICE");

    // show shop details
    Shop shop;
    ShopManager shopManager;
    bool response = shopManager.fetch(shop);

    if (!response)
    {
        utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "Shop details not found!");
        std::cout << "\nPress any key to continue...";
        utility::pauseScreen();
        return;
    }

    std::cout << shop.getName() << "\n";
    std::cout << shop.getAddress() << "\n";
    std::cout << "Contact No. " << shop.getContactNumber() << "\n";
    std::cout << "PAN " << shop.getPan() << "\n\n";

    // show customer details
    std::cout << "Customer name :: " << customer.getName() << "\n\n";

    utility::showLine(spaces, {"ID", "Name", "Rate", "Qty", "Total"});

    for (Product product : cart)
    {
        double total = product.getRate() * product.getQuantity();
        utility::showLine(spaces, {std::to_string(product.getId()), product.getName(), utility::getFormattedDouble(product.getRate()), std::to_string(product.getQuantity()), utility::getFormattedDouble(total)});
    }

    std::cout << "\nNet amount        :: " << sales.getNetAmount() << "\n";
    std::cout << "Discount          :: " << sales.getDiscount() << "%\n";
    std::cout << "Gross amount      :: " << sales.getGrossAmount() << "\n";
    std::cout << "Tender            :: " << sales.getTender() << "\n";
    std::cout << "Change            :: " << sales.getChange() << "\n";

    std::cout << "\nPress any key to continue...";

    utility::pauseScreen();
}

// save invoice
bool inventory_interface::saveInvoice(Sales sales, std::vector<Product> cart, Customer customer)
{
    // customer
    CustomerManager customerManager;
    bool customer_response = customerManager.add(customer);

    // sales
    SalesManager salesManager;
    bool sales_response = salesManager.add(sales);

    // sold products
    ProductManager productManager;
    bool sold_product_response = productManager.sellProduct(cart);

    return customer_response && sales_response && sold_product_response;
}