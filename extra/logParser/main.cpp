#include <iostream>

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
              << "\t--dateStart MM/DD/YYYY\n"
              << "\t\tEvery log before this date won't be displayed\n"
              << "\t--dateEnd MM/DD/YYYY\n"
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


    return 0; 
}