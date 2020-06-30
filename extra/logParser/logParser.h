#pragma once
#include <string>
#include <vector>
#include <ctime>

class LogParser
{
public:
    enum class Sort
    { 
		Date, Type
    };

	LogParser() = default; 
	void addParsedLogPriority(std::string priority);

	void setInputFilePath(std::string path); 
	void setOutputFilePath(std::string path); 

	void setStartDate(std::string date); 
	void setEndDate(std::string date);

	void setSortTechnique(Sort sort);

	void exec();

private: 
	std::vector<std::string> m_parsedPriorities; 
	std::string m_input; 
	std::string m_output; 

	std::time_t m_startDate; 
	std::time_t m_endDate; 

	Sort m_sort {Sort::Date};
};