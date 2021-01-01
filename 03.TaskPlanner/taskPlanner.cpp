#include<bits/stdc++.h>

using namespace std;

class Task;
class User;

enum TaskType { STORY, FEATURE, BUG };
enum TaskStatus { OPEN, IN_PROGRESS, RESOLVED, DELAYED, COMPLETED };

class Sprint {
    private:
        int begin, end;
        string name;
        vector<Task> tasks;
    public:
        Sprint(int begin, int end, string name) {
            this->begin = begin;
            this->end = end;
            this->name = name;
        }
        vector<Task> getTasks();
        void addTask(Task&);
        void printDetails();
        bool operator==(Sprint sprint);
        bool eraseTask(Task& task);
};

class User {
    private:
        vector<Task> taskList;
        vector<Sprint> sprintList;
    public:
        Task createTask(TaskType);
        Task createTask(string);
        Sprint createSprint(int, int, string);
        bool addToSprint(Sprint&, Task&);
        bool removeFromSprint(Sprint&, Task&);
        void printAllTasks();
        bool changeStatus(Task&, TaskStatus);
};

class Task {
    private:
        int id;
        string subtract;    // Only a task of type story has subtract
        User user;
        TaskType taskType;
        TaskStatus taskStatus;
        int generateId();
    public:
        Task();
        int getId();
        void setSubtract(string);
        void setUser(User&);
        void setTaskType(TaskType);
        void setTaskStatus(TaskStatus);
        bool operator==(Task&);
};



/*************** Sprint class methods **********************/
vector<Task> Sprint::getTasks() {
    return tasks;
}

void Sprint::addTask(Task& task) {
    tasks.push_back(task);
}

void Sprint::printDetails() {
    cout<<"Sprint name: "<<name<<endl;
    cout<<"Sprint begins: "<<begin<<endl;
    cout<<"Sprint ends: "<<end<<endl;
}

bool Sprint::eraseTask(Task& task) {
    int i = 0;
    for(Task& tsk: tasks) {
        if(tsk == task) {
            tasks.erase(tasks.begin() + i);
            return true;
        }
        i++;
    }
    return false;
}

inline bool Sprint::operator==(Sprint sprint) {
    return (this->begin == sprint.begin) && (this->end == sprint.end) && (this->name == sprint.name);
}

/**************************************************************/

/******************** Task class methods **********************/
int Task::generateId() {
    static int id = 1;
    return id++;
}

Task::Task() {
    this->id = generateId();
    this->taskStatus = TaskStatus::OPEN;
}

int Task::getId() {
    return this->id;
}

void Task::setSubtract(string subtract) {
    this->subtract = subtract;
}

void Task::setUser(User& user) {
    this->user = user;
}

void Task::setTaskStatus(TaskStatus taskStatus) {
    this->taskStatus = taskStatus;
}

void Task::setTaskType(TaskType taskType) {
    this->taskType = taskType;
}

inline bool Task::operator==(Task& task) {
    return task.id == this->id;
}

/**************************************************************/

/******************** User class methods **********************/
Task User::createTask(TaskType taskType) {
    if(taskType == TaskType::STORY) {
        cout<<"Warning! A task of type story is being created without subtract"<<endl;
    }
    Task task;
    task.setTaskType(taskType);
    task.setUser(*this);
    taskList.push_back(task);
    return task;
}

Task User::createTask(string subtract) {
    Task task;
    task.setTaskType(TaskType::STORY);
    task.setSubtract(subtract);
    task.setUser(*this);
    taskList.push_back(task);
    return task;
}

Sprint User::createSprint(int begin, int end, string name) {
    Sprint sprint(begin, end, name);
    sprintList.push_back(sprint);
    return sprint;
}

bool User::addToSprint(Sprint& sprint, Task& task) {
    for(Sprint& spr: sprintList) {
        if(spr == sprint) {
            sprint.addTask(task);
            return true;
        }
    }
    return false;
}

bool User::removeFromSprint(Sprint& sprint, Task& task) {
    for(Sprint& spr: sprintList) {
        if(spr == sprint) {
            return sprint.eraseTask(task);
        }
    }
    return false;
}

void User::printAllTasks() {
    for(Task& tsk: taskList) {
        cout<<tsk.getId()<<" ";
    }
    cout<<endl;
}

bool User::changeStatus(Task& task, TaskStatus taskStatus) {
    for(Task& tsk: taskList) {
        if(tsk == task) {
            task.setTaskStatus(taskStatus);
            return true;
        }
    }
    return false;
}
/**************************************************************/

int main() {
    User user1, user2;

    Task task1 = user1.createTask(TaskType::FEATURE);
    Task task11 = user1.createTask(TaskType::BUG);

    Task task2 = user2.createTask(TaskType::BUG);
    Task task22 = user2.createTask("This is a subtract");

    Sprint sprint1 = user1.createSprint(22, 33, "Sprint1");
    Sprint sprint2 = user2.createSprint(44, 55, "Sprint2");

    user1.changeStatus(task11, TaskStatus::IN_PROGRESS);

    cout << user1.addToSprint(sprint1, task1) << "\n"; //1
	cout << user1.addToSprint(sprint1, task11) << "\n"; //1
	cout << user1.addToSprint(sprint2, task1) << "\n"; //0
	cout << user1.removeFromSprint(sprint1, task11) << "\n"; //1
	cout << user2.addToSprint(sprint1, task1) << "\n"; //0
	cout << user2.removeFromSprint(sprint1, task2) << "\n"; //0
	cout << user2.addToSprint(sprint2, task1) << "\n"; //1
	cout << user2.addToSprint(sprint2, task2) << "\n"; //1

	sprint1.printDetails();
	cout << endl;
	user1.printAllTasks();
	user2.printAllTasks();
    return 0;
}