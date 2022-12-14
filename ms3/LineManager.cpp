// Name: HASHMEET SINGH SAINI
// Seneca Student ID: 153070214
// Seneca email: hsaini28@myseneca.ca
// Date of completion: 20th November 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <iostream>
#include <algorithm>
#include "Utilities.h"
#include "Workstation.h"
#include "LineManager.h"

namespace sdds {
	LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations)
	{
		Utilities utils;
		size_t next_pos = 0;
		bool more = true;
		std::string record{};

		std::string workstation{};
		std::string nextWorkstation{};
		std::ifstream file(filename);
		if (!file) {
			throw std::string("Couldn't open the file");
		}

		while (getline(file, record)) {
			Workstation* stationPtr1{};
			Workstation* stationPtr2{};
			std::string workstation1{};
			std::string workstation2{};
			next_pos = 0;
			more = true;

			workstation1 = utils.extractToken(record, next_pos, more);
			if (!more) {
				more = true;
				workstation2 = "";
			}
			else {
				workstation2 = utils.extractToken(record, next_pos, more);
			}
			
			stationPtr1 = *(std::find_if(stations.begin(), stations.end(), [workstation1](Workstation* workstation)
				{return workstation->getItemName() == workstation1; }
			));
			m_activeLine.push_back(stationPtr1);

			if (!workstation2.empty()) {
				stationPtr2 = *(std::find_if(stations.begin(), stations.end(), [workstation2](Workstation* workstation)
					{return workstation->getItemName() == workstation2; }
				));
			}
			stationPtr1->setNextStation(stationPtr2);
		}
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workstation1) {
			auto firstStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workstation2) {
				return workstation1 == workstation2->getNextStation();
				});
			if (firstStation == m_activeLine.end()) {
				m_firstStation = workstation1;
			}
			});
		m_cntCustomerOrder = g_pending.size();
	}
	void LineManager::reorderStations()
	{
		std::vector<Workstation*> tempVector = m_activeLine;
		m_activeLine[0] = m_firstStation;
		bool found{};
		
		for (size_t i = 0; i < m_activeLine.size() - 1; i++)
		{
			found = false;
			for (size_t j = 0; j < tempVector.size() && !found; j++)
			{
				if (m_activeLine[i]->getNextStation() && m_activeLine[i]->getNextStation()->getItemName() == tempVector[j]->getItemName())
				{
					m_activeLine[i + 1] = tempVector[j];
					found = true;
				}
			}
		}
	}
	bool LineManager::run(std::ostream& os)
	{
		static size_t counter=1;
		os << "Line Manager Iteration: " << counter++ << std::endl;
		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
		for (auto station : m_activeLine) {
			station->fill(os);
		}
		for (auto station : m_activeLine) {
			station->attemptToMoveOrder();
		}
		return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
	}
	void LineManager::display(std::ostream& os) const
	{
		for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation* workstation) {
			workstation->display(os); 
			});
	}
}