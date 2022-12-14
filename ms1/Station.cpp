// Name: HASHMEET SINGH SAINI
// Seneca Student ID: 153070214
// Seneca email: hsaini28@myseneca.ca
// Date of completion: 14th November 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	Station::Station(const std::string& rec)
	{
		bool more{};
		size_t next_pos = 0u;
		Utilities utils;
		id_generator++;

		m_stationId = id_generator;
		m_item = utils.extractToken(rec, next_pos, more);
		m_SNo = std::stoi(utils.extractToken(rec, next_pos, more));
		m_stock = std::stoi(utils.extractToken(rec, next_pos, more));
		m_widthField = utils.getFieldWidth();
		m_description = utils.extractToken(rec, next_pos, more);

	}

	const std::string& Station::getItemName() const
	{
		return m_item;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_SNo++;
	}

	size_t Station::getQuantity() const
	{
		return m_stock;
	}

	void Station::updateQuantity()
	{
		if (m_stock > 0) {
			m_stock--;
		}
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os.width(3);
		os.fill('0');
		os << m_stationId << " | ";

		os.setf(std::ios::left);
		os.fill(' ');
		os.width(m_widthField);
		os << getItemName() << " | ";
		os.unsetf(std::ios::left);
		
		os.fill('0');
		os.width(6);
		os << m_SNo;
		os.fill(' ');
		os<< " | ";

		if (full) {
			os.width(4);
			os << getQuantity() << " | ";
			os.setf(std::ios::left);
			os << m_description;
			os.unsetf(std::ios::left);
		}

		os << std::endl;
	}
}