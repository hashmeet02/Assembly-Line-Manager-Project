// Name: HASHMEET SINGH SAINI
// Seneca Student ID: 153070214
// Seneca email: hsaini28@myseneca.ca
// Date of completion: 20th November 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS

#include "Utilities.h"

namespace sdds {
	char Utilities::m_delimiter{};

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string token{};

		size_t pos = str.find(m_delimiter, next_pos);
		if (pos == next_pos) {
			more = false;
			throw "pos = next_pos";
		}
		if (more) {
			token = str.substr(next_pos, pos - next_pos);
			//token = trim(token);
			m_widthField = std::max(token.length(), getFieldWidth());
			if (pos != std::string::npos) {
				next_pos = pos + 1;
				more = true;
			}
			else more = false;
		}

		return trim(token);
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}

	std::string ltrim(const std::string& toBeTrimmed)
	{
		size_t start = toBeTrimmed.find_first_not_of(" ");
		return (start == std::string::npos) ? "" : toBeTrimmed.substr(start);
	}

	std::string rtrim(const std::string& toBeTrimmed)
	{
		size_t end = toBeTrimmed.find_last_not_of(" ");
		return (end == std::string::npos) ? "" : toBeTrimmed.substr(0, end + 1);
	}

	std::string trim(const std::string& toBeTrimmed) {
		return rtrim(ltrim(toBeTrimmed));
	}
}