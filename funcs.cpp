#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

inline std::ofstream O_tasksFile;
inline std::ifstream I_tasksFile;
inline std::vector<std::string> Tasks;
inline int tasksDay;


// Getting Tasks and putting them in the Tasks vector and the file
void getTasksFromUser(int today)
{            
    // if tasksDay is not today then get new tasks
    if (tasksDay != today)
    {
        static int printingDate = 0;
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

    for (int i = 0, n = Tasks.size(); i < n; i++)
    {
            O_tasksFile << Tasks[i] << '\n';
    }
}

// If the user presses y the entire file's contents get erased
void clearTasks()
{
    char clearData{};
    std::cout << "Clear the previous tasks (y or n)? ";
    std::cin >> clearData;

    switch (clearData)
    {
    case 'y':
        O_tasksFile.open("Tasks.txt", std::ofstream::out | std::ofstream::trunc);
        break;
    case 'Y':
        O_tasksFile.open("Tasks.txt", std::ofstream::out | std::ofstream::trunc);
        break;
    case 'n':
        break;
    case 'N':
        break;
    default:
        std::cout << "Enter one of y or n next time." << '\n';
        break;
    }
}

// Getting tasks from file
void getTasksFromFile(int today)
{
    Tasks.clear();
    I_tasksFile.open("Tasks.txt");
    // Go to where today's day is
    int buffer{};
    while (buffer != tasksDay)
    {
        I_tasksFile >> buffer;
        I_tasksFile.clear();
        if (tasksDay == 0)
            break;
    }

    // Start reading tasks until we get nothing
    std::string bufferString{};
    while (std::getline(I_tasksFile, bufferString))
    {
        I_tasksFile >> bufferString;
        Tasks.push_back(bufferString);
    }
    
    // Remove a empty string
    if (Tasks.size() > 0) { Tasks.pop_back(); }

    // Find a way to mark tasks as completed
    std::vector<int> completedTasks{};
    std::cout << "Enter 1 if completed the task: " << '\n';
    for (int i = 0; i < Tasks.size(); i++)
    {
        int comp = 0;
        std::cout << Tasks.at(i) << " : ";
        std::cin >> comp;

        if (comp > 0) { completedTasks.push_back(i); }
    }

    std::cout << "Completed Tasks: " << '\n';
    for (int i = 0; i < completedTasks.size(); i++)
    {
        std::cout << Tasks.at(completedTasks[i]) << '\t';
    }
}

int getDate()
{
    auto time = std::chrono::system_clock::now();
    auto dp = floor<std::chrono::days>(time);
    std::chrono::year_month_day ymd{ dp };
    auto date = ymd.day();
    auto result = static_cast<unsigned>(date);
    return static_cast<int>(result);
}

int welcome()
{
    std::cout << "Task Manager V0.1" << '\n';
    std::cout << "Read Tasks (1)" << '\t' << "Enter new Tasks (2)" << std::endl;

    int choice{};
    std::cout << "Enter a number: ";
    std::cin >> choice;
    
    return choice;
}
