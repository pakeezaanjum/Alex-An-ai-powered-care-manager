#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <string>
#define HASH_SIZE 1000 // Reduce size for memory efficiency
using namespace std;

// Task structure (Updated)
struct Task {
    string date;
    string time;
    string description;
    string category;  // Added category for task classification (e.g., hydration, workout)
    string status;    // Track task status (e.g., Pending, Completed)
    
    Task(string d, string t, string desc, string cat = "General") 
        : date(d), time(t), description(desc), category(cat), status("Pending") {}
    
    void setStatus(string newStatus) {
        status = newStatus;
    }
};

// User class (Updated)
class User {
private:
    string name;
    string cnic;
    string workplace;
    string job;

public:
    queue<Task*> tasks; // Dynamic storage for tasks

    User(string n, string c, string wp, string j) : name(n), cnic(c), workplace(wp), job(j) {}

    void addTask(string date, string time, string description, string category = "General") {
        tasks.push(new Task(date, time, description, category));
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
            cout << "Task: " << task->description << ", Date: " << task->date << ", Time: " << task->time
                 << ", Category: " << task->category << ", Status: " << task->status << endl;
            tempQueue.pop();
        }
    }

    Task* getNextTask() {
        if (!tasks.empty()) {
            Task* nextTask = tasks.front();
            tasks.pop();
            return nextTask;
        }
        return nullptr;
    }
};

// Simple HashMap to store completed tasks
class HashMap {
private:
    struct HashNode {
        string taskDescription;
        bool isCompleted;
        string date;
        string time;

        HashNode(string desc, bool status, string d, string t) 
            : taskDescription(desc), isCompleted(status), date(d), time(t) {}
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
    void addRecord(string taskDescription, bool status, string date, string time) {
        int index = hashFunction(taskDescription);
        map[index].push_back(new HashNode(taskDescription, status, date, time));
        cout << "Alex: Task recorded in HashMap: " << taskDescription << " (Completed: " << (status ? "Yes" : "No") 
             << ") on " << date << " at " << time << endl;
    }

    void displayRecords() {
        cout << "Alex: Here is the list of your completed tasks:" << endl;
        for (int i = 0; i < HASH_SIZE; i++) {
            if (!map[i].empty()) {
                for (HashNode* node : map[i]) {
                    cout << "Task: " << node->taskDescription << ", Completed: " << (node->isCompleted ? "Yes" : "No")
                         << ", Date
