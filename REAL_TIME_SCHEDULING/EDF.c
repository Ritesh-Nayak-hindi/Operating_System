//EDF SCHEDULING
#include <stdio.h>
#define MAX 100
typedef struct {
    int pid;
    int ET;
    int P;
    int RT;
    int NRT;
    int deadline;
    int AT;
}process;

int lcm(int a,int b){
    int max=(a>b)? a:b;
    while(1){
        if(max%a==0 && max%b==0){
            return max;
        }
        max++;
    }
}

int lcm_period(process P[],int n){
    int res=P[0].P;
    for(int i=1;i<n;i++){
        res=lcm(res, P[i].P);
    }
    return res;
}

int main(void){
    int n=2;
    process P[n];
    
    for(int i=0;i<n;i++){
        printf("ENTER THE EXECUTION TIME AND PERIOD OF THE PRCESS %d :",i+1);
        scanf("%d",&P[i].ET);
        scanf("%d",&P[i].P);
        scanf("%d",P[i).AT;
        P[i].pid=i+1;
        P[i].RT=0;
        P[i].NRT=P[i].AT;
        P[i].deadline=0;
    }
    
    int total_time=lcm_period(P, n);
    for(int time=0;time<total_time;time++){
        //to find the NRT and RT of all the invo;lved processes
        for(int i=0;i<n;i++){
            if(time>=P[i].AT && time==P[i].NRT){
                P[i].RT=P[i].ET;
                P[i].NRT+=P[i].P;
                P[i].deadline=P[i].P+time;
            }
        }
        
        // check which process has the minimum deadline amogst all the processes
        int x=-1;
        int min_deadline=1e9;
        for(int i=0;i<n;i++){
            if(P[i].RT>0 && P[i].deadline<min_deadline){
                min_deadline=P[i].deadline;
                x=i;
            }
        }
        if(x!=-1){
            printf("TIME: %d RUNNING TASK: %d\n", time + 1, P[x].pid);
            P[x].RT--;
        }
        else{
            printf("TIME %d CPU IDLE\n",time+1);
        }
        
        //check for the missed dealines
        for(int i=0;i<n;i++){
            if(time==P[i].deadline-1 && P[i].RT>0){
                printf("THE TASK %d MISSED ITS DEADLINE AT TIME %d",P[i].pid,time+1);
                P[i].RT=0;
            }
        }
    }
}



/*
OUTPUT:

ENTER THE EXECUTION TIME AND PERIOD OF THE PRCESS 1 :1
4
ENTER THE EXECUTION TIME AND PERIOD OF THE PRCESS 2 :2
5
TIME: 1 RUNNING TASK: 1
TIME: 2 RUNNING TASK: 2
TIME: 3 RUNNING TASK: 2
TIME 4 CPU IDLE
TIME: 5 RUNNING TASK: 1
TIME: 6 RUNNING TASK: 2
TIME: 7 RUNNING TASK: 2
TIME 8 CPU IDLE
TIME: 9 RUNNING TASK: 1
TIME 10 CPU IDLE
TIME: 11 RUNNING TASK: 2
TIME: 12 RUNNING TASK: 2
TIME: 13 RUNNING TASK: 1
TIME 14 CPU IDLE
TIME 15 CPU IDLE
TIME: 16 RUNNING TASK: 2
TIME: 17 RUNNING TASK: 1
TIME: 18 RUNNING TASK: 2
TIME 19 CPU IDLE
TIME 20 CPU IDLE
Program ended with exit code: 0
*/
