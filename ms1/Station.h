// Name: HASHMEET SINGH SAINI
// Seneca Student ID: 153070214
// Seneca email: hsaini28@myseneca.ca
// Date of completion: 14th November 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

namespace sdds {
	class Station {
		int m_stationId{};
		std::string m_item{};
		std::string m_description{};
		unsigned int m_SNo{};
		unsigned int m_stock{};

		static size_t m_widthField;
		static int id_generator;
	public:
		Station(const std::string& rec);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};

}

#endif // !SDDS_STATION_H
