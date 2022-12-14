// Name: HASHMEET SINGH SAINI
// Seneca Student ID: 153070214
// Seneca email: hsaini28@myseneca.ca
// Date of completion: 14th November 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {

	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder()
	{
		m_name="";
		m_product="";
		m_cntItem=0;
		m_lstItem=nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& rec)
	{
		Utilities utils;
		bool more = true;
		size_t next_pos = 0, start=0;

		m_name = utils.extractToken(rec, next_pos, more);
		m_product = utils.extractToken(rec, next_pos, more);
		m_cntItem = 0;
		start = next_pos;

		while (more)
		{
			utils.extractToken(rec, next_pos, more);
			m_cntItem++;
		}

		m_lstItem = new Item * [m_cntItem];
		more = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item(utils.extractToken(rec, start, more));
		}

		if (utils.getFieldWidth() > m_widthField) {
			m_widthField = utils.getFieldWidth();
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& toCopy)
	{
		std::string err = "A CustomerOrder object should not allow copy operations";
		throw err;
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& toMove) noexcept
	{
		*this = std::move(toMove);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& toMove) noexcept
	{
		if (&toMove != this)
		{
			if (m_lstItem) {
				for (size_t i = 0; i < m_cntItem; i++) {
					delete m_lstItem[i];
				}
			}
			delete[] m_lstItem;

			m_name = toMove.m_name;
			m_product = toMove.m_product;
			m_cntItem = toMove.m_cntItem;
			m_lstItem = toMove.m_lstItem;

			toMove.m_lstItem = nullptr;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		if (m_lstItem) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		bool rtnFlag = true;
		for (size_t i = 0; i < m_cntItem && rtnFlag == true; i++) {
			if (!(m_lstItem[i]->m_isFilled)) rtnFlag = false;
		}
		return rtnFlag;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool rtnFlag = true;
		for (size_t i = 0; i < m_cntItem && rtnFlag == true; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (!(m_lstItem[i]->m_isFilled)) rtnFlag = false;
			}
		}
		return rtnFlag;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		std::string itemName = station.getItemName();
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (station.getQuantity() <= 0) {
					os << "Unable to fill " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else
				{
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					station.updateQuantity();
					m_lstItem[i]->m_isFilled = true;

					os.width(11);
					os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}

				return;
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (unsigned int i = 0; i < m_cntItem; i++)
		{
			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber
				<< std::setfill(' ') << "] ";
			os.setf(std::ios::left); 
			os << std::setw(m_widthField) << m_lstItem[i]->m_itemName;
			os.unsetf(std::ios::left);
			os<<" - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}