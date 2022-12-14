// Name: HASHMEET SINGH SAINI
// Seneca Student ID: 153070214
// Seneca email: hsaini28@myseneca.ca
// Date of completion: 14th November 2022
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
		const auto delimPos = str.find(getDelimiter(), next_pos);
		auto token = str.substr(next_pos, delimPos - next_pos);
		more = (delimPos != std::string::npos) && (token.length() != 0);
		if (delimPos == next_pos)
		{
			std::string err = "ERROR - no token between 2 delimiters";
			throw err;
		}

		if (token.length() > getFieldWidth())
		{
			setFieldWidth(token.length());
		}
		next_pos = delimPos + 1u;
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