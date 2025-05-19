//scheduling algorithims
//PRIOPRITY SCHEDULING
#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
void PRIORITY(int bt[],int wt[],int tat[],int p[],int pr[],int n){
    printf("FCFS SCHEDULING\n");
    //sort the bt according to the priority
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(pr[i]>pr[j]){
                swap(&pr[i], &pr[j]);
                swap(&bt[i], &bt[j]);
                swap(&p[i], &p[j]);
                
            }
        }
    }
    
    wt[0]=0;
    for(int i=1;i<n;i++){
        wt[i]=wt[i-1]+bt[i-1];
    }
    float total_WT=0.0;
    float total_TAT=0.0;
    printf("\nP\t\tBT\t\tWT\t\tTAT");
    for(int i=0;i<n;i++){
        tat[i]=bt[i]+wt[i];
        total_WT+=wt[i];
        total_TAT+=tat[i];
        printf("\nP%d\t\t%d\t\t%d\t\t%d",i+1,bt[i],wt[i],tat[i]);
    }
    printf("\nAVG_WT:%2f\nAVG_TAT:%2f\n",total_WT/n,total_TAT/n);
}





int main(void){
    printf("ENTER THE NUMBER OF PROCESSES");
    int n;
    scanf("%d",&n);
    int bt[n],wt[n],tat[n],p[n],pr[n];
    for(int i=0;i<n;i++){
        printf("ENTER THE BURST TIME AND PRIORITY OF THE PROCESS %d",i+1);
        scanf("%d\n",&bt[i]);
        scanf("%d",&pr[i]);
        p[i]=i+1;//--> tracks the index of the invloved process
    }
    PRIORITY(bt, wt, tat, p, pr, n);
    
}





/*

ENTER THE NUMBER OF PROCESSES5
ENTER THE BURST TIME AND PRIORITY OF THE PROCESS 110
3
ENTER THE BURST TIME AND PRIORITY OF THE PROCESS 21
1
ENTER THE BURST TIME AND PRIORITY OF THE PROCESS 32
4
ENTER THE BURST TIME AND PRIORITY OF THE PROCESS 41
5
ENTER THE BURST TIME AND PRIORITY OF THE PROCESS 55
2
FCFS SCHEDULING

P		BT		WT		TAT
P1		1		0		1
P2		5		1		6
P3		10		6		16
P4		2		16		18
P5		1		18		19
AVG_WT:8.200000
AVG_TAT:12.000000
Program ended with exit code: 0
*/
