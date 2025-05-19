//Multilevel Queue Scheduling

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int pid;
    int bt;
    int wt;
    int tat;
}process;

void calculate_fcfs(process P[],int n,int *start_time){
    P[0].wt=*start_time;//you need to update this start time evry time you call this fucntion

    // if we would like to have varibale arrival times then we need to sort the process queue by AT and then current time =start time 
    P[0].tat=P[0].bt+P[0].wt;
    for(int i=1;i<n;i++){
        P[i].wt=P[i-1].wt+P[i-1].bt;
        P[i].tat=P[i].bt+P[i].wt;
    }
    *start_time=P[n-1].wt+P[n-1].bt;
    //here starttime=currenttime
}

void calculate_avg(int values[],int n,char *type){
    int total = 0;
        for (int i = 0; i < n; i++) total += values[i];
    float avg= (float)total / n;
    printf("\nAverage %s: %.2f\n", type,avg);
}

void print_table(process P[],int n,char * queue_name){
    printf("\n%s QUEUE\n:",queue_name);
    printf("PID\t\tBT\t\tWT\t\tTAT\n");
    for(int i=0;i<n;i++){
        printf("PID%d\t\t%d\t\t%d\t\t%d\n",i+1,P[i].bt,P[i].wt,P[i].tat);
    }
}

int main(void){
    int sys_n;
    int user_n;
    printf("ENTER THE NUMBER OF SYSTEM AND USER PROCESSES\n");
    scanf("%d",&sys_n);
    scanf("%d",&user_n);
    process S[sys_n];
    process U[user_n];
    for(int i=0;i<sys_n;i++){
        printf("ENTER THE BURST TIME FOR THE SYSTEM PROCESS: ");
        scanf("%d",&S[i].bt);
        S[i].pid=i+1;
    }
    for(int i=0;i<user_n;i++){
        printf("ENTER THE BURST TIME FOR THE USER PROCESS: ");
        scanf("%d",&U[i].bt);
        U[i].pid=i+1;
    }
    int time=0;
    calculate_fcfs(S, sys_n,&time);
    calculate_fcfs(U, user_n,&time);
    
    print_table(S, sys_n, "SYSTEM");
    print_table(U, user_n, "USER");
    
    //calculating the average time
    int WT_ALL[sys_n+user_n];
    int TAT_ALL[sys_n+user_n];
    
    for(int i=0;i<sys_n;i++){
        WT_ALL[i]=S[i].wt;
        TAT_ALL[i]=S[i].tat;
    }
    for(int i=0;i<user_n;i++){
        WT_ALL[sys_n+i]=U[i].wt;
        TAT_ALL[sys_n+i]=U[i].tat;
    }
    
    calculate_avg(WT_ALL, sys_n+user_n,"WAITING TIME");
    calculate_avg(TAT_ALL, sys_n+user_n,"TURN_AROUND_TIME TIME");
    return 0;
}


/*

ENTER THE NUMBER OF SYSTEM AND USER PROCESSES
2
2
ENTER THE BURST TIME FOR THE SYSTEM PROCESS: 4
ENTER THE BURST TIME FOR THE SYSTEM PROCESS: 3
ENTER THE BURST TIME FOR THE USER PROCESS: 5
ENTER THE BURST TIME FOR THE USER PROCESS: 2

SYSTEM QUEUE
:PID		BT		WT		TAT
PID1		4		0		4
PID2		3		4		7

USER QUEUE
:PID		BT		WT		TAT
PID1		5		7		12
PID2		2		12		14

Average WAITING TIME: 5.75

Average TURN_AROUND_TIME TIME: 9.25
Program ended with exit code: 0
*/
