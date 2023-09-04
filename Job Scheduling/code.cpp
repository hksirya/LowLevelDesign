#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

enum User { ROOT, ADMIN, USER };
enum SchedulingAlgorithms { FCFS, SJF, FPS, EDF };

class Job {
private:
    int id;
    string name;
    int priority;
    int duration;
    int deadline;
    User user;

    static int getUniqueId() {
        static int id = 1;
        return id++;
    }

public:
    // Constructor
    Job(string name, int priority, int duration, int deadline, User user) {
        this->name = name;
        this->id = getUniqueId();
        this->priority = priority;
        this->duration = duration;
        this->deadline = deadline;
        this->user = user;
    }

    // Getter for id
    int getId() const {
        return id;
    }

    // Getter for name
    string getName() const {
        return name;
    }

    // Getter for priority
    int getPriority() const {
        return priority;
    }

    // Getter for duration
    int getDuration() const {
        return duration;
    }

    // Getter for deadline
    int getDeadline() const {
        return deadline;
    }

    // Getter for user
    User getUser() const {
        return user;
    }
};

struct fcfsComparator {
    bool operator()(const Job& lhs, const Job& rhs) const {
        return lhs.getId() > rhs.getId();
    }
};

struct sjfComparator {
    bool operator()(const Job& lhs, const Job& rhs) const {
        return lhs.getDuration() > rhs.getDuration()
            || (lhs.getDuration() == rhs.getDuration() && lhs.getPriority() > rhs.getPriority());
    }
};

struct fpsComparator {
    bool operator()(const Job& lhs, const Job& rhs) const {
        return lhs.getPriority() > rhs.getPriority()
            || (lhs.getPriority() == rhs.getPriority() && lhs.getUser() > rhs.getUser())
            || (lhs.getPriority() == rhs.getPriority() && lhs.getUser() == rhs.getUser() && lhs.getDuration() < rhs.getDuration());
    }
};

struct edfComparator {
    bool operator()(const Job& lhs, const Job& rhs) const {
        return lhs.getDeadline() > rhs.getDeadline()
            || (lhs.getDeadline() == rhs.getDeadline() && lhs.getPriority() > rhs.getPriority())
            || (lhs.getPriority() == rhs.getPriority() && lhs.getDeadline() == rhs.getDeadline() && lhs.getDuration() > rhs.getDuration());
    }
};

class Scheduler {
private:
    vector<Job> jobs;
    priority_queue<Job, vector<Job>, fcfsComparator> fcfs;
    priority_queue<Job, vector<Job>, sjfComparator> sjf;
    priority_queue<Job, vector<Job>, fpsComparator> fps;
    priority_queue<Job, vector<Job>, edfComparator> edf;

public:
    Scheduler() {}

    void addJob(Job& job) {
        jobs.push_back(job);
        fcfs.push(job);
        sjf.push(job);
        fps.push(job);
        edf.push(job);
    }

    void processThreads(vector<int>& threadCapacity) {
        int minElement = *min_element(threadCapacity.begin(), threadCapacity.end());

        for (int i = 0; i < threadCapacity.size(); i++) {
            threadCapacity[i] -= minElement;
        }
    }

    vector<vector<Job>> schedulingAlgorithms(SchedulingAlgorithms algorithm, int threads) {
        vector<vector<Job>> result;
        result.resize(threads);
        vector<int> threadCapacity(threads, 0);

        switch (algorithm) {
            case SchedulingAlgorithms::FCFS:
                while (!fcfs.empty()) {
                    for (int i = 0; i < threads; i++) {
                        if (!fcfs.empty() && threadCapacity[i] == 0) {
                            auto top = fcfs.top();
                            fcfs.pop();
                            result[i].push_back(top);
                            threadCapacity[i] += top.getDuration();
                        }
                    }
                    processThreads(threadCapacity);
                }
                break;
            case SchedulingAlgorithms::SJF:
                while (!sjf.empty()) {
                    for (int i = 0; i < threads; i++) {
                        if (!sjf.empty() && threadCapacity[i] == 0) {
                            auto top = sjf.top();
                            sjf.pop();
                            result[i].push_back(top);
                            threadCapacity[i] += top.getDuration();
                        }
                    }
                    processThreads(threadCapacity);
                }
                break;
            case SchedulingAlgorithms::FPS:
                while (!fps.empty()) {
                    for (int i = 0; i < threads; i++) {
                        if (!fps.empty() && threadCapacity[i] == 0) {
                            auto top = fps.top();
                            fps.pop();
                            result[i].push_back(top);
                            threadCapacity[i] += top.getDuration();
                        }
                    }
                    processThreads(threadCapacity);
                }
                break;
            case SchedulingAlgorithms::EDF:
                while (!edf.empty()) {
                    for (int i = 0; i < threads; i++) {
                        if (!edf.empty() && threadCapacity[i] == 0) {
                            auto top = edf.top();
                            edf.pop();
                            result[i].push_back(top);
                            threadCapacity[i] += top.getDuration();
                        }
                    }
                    processThreads(threadCapacity);
                }
                break;
            default:
                break;
        }

        return result;
    }
};
int main() {
	Job j1("J1", 10, 0, 10, User::ROOT);
	Job j2("J2", 20, 0, 40, User::ADMIN);
	Job j3("J3", 15, 2, 40, User::ROOT);
	Job j4("J4", 30, 1, 40, User::USER);
	Job j5("J5", 10, 2, 30, User::USER);

	Scheduler scheduler;
	scheduler.addJob(j1);
	scheduler.addJob(j2);
	scheduler.addJob(j3);
	scheduler.addJob(j4);
	scheduler.addJob(j5);

	cout << "******** FCFS **************" << endl;

	vector<vector<Job>> res = scheduler.schedulingAlgorithms(SchedulingAlgorithms::FCFS, 2);

    for (size_t i = 0; i< res.size(); ++i)
    {
        vector<Job> temp = res[i];
        for (Job job : temp)
            cout << job.getName().c_str() << " ";
        cout << endl;
    }

	cout << "******** SJF **************" << endl;

	res = scheduler.schedulingAlgorithms(SchedulingAlgorithms::SJF, 2);

    for (size_t i = 0; i< res.size(); ++i)
    {
        vector<Job> temp = res[i];
        for (Job job : temp)
            cout << job.getName().c_str() << " ";
        cout << endl;
    }

	cout << "******** FPS **************" << endl;

	res = scheduler.schedulingAlgorithms(SchedulingAlgorithms::FPS, 2);

    for (size_t i = 0; i< res.size(); ++i)
    {
        vector<Job> temp = res[i];
        for (Job job : temp)
            cout << job.getName().c_str() << " ";
        cout << endl;
    }

    cout << "******** EDF **************" << endl;

	res = scheduler.schedulingAlgorithms(SchedulingAlgorithms::EDF, 2);

    for (size_t i = 0; i< res.size(); ++i)
    {
        vector<Job> temp = res[i];
        for (Job job : temp)
            cout << job.getName().c_str() << " ";
        cout << endl;
    }
	return 0;
}
