//FIFO PAGE REPLACEMENT ALGORITHIM
#include <stdio.h>
#define MAX 50
int search(int frames[],int key,int f){
    for(int i=0;i<f;i++){
        if(frames[i]==key){
            return 1;
        }
    }
    return 0;
}

void FIFO(int pages[],int n,int f){
    int frames[MAX];
    int count=0;
    int faults=0;
    int front=0;
    for(int i=0;i<f;i++){
        frames[i]=-1;
    }
    for(int i=0;i<n;i++){
        if(!search(frames, pages[i], f)){
            frames[front]=pages[i];
            front=(front+1)%f;
            faults++;
        }
        //what all was present in the frame after this one page
        printf("AFTER THE PAGE %d THE FRAME IS:\n",pages[i]);
        for(int j=0;j<f;j++){
            if(frames[j]!=-1){
                printf("FRAME: %d\n",frames[j]);
            }
        }
    }
    printf("NUMBER OF PAGE FAULTS:%d",faults);
}

int main(void){
    int n;
    int f;
    int pages[MAX];
    printf("ENTER THE LENGHT OF PAGE REFERENCE STRING");
    scanf("%d",&n);
    printf("ENTER THE PAGE REFERENCE STRING");//130356303124
    for(int i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }
    printf("ENTER THE NUMBER OF FRAMES");
    scanf("%d",&f);
    printf("\n-------FIFO ALLOCATION-------\n");
    FIFO(pages, n, f);
}


/*

OUTPUT:
ENTER THE LENGHT OF PAGE REFERENCE STRING5
ENTER THE PAGE REFERENCE STRING1
1
0
2
3
ENTER THE NUMBER OF FRAMES2

-------FIFO ALLOCATION-------
AFTER THE PAGE 1 THE FRAME IS:
FRAME: 1
AFTER THE PAGE 1 THE FRAME IS:
FRAME: 1
AFTER THE PAGE 0 THE FRAME IS:
FRAME: 1
FRAME: 0
AFTER THE PAGE 2 THE FRAME IS:
FRAME: 2
FRAME: 0
AFTER THE PAGE 3 THE FRAME IS:
FRAME: 2
FRAME: 3
NUMBER OF PAGE FAULTS:4
Program ended with exit code: 0
*/
