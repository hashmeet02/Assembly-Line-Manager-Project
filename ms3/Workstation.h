// Name: HASHMEET SINGH SAINI
// Seneca Student ID: 153070214
// Seneca email: hsaini28@myseneca.ca
// Date of completion: 20th November 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include <string>
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"


namespace sdds{
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation: public Station {
		std::deque <CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};
	public:
		Workstation(const std::string& str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station=nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

		Workstation(const Workstation& toCopy)=delete;
		Workstation& operator=(const Workstation& toAssign) = delete;
		Workstation(Workstation&& toMove) noexcept =delete;
		Workstation& operator=(Workstation&& toMove) noexcept = delete;
	};
}
#endif // !SDDS_WORKSTATION_H
