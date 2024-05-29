#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "def.h"

inline std::ofstream O_tasksFile;
inline std::ifstream I_tasksFile;
inline std::vector<std::string> Tasks = {};
inline int tasksDay;
// Getting Tasks From File is broken, Loop doesn't stop

int main()
{
    int today = getDate();  // Get today's date
    int choice = welcome();

    O_tasksFile.open("Tasks.txt", std::fstream::app);
    I_tasksFile.open("Tasks.txt");

    // Put the Tasks vector in a file
    if (O_tasksFile.is_open())
    {
        if (I_tasksFile.is_open())
        {
            // Get the day last tasks were written on
            int num = 0;
            std::string bufferStr;
            while (true)
            {
                I_tasksFile >> num;
                I_tasksFile.clear();
                if (!std::getline(I_tasksFile >> std::ws, bufferStr))
                    break;
                
                if (num > 0)
                    tasksDay = num;
            }

        }
        else
        {
            std::cout << "The Tasks file could not be opened for reading." << '\n';
        }
        
        switch (choice)
        {
        case 1:
            I_tasksFile.close();
            getTasksFromFile(today);
            break;
        case 2:
            clearTasks();
            getTasksFromUser(today);
            I_tasksFile.close();
            break;
        default:
            std::cout << "You entered something else than 1 or 2" << std::endl;
            break;
        }
    }
    else
    {
        std::cout << "Tasks.txt File not Found." << '\n' << "Either make a new file near the .exe or restore the file." << '\n';
    }

    return 0;
}
