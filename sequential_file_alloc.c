//sequential file allocation
#include <stdio.h>
#define MAX 100
typedef struct{
    int startNliock;
    int length;
    int allocated;
}File;

int main(void){
    int disk[MAX]={0};
    int numFile;
    int totalBlock;
    File F[MAX];
    int start;
    int len;
    printf("ENTER THE NUMBER OF FILES:");
    scanf("%d",&numFile);
    printf("ENTER THE NUMEBR OF TOTAL BLOCKS:");
    scanf("%d",&totalBlock);
    
    for(int i=0;i<numFile;i++){
        printf("ENTER THE START OF BLOCK AND LENGHT OF FILE");
        scanf("%d",&start);
        scanf("%d",&len);
        if(start+len>totalBlock){
            printf("ERROR MEMORY OVERFLOWN\n");
            continue;
        }
        //check whether the disk blocks are free or not
        int free=1;
        for(int k=start;k<start+len;k++){
            if(disk[k]==1){
                free=0;
                break;
            }
        }
        //if the space in the disk is free over a period then we do the follwing
        if(free){
            //alllocate that space in the disk
            for(int j=start;j<start+len;j++){
                disk[j]=1;
            }
            F[i].startNliock=start;
            F[i].length=len;
            F[i].allocated=1;
            printf("File %d allocated from block %d to %d\n", i + 1, start, start + len - 1);
        }
        else{
            printf("THE DISK IS ALREDAY ALLCOATED , TRY AGAIN\n");
            F[i].allocated=0;
            
        }
        
        
    }
    
    
    //print the allocation table properly
    printf("\n--------FILE ALLOCATION TABLE--------\n");
    printf("\nFILE NO.\t\tSTART BLOCK\t\tLENGTH\n");
    for(int i=0;i<numFile;i++){
        if(F[i].allocated){
            printf("%d\t\t\t\t%d\t\t\t\t%d\n",i+1,F[i].startNliock,F[i].length);
        }
        else{
            printf("%d\t\t\t\t----------FILE NOT ALLOCATED-------",i+1);
        }
       
    }
}


/*
OUTPUT :
ENTER THE NUMBER OF FILES:3
ENTER THE NUMEBR OF TOTAL BLOCKS:20
ENTER THE START OF BLOCK AND LENGHT OF FILE2
5
File 1 allocated from block 2 to 6
ENTER THE START OF BLOCK AND LENGHT OF FILE7
4
File 2 allocated from block 7 to 10
ENTER THE START OF BLOCK AND LENGHT OF FILE5
3
THE DISK IS ALREDAY ALLCOATED , TRY AGAIN

--------FILE ALLOCATION TABLE--------

FILE NO.		START BLOCK		LENGTH
1				2				5
2				7				4
3				----------FILE NOT ALLOCATED-------Program ended with exit code: 0
*/
