#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int task_id;
    int execution_time;
    int period;
    int deadline;
    int remaining_time;
} Task;

int compare_by_deadline(const void *a, const void *b) {
    Task *task_a = (Task *)a;
    Task *task_b = (Task *)b;
    return task_a->deadline - task_b->deadline;
}

void EDF_Scheduling(Task tasks[], int num_tasks) {
    int time = 0;
    int completed_tasks = 0;

    while (completed_tasks < num_tasks) {
        Task ready_queue[num_tasks];
        int ready_count = 0;

        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining_time > 0 && tasks[i].deadline > time) {
                ready_queue[ready_count++] = tasks[i];
            }
        }

        if (ready_count == 0) {
            printf("No tasks are ready to run at time %d\n", time);
            time++;
            continue;
        }

        qsort(ready_queue, ready_count, sizeof(Task), compare_by_deadline);

        Task *current_task = &ready_queue[0];

        printf("At time %d, executing task %d (Remaining time: %d, Deadline: %d)\n", time, current_task->task_id, current_task->remaining_time, current_task->deadline);

        current_task->remaining_time--;

        if (current_task->remaining_time == 0) {
            completed_tasks++;
            printf("Task %d completed at time %d\n", current_task->task_id, time + 1);
        }

        time++;
    }
}

int main() {
    Task tasks[] = {
        {1, 3, 5, 5, 3},
        {2, 2, 7, 7, 2},
        {3, 1, 4, 4, 1},
        {4, 4, 10, 10, 4}
    };
    int num_tasks = sizeof(tasks) / sizeof(tasks[0]);

    EDF_Scheduling(tasks, num_tasks);

    return 0;
}
