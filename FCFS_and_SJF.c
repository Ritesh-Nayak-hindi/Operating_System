//scheduling algorithims
#include <stdio.h>
#include <stdlib.h>


void FCFS(int bt[],int wt[],int tat[],int n){
    printf("FCFS SCHEDULING\n");
    wt[0]=0;
    for(int i=1;i<n;i++){
        wt[i]=wt[i-1]+bt[i-1];
    }
    float totalWT=0;
    float totalTAT=0;
    printf("\nP\t\tBT\t\tWT\t\tTAT");
    for(int i=0;i<n;i++){
        tat[i]=wt[i]+bt[i];
        totalWT+=wt[i];
        totalTAT+=tat[i];
        printf("\nP%d\t\t%d\t\t%d\t\t%d",i+1,bt[i],wt[i],tat[i]);
    }
    printf("\nAVG_WT:%2f\nAVG_TAT:%2f\n",totalWT/n,totalTAT/n);
}


void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
void SJF(int bt[],int wt[],int tat[],int n){
    printf("SJF SCHEDULING\n");
    wt[0]=0;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(bt[i]>bt[j]){
                swap(&bt[i], &bt[j]);
            }
        }
    }
    //create the waiting time
    for(int i=1;i<n;i++){
        wt[i]=wt[i-1]+bt[i-1];
    }
    float totalWT=0;
    float totalTAT=0;
    printf("\nP\t\tBT\t\tWT\t\tTAT");
    for(int i=0;i<n;i++){
        tat[i]=wt[i]+bt[i];
        totalWT+=wt[i];
        totalTAT+=tat[i];
        printf("\nP%d\t\t%d\t\t%d\t\t%d",i+1,bt[i],wt[i],tat[i]);
    }
    printf("\nAVG_WT:%2f\nAVG_TAT:%2f\n",totalWT/n,totalTAT/n);
}


int main(void){
    printf("ENTER THE NUMBER OF PROCESSES");
    int n;
    scanf("%d",&n);
    int bt[n],wt[n],tat[n];
    for(int i=0;i<n;i++){
        printf("ENTER THE BURST TIME OF THE PROCESS %d",i+1);
        scanf("%d",&bt[i]);
    }
    
    FCFS(bt, wt, tat, n);
    SJF(bt, wt, tat, n);
    
    
}


/*

OUTPUT:


ENTER THE NUMBER OF PROCESSES4
ENTER THE BURST TIME OF THE PROCESS 12
ENTER THE BURST TIME OF THE PROCESS 22
ENTER THE BURST TIME OF THE PROCESS 33
ENTER THE BURST TIME OF THE PROCESS 46
FCFS SCHEDULING

P		BT		WT		TAT
P1		2		0		2
P2		2		2		4
P3		3		4		7
P4		6		7		13
AVG_WT:3.250000
AVG_TAT:6.500000
SJF SCHEDULING

P		BT		WT		TAT
P1		2		0		2
P2		2		2		4
P3		3		4		7
P4		6		7		13
AVG_WT:3.250000
AVG_TAT:6.500000
Program ended with exit code: 0
*/
