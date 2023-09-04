# Job Scheduler
Design a Job Scheduler
# Definitions and requirements
A job scheduler is meant to schedule M jobs on N threads on a single machine. The input contains the following data:
-  Job name
-  Duration: Time taken to complete the job
-  Priority: Priority of the job [P0 > P1 > P2]
-  Deadline: Expiry time after which job should not be run [The clock starts from 0 and deadline is the actual clock time]
-  UserType: Type of user who has initiated the job. Precedence of users: Root > Admin > User
# Scheduling Algorithms 
# Shortest Job First [SJF]
Shortest Job First (SJF) is a scheduling policy that selects the waiting process with the smallest execution time to execute next.
In case of a tie, choose the job according to the priority order (higher priority job gets scheduled first)

# First Come First Serve [FCFS]
Jobs are executed on first come, first serve basis. The input would be taken as the order of jobs needing to be scheduled
# Fixed Priority Scheduling [FPS]
Each process is assigned a priority. Process with the highest priority should be executed first, followed by the next highest priority. In case of tie, choose the job according to the following order
- User Type
-  Longest Job First
# Earliest Deadline First [EDF]
The next job would be the one closest to its deadline. In case of tie, choose the job according to the following order
- Priority (higher priority job is scheduled first)
-  Duration (lower duration job is scheduled first).
In case we cannot schedule a job such that it completes before its deadline then it should be ignored.

# Other Requirments 
- Input: List of jobs, number of threads
- Output: The order of jobs scheduled for each algorithm on each thread as output.

# Output
![Screenshot (812)](https://github.com/hksirya/LowLevelDesign/assets/104431269/db9ccf63-d0c7-43ca-bd92-dc434c07855c)


