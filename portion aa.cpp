#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <string>
using namespace std;

// Task structure (Updated)
struct Task {
    string date;
    string time;
    string description;
    string category;  // Added category for task classification (e.g., hydration, workout, meeting, etc.)
    string status;    // Track task status (e.g., Pending, Completed)
    
    Task(string d, string t, string desc, string cat = "General") 
        : date(d), time(t), description(desc), category(cat), status("Pending") {}
    
    void setStatus(string newStatus) {
        status = newStatus;
    }
};

// TaskTreeNode for Binary Search Tree (BST)
struct TaskTreeNode {
    string description;
    int status;  // 1 for completed, 0 for not completed
    TaskTreeNode* left;
    TaskTreeNode* right;

    TaskTreeNode(string desc, int stat) : description(desc), status(stat), left(nullptr), right(nullptr) {}
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

// Function to display current date and time
void displayCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    cout << "Alex: Today's date is: " << 1900 + ltm->tm_year << "-"
         << 1 + ltm->tm_mon << "-" << ltm->tm_mday << endl;
    cout << "Alex: The current time is: " << 1 + ltm->tm_hour << ":"
         << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec << endl;
}

// Function to handle emergency circumstances (fire alarm)
void EmergencyCircumstances(bool fireDetected) {
    if (fireDetected) {
        cout << "Alex: Emergency! Fire alarm has been triggered." << endl;
        cout << "Alex: Initiating emergency protocol..." << endl;
        cout << "Alex: Calling 911... Please stay calm." << endl;
        cout << "Alex: Searching for the nearest emergency exits..." << endl;
        cout << "Alex: The nearest emergency exit is located to the left of the living room. Please proceed immediately!" << endl;
        cout << "Alex: If possible, use the emergency phone located in the hallway to confirm the situation." << endl;
        cout << "Alex: Please exit the house immediately and avoid using elevators during the emergency." << endl;
    } else {
        cout << "Alex: No fire detected. All systems are normal." << endl;
    }
}

// Function to insert tasks into the BST
TaskTreeNode* insertTask(TaskTreeNode* root, string description, int status) {
    if (root == nullptr) {
        return new TaskTreeNode(description, status);
    }

    if (description < root->description) {
        root->left = insertTask(root->left, description, status);
    } else {
        root->right = insertTask(root->right, description, status);
    }
    return root;
}

// Function to display the table of tasks (task name and status)
void displayTaskTable(TaskTreeNode* root) {
    if (root == nullptr) {
        return;
    }
    displayTaskTable(root->left);
    cout << "Task: " << root->description << ", Status: " << (root->status ? "1 (Completed)" : "0 (Not Completed)") << endl;
}

// Main Function
int main() {
    // Display current date and time
    displayCurrentDateTime();

    // Create a user
    User user("Alice", "12345-6789012-3", "TechCorp", "Software Engineer");

    // Add tasks to the user's queue (doctor appointments, meetings, etc.)
    user.addTask("2024-12-22", "10:00 AM", "Meeting with Bob");
    user.addTask("2024-12-22", "02:00 PM", "Doctor's appointment");

    // Display user info and tasks
    user.displayUser();
    user.displayTasks();

    // BST for task status
    TaskTreeNode* root = nullptr;

    // Simulate task completion
    while (!user.tasks.empty()) {
        Task* currentTask = user.getNextTask();

        // Robot asks if the task is completed
        cout << "Alex: Did you complete the task: " << currentTask->description
             << " scheduled for " << currentTask->date << " at " << currentTask->time << "? (yes/no): ";
        string response;
        cin >> response;

        // Update task status based on user input
        bool isCompleted = (response == "yes");
        currentTask->setStatus(isCompleted ? "Completed" : "No");

        // Insert task into BST
        root = insertTask(root, currentTask->description, isCompleted);

        delete currentTask; // Free dynamically allocated memory
    }

    // Display completed tasks
    cout << "\nAlex: Here is the record of your completed tasks:\n";
    displayTaskTable(root);

    // Periodic Tasks (Hydration, Workout, Sleep Schedule)
    user.addTask("2024-12-22", "08:00 AM", "Hydrate", "Health");
    user.addTask("2024-12-22", "07:00 PM", "Workout", "Health");
    user.addTask("2024-12-22", "10:00 PM", "Sleep Schedule", "Health");

    // Simulate task completion for periodic tasks
    while (!user.tasks.empty()) {
        Task* currentTask = user.getNextTask();

        // Robot asks if the task is completed
        cout << "Alex: Did you complete the task: " << currentTask->description
             << " scheduled for " << currentTask->date << " at " << currentTask->time << "? (yes/no): ";
        string response;
        cin >> response;

        // Update task status based on user input
        bool isCompleted = (response == "yes");
        currentTask->setStatus(isCompleted ? "Completed" : "No");

        // Insert task into BST
        root = insertTask(root, currentTask->description, isCompleted);

        delete currentTask; // Free dynamically allocated memory
    }

    // Display completed periodic tasks
    cout << "\nAlex: Here is the record of your completed tasks:\n";
    displayTaskTable(root);

    // Simulating fire detection
    bool fireDetected = true; // Change to `false` to simulate no fire

    // Calling the EmergencyCircumstances function
    EmergencyCircumstances(fireDetected);

    return 0;
}
