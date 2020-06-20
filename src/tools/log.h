#pragma once
#include <sstream>
#include <mutex>
//#include <source_location> As soon as it is available, use this instead of defined macros
// TODO(mfle) At each << call, remove previous endline operator and add another one at the end of the new message

class Log
{
public: 
	enum class Priority {Debug, Info, Warning, Error, Remember};
	Log(Priority p, const char* fileName, int lineNumber);
	~Log();
	Log(Log& o) = delete; 
	Log(Log&& o) = delete; 
	Log& operator=(Log& o) = delete; 
	Log& operator=(Log&& o) = delete; 

	Log& operator<<(bool b) 
	{
		m_stream << std::boolalpha << b; 
		return *this; 
	}

	 Log& operator<< (const std::string& message)
	{
		m_stream << message;
		return *this;
	}

	 Log& operator<< (const char* message)
	 {
		 m_stream << std::string(message);
		 return *this;
	 }

	 Log& operator<< (int message)
	{
		m_stream << message;
		return *this;
	}

	 Log& operator<< (unsigned int message)
	{
		m_stream << message;
		return *this;
	}

	 Log& operator<< (float message)
	{
		m_stream << message;
		return *this;
	}

	 Log& operator<< (double message)
	{
		m_stream << message;
		return *this;
	}

	 Log& operator<< (char message)
	{
		m_stream << message;
		return *this;
	}

	 Log& operator<< (int64_t message)
	 {
		 m_stream << message;
		 return *this;
	 }

private:
	Priority m_priority = Priority::Debug;
	std::ostringstream m_stream;
	static std::mutex m_mutex; 
};
 
#define lError		Log(Log::Priority::Error, __FILE__, __LINE__)
#define lInfo		Log(Log::Priority::Info, __FILE__, __LINE__)
#define lWarning	Log(Log::Priority::Warning, __FILE__, __LINE__)
#define lDebug		Log(Log::Priority::Debug, __FILE__, __LINE__)
#define lRemember	Log(Log::Priority::Remember, __FILE__, __LINE__)