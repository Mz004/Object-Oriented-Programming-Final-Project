/******************************************************************************
                         Milestone - #56
Full Name   : Manav Alpeshbhai Zadafiya
Student ID# : 144095221
Email       : mazadafiya@myseneca.ca
Section     : ZCC
Date        : 2023-12-07
Authenticity Declaration:
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
******************************************************************************/
#pragma once
#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds
{
    class Menu {
        char* m_Content = nullptr; //dynamic attribute
        unsigned int m_numOpt;
    public:
        Menu();
        Menu(const char* content); //parameterized constructor to initialize c-type string
        ~Menu(); // destrucotr to prevent memory leaks 

        // To avoid copy of menu object to another 
        Menu(const Menu&) = delete;
        Menu& operator=(const Menu&) = delete;

        // This function returns an unsigned integer and will not change the state of the Menu object.
        unsigned int run();
    };
}

#endif // !SDDS_MENU_H