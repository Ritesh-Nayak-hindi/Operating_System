#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int task_id;
    int execution_time;
    int period;
    int remaining_time;
    int next_release_time;
    int deadline;
} Task;

int lcm(int a, int b) {
    int max = (a > b) ? a : b;
    while (1) {
        if (max % a == 0 && max % b == 0) {
            return max;
        }
        max++;
    }
}

int calculate_period_lcm(Task T[], int n) {
    int res = T[0].period;
    for (int i = 1; i < n; i++) {
        res = lcm(res, T[i].period);
    }
    return res;
}

int main(void) {
    int n;
    printf("ENTER THE NUMBER OF TASKS TO BE PERFORMED: ");
    scanf("%d", &n);

    Task T[n];
    for (int i = 0; i < n; i++) {
        printf("ENTER EXECUTION TIME AND PERIOD FOR TASK %d: ", i + 1);
        scanf("%d%d", &T[i].execution_time, &T[i].period);
        T[i].task_id = i + 1;
        T[i].next_release_time = 0;
        T[i].remaining_time = 0;
        T[i].deadline = T[i].period; // Initial deadline = period
    }

    int total_time = calculate_period_lcm(T, n);
    int busy_time = 0;
    int last_task = -1;

    for (int time = 0; time < total_time; time++) {

        // Release new jobs and reset remaining_time
        for (int i = 0; i < n; i++) {
            if (time == T[i].next_release_time) {
                if (T[i].remaining_time > 0) {
                    printf("!!! DEADLINE MISSED BY TASK %d at TIME %d\n", T[i].task_id, time);
                }
                T[i].remaining_time = T[i].execution_time;
                T[i].next_release_time += T[i].period;
                T[i].deadline = time + T[i].period;
            }
        }

        // Select task with earliest deadline (EDF)
        int min_deadline = 1e9;
        int selected_task = -1;
        for (int i = 0; i < n; i++) {
            if (T[i].remaining_time > 0 && T[i].deadline < min_deadline) {
                min_deadline = T[i].deadline;
                selected_task = i;
            }
        }

        // Execute selected task
        if (selected_task != -1) {
            printf("TIME: %d RUNNING TASK: %d\n", time + 1, T[selected_task].task_id);
            T[selected_task].remaining_time--;
            busy_time++;

            if (last_task != -1 && last_task != selected_task && T[last_task].remaining_time > 0) {
                printf("!!! TASK %d PREEMPTED BY TASK %d at TIME %d\n", T[last_task].task_id, T[selected_task].task_id, time + 1);
            }

            last_task = selected_task;
        } else {
            printf("TIME: %d IDLE\n", time + 1);
            last_task = -1;
        }
    }

    float cpu_utilization = (busy_time * 100.0) / total_time;
    printf("\nCPU UTILIZATION: %.2f%%\n", cpu_utilization);

    return 0;
}
