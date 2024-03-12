#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

std::ofstream O_tasksFile;
std::ifstream I_tasksFile;
std::vector<std::string> Tasks = {};
int tasksDay = 0;

// Getting tasks from user
void getTasksFromUser(int today)
{
    static int printingDate = 0;
    // Getting Tasks and putting them in the Tasks vector
    std::string userTask{};
    while (true)
    {
        std::cout << "Enter a task (or stop to stop) : ";
        std::cin >> userTask;
        if (userTask == "stop")
            break;
        if (printingDate == 0)
        {
            O_tasksFile << today << '\n';
            printingDate++;
        }
        Tasks.push_back(userTask);
    }
}

void clearTasks()
{
    // If the user presses y the entire file's contents get erased
    char clearData{};
    std::cout << "Clear the previous tasks (y or n)? ";
    std::cin >> clearData;

    switch (clearData)
        {
            case 'y':
                O_tasksFile.open("Tasks.txt", std::ofstream::out | std::ofstream::trunc);
                break;
            case 'n':
                break;
            case 'Y':
                O_tasksFile.open("Tasks.txt", std::ofstream::out | std::ofstream::trunc);
                break;
            default:
                std::cout << "Enter one of y or n next time." << '\n';
                break;
        }
}

// Getting tasks from file
void getTasksFromFile(int today)
{
    I_tasksFile.open("Tasks.txt");
    // Go to where today's day is
    int buffer;
    while (buffer != today)
    {
        I_tasksFile >> buffer;
        if (tasksDay == 0)
            break;
    }
    std::cout << buffer;

    // Start reading tasks until we get nothing

    // Find a way to mark tasks as completed
}

int main()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);  // Get today's date
    int today = now->tm_mday;


    // Get Items for TO - DO
    clearTasks();

    O_tasksFile.open("Tasks.txt", std::fstream::app);


    I_tasksFile.open("Tasks.txt");
    // Put the Tasks vector in a file
    if (O_tasksFile.is_open())
    {
        if (I_tasksFile.is_open())
        {
            // Get the day last tasks were written on
            while (tasksDay != today)
            {
                I_tasksFile >> tasksDay;
                if (tasksDay == 0)
                    break;
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
            Tasks.clear();

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
