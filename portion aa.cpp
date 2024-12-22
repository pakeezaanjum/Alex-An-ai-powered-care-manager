//if you were not smart enough God would never had you put in this place
#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <string>
#define HASH_SIZE 1000 // Reduce size for memory efficiency
using namespace std;

// Task structure
struct Task {
    string date;
    string time;
    string description;
    Task(string d, string t, string desc) : date(d), time(t), description(desc) {}
};

// User class
class User {
private:
    string name;
    string cnic;
    string workplace;
    string job;

public:
    queue<Task*> tasks; // Dynamic storage for tasks

    User(string n, string c, string wp, string j) : name(n), cnic(c), workplace(wp), job(j) {}

    void addTask(string date, string time, string description) {
        tasks.push(new Task(date, time, description));
        cout << "Alex: Task added: " << description << " on " << date << " at " << time << endl;
    }

    void displayUser() {
        cout << "Alex: Here is the user's information:" << endl;
        cout << "Name: " << name << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Workplace: " << workplace << endl;
        cout << "Job: " << job << endl;
    }

    void displayTasks() {
        if (tasks.empty()) {
            cout << "Alex: You have no pending tasks today." << endl;
            return;
        }
        cout << "Alex: Here are your tasks for today:" << endl;
        queue<Task*> tempQueue = tasks;
        while (!tempQueue.empty()) {
            Task* task = tempQueue.front();
            cout << "Task: " << task->description << ", Date: " << task->date << ", Time: " << task->time << endl;
            tempQueue.pop();
        }
    }
};

// Simple HashMap to store completed tasks
class HashMap {
private:
    struct HashNode {
        string taskDescription;
        bool isCompleted;

        HashNode(string desc, bool status) : taskDescription(desc), isCompleted(status) {}
    };

    vector<HashNode*> map[HASH_SIZE];

    int hashFunction(string key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % HASH_SIZE;
        }
        return hash;
    }

public:
    void addRecord(string taskDescription, bool status) {
        int index = hashFunction(taskDescription);
        map[index].push_back(new HashNode(taskDescription, status));
        cout << "Alex: Task recorded in HashMap: " << taskDescription << " (Completed: " << (status ? "Yes" : "No") << ")" << endl;
    }

    void displayRecords() {
        cout << "Alex: Here is the list of your completed tasks:" << endl;
        for (int i = 0; i < HASH_SIZE; i++) {
            if (!map[i].empty()) {
                for (HashNode* node : map[i]) {
                    cout << "Task: " << node->taskDescription << ", Completed: " << (node->isCompleted ? "Yes" : "No") << endl;
                }
            }
        }
    }
};

// Function to get the current date and time
void displayCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    cout << "Alex: Today's date is: " << 1900 + ltm->tm_year << "-"
         << 1 + ltm->tm_mon << "-" << ltm->tm_mday << endl;
    cout << "Alex: The current time is: " << 1 + ltm->tm_hour << ":"
         << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec << endl;
}

// Main Function
int main() {
    // Display current date and time
    displayCurrentDateTime();

    // Create a user
    User user("Alice", "12345-6789012-3", "TechCorp", "Software Engineer");

    // Add tasks to the user's queue
    user.addTask("2024-12-22", "10:00 AM", "Meeting with Bob");
    user.addTask("2024-12-22", "02:00 PM", "Doctor's appointment");

    // Display user info and tasks
    user.displayUser();
    user.displayTasks();

    // HashMap to store completed tasks
    HashMap completedTasks;

    // Simulate task completion
    while (!user.tasks.empty()) {
        Task* currentTask = user.tasks.front();
        user.tasks.pop();

        // Robot asks if the task is completed
        cout << "Alex: Did you complete the task: " << currentTask->description
             << " scheduled for " << currentTask->date << " at " << currentTask->time << "? (yes/no): ";
        string response;
        cin >> response;

        // Update task status based on user input
        bool isCompleted = (response == "yes");
        completedTasks.addRecord(currentTask->description, isCompleted);

        delete currentTask; // Free dynamically allocated memory
    }

    // Display completed tasks
    cout << "\nAlex: Here is the record of your completed tasks:\n";
    completedTasks.displayRecords();

    return 0;
}

