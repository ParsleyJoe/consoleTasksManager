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



    clearTasks();
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

        // if tasksDay is not today then get new tasks
        if (tasksDay != today)
        {
            getTasksFromUser(today);
            for (int i = 0, n = Tasks.size(); i < n; i++)
            {
                O_tasksFile << Tasks[i] << '\n';
            }

        }
        I_tasksFile.close();
        getTasksFromFile(today);


        // Need to close file cuz we open it to remove the contents
    }
    else
    {
        std::cout << "Tasks.txt File not Found." << '\n' << "Either make a new file near the .exe or restore the file." << '\n';
    }


    return 0;
}
