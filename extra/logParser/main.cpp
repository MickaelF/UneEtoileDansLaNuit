#include <iostream>
#include <string_view>
#include "logparser.h"

namespace 
{
constexpr std::string_view helpArg {"-h"};
constexpr std::string_view inputArg {"-i"};
constexpr std::string_view outputArg {"-o"};
constexpr std::string_view rememberArg {"-R"};
constexpr std::string_view errorArg {"-E"};
constexpr std::string_view warningArg {"-W"};
constexpr std::string_view fatalArg {"-F"};
constexpr std::string_view infoArg {"-I"};
constexpr std::string_view debugArg {"-D"};
constexpr std::string_view dateStartArg {"--dateStart"};
constexpr std::string_view dateEndArg {"--dateEnd"};
constexpr std::string_view sortArg {"--sort"};
constexpr std::string_view sortDateArg {"date"};
constexpr std::string_view sortTypeArg {"type"};
}

void displayHelp() 
{
    std::cout << "LogParser - Help\n"
              << "\n"
              << "Parse and create a new file with only awaited logs.\n"
              << "Call: LogParser [options]\n"
              << "Options: \n"
              << "\t-h\n"
              << "\t\tDisplay help\n"
              << "\t-i path_to_log_file\n"
              << "\t\tWhere to find the log file to parse. By default, it look for the default path where log are written.\n"
              << "\t-o path_to_output_file\n"
              << "\t\tWhere to write result file. By default, it's created in the same folder of "
                 "the parsed file.\n"
              << "\t-R\n"
              << "\t\tSelect Remember logs\n"
              << "\t-E\n"
              << "\t\tSelect error logs\n"
              << "\t-F\n"
              << "\t\tSelect fatal logs\n"
              << "\t-W\n"
              << "\t\tSelect warning logs\n"
              << "\t-I\n"
              << "\t\tSelect info logs\n"
              << "\t-D\n"
              << "\t\tSelect debug logs\n"
              << "\t--dateStart MM/DD/YY\n"
              << "\t\tEvery log before this date won't be displayed\n"
              << "\t--dateEnd MM/DD/YY\n"
              << "\t\tEvery log after this date won't be displayed\n"
              << "\t--sort [type/date]\n"
              << "\t\tSort logs by type or by date. By default, they are sorted by date\n"
              << std::endl;
    
}

int main(int argc, char *argv[])
{
    
    if (argc == 1)
    {
        displayHelp();
        return 0;
    }
    LogParser parser; 
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i] == helpArg)
            displayHelp();
        else if (argv[i] == inputArg)
            parser.setInputFilePath(argv[++i]);
        else if (argv[i] == outputArg)
            parser.setOutputFilePath(argv[++i]);
        else if (argv[i] == rememberArg)
            parser.addParsedLogPriority("Remember");
        else if (argv[i] == errorArg)
            parser.addParsedLogPriority("Error");
        else if (argv[i] == warningArg)
            parser.addParsedLogPriority("Warning");
        else if (argv[i] == fatalArg)
            parser.addParsedLogPriority("Fatal");
        else if (argv[i] == infoArg)
            parser.addParsedLogPriority("Info");
        else if (argv[i] == debugArg)
            parser.addParsedLogPriority("Debug");
        else if (argv[i] == dateStartArg)
            parser.setStartDate(argv[++i]);
        else if (argv[i] == dateEndArg)
            parser.setEndDate(argv[++i]);
        else if (argv[i] == sortArg)
        {
            i++;
            if (argv[i] == sortDateArg) parser.setSortTechnique(LogParser::Sort::Date);
            else if (argv[i] == sortDateArg) parser.setSortTechnique(LogParser::Sort::Type);
        }
    }

    return 0; 
}