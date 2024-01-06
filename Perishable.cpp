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
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "Utils.h"
#include "Perishable.h"
#include "Item.h"
#include "Date.h"

using namespace std;

namespace sdds
{
	Perishable::Perishable()
	{
		expDate.formatted(true);
		handling = nullptr;
	}

	Perishable::Perishable(const Perishable& p) : Item(p)
	{
		handling = nullptr;
		expDate = p.expDate;
		if (p.handling != nullptr) {
			handling = new char[strlen(p.handling) + 1];
			strcpy(handling, p.handling);
		}
		else {
			handling = nullptr;
		}
	}
	Perishable& Perishable::operator=(const Perishable& p)
	{
		Item::operator=(p);
		if (this != &p) {
			expDate = p.expDate;
			delete[] handling;

			if (p.handling != nullptr) {
				handling = new char[strlen(p.handling) + 1];
				strcpy(handling, p.handling);
			}
			else {
				handling = nullptr;
			}
		}
		return *this;
	}
	Perishable::~Perishable()
	{
		delete[] handling;
	}

	const Date& Perishable::expiry() const
	{
		return expDate;
	}

	Perishable::operator bool() const
	{
		bool check = false;
		if ((i_sku >= 10000 && i_sku <= 39999) && i_state)
		{
			check = true;
		}
		return check;
	}

	int Perishable::readSku(std::istream& istr)
	{
		int sku;
		sku = ut.getint(10000, 39999, "SKU: ");
		i_sku = sku;
		return sku;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const
	{
		Date d = expDate;
		d.formatted(false);
		if (i_state)
		{
			//Calling Item class save function
			Item::save(ofstr);
			ofstr << "\t";
			if (handling != nullptr && strlen(handling) > 0)
			{
				ofstr << handling;
			}
			ofstr << "\t";
			d.write(ofstr);
		}
		return ofstr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr)
	{
		string desc;
		Item::load(ifstr);
		getline(ifstr, desc, '\t');
		ut.alocpy(handling, desc.c_str());
		ifstr >> expDate;
		ifstr.ignore(1000, '\n');

		if (ifstr.bad()) {
			i_state = "Input file stream read (perishable) failed!";
		}
		return ifstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr) const
	{
		if (!i_state) {
			ostr << i_state;
		}
		else {
			if (Item_linear) {
				Item::display(ostr);
				if (handling && strlen(handling) > 0) {
					ostr << "*";
				}
				else {
					ostr << " ";
				}
				ostr << expDate;
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: ";
				ostr << expDate << endl;
				if (handling && strlen(handling) > 0) {
					ostr << "Handling Instructions: " << handling << std::endl;
				}
			}
		}
		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr)
	{
		Item::read(istr);
		char desc[1000 + 1];

		delete[] handling;
		handling = nullptr;

		cout << "Expiry date (YYMMDD): ";
		expDate.read(istr);
		istr.ignore(2000, '\n');
		cout << "Handling Instructions, ENTER to skip: ";
		if (istr.peek() != '\n') {
			istr.getline(desc, 1000 + 1);
			handling = new char[strlen(desc) + 1];
			strcpy(handling, desc);
		}
		if (istr.fail()) {
			i_state = "Perishable console date entry failed!";
		}
		return istr;
	}
}