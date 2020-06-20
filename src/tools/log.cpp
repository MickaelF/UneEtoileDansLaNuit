#include "log.h"
#include <iostream>

namespace {
	const char* enumToStr(Log::Priority p)
	{
		switch (p)
		{
		case Log::Priority::Debug:
			return "Debug";
		case Log::Priority::Info:
			return "Info";
		case Log::Priority::Warning:
			return "Warning";
		case Log::Priority::Error:
			return "Error";
		case Log::Priority::Remember:
			return "Remember";
		default: return "Unknown"; 
		}
	}
}
std::mutex Log::m_mutex;

Log::Log(Priority priority, const char* fileName, int lineNumber) : m_priority(priority)
{
	m_stream << enumToStr(priority) << "-" << fileName << ":" << lineNumber << " - "; 
}

Log::~Log()
{
	std::lock_guard<std::mutex> lock{ m_mutex };
	std::cout << m_stream.str() << std::endl; 
	// TODO(mfle) Log in file
}