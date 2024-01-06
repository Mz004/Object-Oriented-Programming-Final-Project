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
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include "Menu.h"
#include "iProduct.h"

namespace sdds
{
	const int sdds_max_num_items = 100;
	class AidMan
	{
		char* filename = nullptr;
		Menu mainMenu; //object of Menu Class 
		iProduct* items[sdds_max_num_items]; //Array of Objects of iProduct Class
		int noOfItems = 0;
		unsigned int menu();

	public:
		AidMan(const char* filename = nullptr);
		~AidMan();
		AidMan(const AidMan&) = delete;
		AidMan& operator=(const AidMan) = delete;
		void run();
		void save();
		void deallocateItems();
		bool load();
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void addItem();
		void remove(int index);
		void removeItem();
		void updateItem(int index);
		void updateQuantity();
		void sort();
		void ship();
		operator bool()const { return filename && noOfItems; };
	};
}
#endif // !SDDS_AIDMAN_H