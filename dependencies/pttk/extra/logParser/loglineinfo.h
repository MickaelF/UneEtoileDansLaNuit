#pragma once
#include <string_view>
#include <ctime>

class LogLineInfo
{
public: 
	LogLineInfo(std::string_view line); 

	std::string_view priority() const { return m_priority; }
	std::time_t date() const; 
	std::time_t dateTime() const; 

private: 
	std::string_view m_priority; 
	std::string_view m_date; 
	std::string_view m_time; 
};