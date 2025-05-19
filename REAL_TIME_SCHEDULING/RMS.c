//RATE MONOTONINC SCHEDULING
#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int task_id;
    int execution_time;
    int period;
    int remaining_time;
    int next_release_time;
}Task;

int lcm(int a,int b){
    int max=(a>b) ?a:b;
    while(1){
        if(max%a==0 && max%b==0){
            return max;
        }
        max++;
    }
}

int calculate_period_lcm(Task T[],int n){
    int res=T[0].period;
    for(int i=1;i<n;i++){
        res=lcm(res, T[i].period);
    }
    return res;
}

int main(void){
    int n;
    printf("ENTER THE NUMBER OF TASKS TO BE PERFORMED\n");
    scanf("%d",&n);
    Task T[n];
    for(int i=0;i<n;i++){
        printf("ENTER THE EXECUTION TIME AND PERIOD OF TASK %d",i+1);
        scanf("%d",&T[i].execution_time);
        scanf("%d",&T[i].period);
        T[i].task_id=i+1;
        T[i].next_release_time=0;
        T[i].remaining_time=0;
    }
    int total_time=calculate_period_lcm(T, n);
    for(int time=0;time<total_time;time++){
        //removing the tasks which can start at this period
        for(int i=0;i<n;i++){
            if(time==T[i].next_release_time){
                T[i].remaining_time=T[i].execution_time;
                T[i].next_release_time+=T[i].period;
            }
        }
        
        //checking whoch has the highest priority (shortest period and remaing time to be executed)
        int min_period=9999999;
        int selected_task=-1;
        for(int i=0;i<n;i++){
            if(T[i].remaining_time>0 && T[i].period<min_period){
                min_period=T[i].period;
                selected_task=i;
            }
        }
        
        //executing th task
        if(selected_task!=-1){
            printf("TIME:%d RUNNING TASK:%d\n",time+1,T[selected_task].task_id);
            T[selected_task].remaining_time--;
        }
        else{
            printf("TIME:%d IDLE\n",time+1);
        }
        
        
        
    }
    return 0;
}




/*

ENTER THE NUMBER OF TASKS TO BE PERFORMED
2
ENTER THE EXECUTION TIME AND PERIOD OF TASK 11
4
ENTER THE EXECUTION TIME AND PERIOD OF TASK 22
6
TIME:1 RUNNING TASK:1
TIME:2 RUNNING TASK:2
TIME:3 RUNNING TASK:2
TIME:4 IDLE
TIME:5 RUNNING TASK:1
TIME:6 IDLE
TIME:7 RUNNING TASK:2
TIME:8 RUNNING TASK:2
TIME:9 RUNNING TASK:1
TIME:10 IDLE
TIME:11 IDLE
TIME:12 IDLE
Program ended with exit code: 0
*/
