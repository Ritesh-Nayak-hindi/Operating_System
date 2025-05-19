//BANKERS ALGORITHIM
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define P 5
#define R 3
int alloc[P][R]=
{   {0, 1, 0},  // Allocation Matrix
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int max[P][R]={
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int avail[R]={3,3,2};
int work[R]={3,3,2};//initializing this work matrix
int need[P][R];
int main(void){
    for(int i=0;i<P;i++){
        for(int j=0;j<R;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    bool finish[P]={false};
    int safe_seq[P];
    int count=0;
    while(count <P){
        bool found=false;
        for(int i=0;i<P;i++){
            if(!finish[i]){
                int j;
                for(j=0;j<R;j++){
                    if(need[i][j]>work[j]){
                        break;
                    }
                }
                
                if(j==R){
                    //therofre all the resources needed are avilable
                    //realse all the resiurces
                    for(int k=0;k<R;k++){
                        work[k]+=alloc[i][k];
                    }
                    safe_seq[count++]=i;
                    found=true;
                    finish[i]=true;
                }
            }
        }
        //if with in the while loop we donot find any process to be in safe sequence then we break it
        if(!found){
            printf("NO SAFE SEQUENCE IS FOUND\n");
            return 0;
        }
    }
    
    printf("SAFE SEQUENCE IS FOUND\nSAFE SEQUENCE:\n");
    for(int i=0;i<P;i++){
        printf("P%d ",safe_seq[i]);
    }
    return 0;
    
    
    
    
}


/*
OUTPUT 
SAFE SEQUENCE IS FOUND
SAFE SEQUENCE:
P1 P3 P4 P0 P2 Program ended with exit code: 0
*/
