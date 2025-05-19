//FCFS AND SJF UISNG ARRIVAL TIME
#include <stdio.h>
#define MAX 100
typedef struct{
    int id;
    int CT;
    int AT;
    int BT;
    int TAT;
    int WT;
    int finished;
    
} process;

void sort_by_AT(process P[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(P[i].AT>P[j].AT){
                process temp=P[i];
                P[i]=P[j];
                P[j]=temp;
            }
        }
    }
}

void FCFS(process P[],int n){
    sort_by_AT(P, n);
    int currentTime=0;
    for(int i=0;i<n;i++){
        if(currentTime<P[i].AT){
            currentTime=P[i].AT;
        }
        currentTime+=P[i].BT;
        P[i].CT=currentTime;
        P[i].TAT=P[i].CT-P[i].AT;
        P[i].WT=P[i].TAT-P[i].BT;
    }
    
    printf("\n-----FCFS SCHEDULING-----\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",P[i].id,P[i].AT,P[i].BT,P[i].CT,P[i].TAT,P[i].WT);
    }
}

void SJF(process P[],int n){
    int currentTime=0;
    int completed=0;
    while(completed<n){
        int minBT=1e9;
        int idx=-1;
        for(int i=0;i<n;i++){
            if(!P[i].finished && P[i].AT<=currentTime && P[i].BT<minBT){
                minBT=P[i].BT;
                idx=i;
            }
        }
        if(idx!=-1){
            if(currentTime<P[idx].AT){
                currentTime=P[idx].AT;
            }
            currentTime+=P[idx].BT;
            P[idx].CT=currentTime;
            P[idx].TAT=P[idx].CT-P[idx].AT;
            P[idx].WT=P[idx].TAT-P[idx].BT;
            P[idx].finished=1;
            completed++;
        }
        else{
            currentTime++;
        }
    }
    printf("\n-----SJF SCHEDULING-----\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",P[i].id,P[i].AT,P[i].BT,P[i].CT,P[i].TAT,P[i].WT);
    }
}

int main(void){
    process p[MAX];
        int n;

        printf("Enter number of processes: ");
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            p[i].id = i + 1;
            printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
            scanf("%d%d", &p[i].AT, &p[i].BT);
            p[i].finished=0;
        }

        // Copy for both algorithms
        process p_fcfs[MAX], p_sjf[MAX];
        for (int i = 0; i < n; i++) {
            p_fcfs[i] = p[i];
            p_sjf[i] = p[i];
        }

        FCFS(p_fcfs, n);
        SJF(p_sjf, n);

        return 0;
}
    


/*
OUTPUT:

Enter number of processes: 4
Enter Arrival Time and Burst Time for Process 1: 0
7
Enter Arrival Time and Burst Time for Process 2: 8
3
Enter Arrival Time and Burst Time for Process 3: 3
4
Enter Arrival Time and Burst Time for Process 4: 5
6

-----FCFS SCHEDULING-----
PID	AT	BT	CT	TAT	WT
P1	0	7	7	7	0
P3	3	4	11	8	4
P4	5	6	17	12	6
P2	8	3	20	12	9

-----SJF SCHEDULING-----
PID	AT	BT	CT	TAT	WT
P1	0	7	7	7	0
P2	8	3	14	6	3
P3	3	4	11	8	4
P4	5	6	20	15	9
Program ended with exit code: 0
*/
