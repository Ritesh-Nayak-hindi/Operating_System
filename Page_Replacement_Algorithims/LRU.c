//LRU PAGE REPLACEMENT ALGORITHIM
#include <stdio.h>
#define MAX 50
int LRU_index(int time[],int t){
    int min=time[0];
    int pos=0;
    for(int i=0;i<t;i++){
        if(time[i]<min){
            min=time[i];
            pos=i;
        }
    }
    return pos;
}

void LRU(int pages[],int n,int f){
    int frames[MAX],time[MAX],count=0,faults=0;
    for(int i=0;i<f;i++){
        frames[i]=-1;
        time[i]=0;
    }
    
    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<f;j++){
            if(frames[j]==pages[i]){
                found=1;
                count++;
                time[j]=count;
                //this is original frame and will not cause a frame fault
                break;
            }
        }
        if(!found){
            //check for an empty loaction in the frames
            int pos=-1;
            for(int j=0;j<f;j++){
                if(frames[j]==-1){
                    pos=j;
                }
            }
            if(pos==-1){
                pos=LRU_index(time, f);
            }
            frames[pos]=pages[i];
            count++;
            time[pos]=count;
            faults++;
        }
        
        printf("Frame after page %d: ", pages[i]);
                for (int j = 0; j < f; j++)
                    if (frames[j] != -1) printf("%d ", frames[j]);
                printf("\n");
        
    }
    printf("Total Page Faults (LRU): %d\n", faults);
}

int main(void){
    int n, f, pages[MAX];

       printf("Enter number of pages: ");
       scanf("%d", &n);

       printf("Enter page reference string:\n");
       for (int i = 0; i < n; i++)
           scanf("%d", &pages[i]);

       printf("Enter number of frames: ");
       scanf("%d", &f);
    
    LRU(pages, n, f);
}


/*
OUTPUT:
Enter number of pages: 5
Enter page reference string:
1
1
0
2
3
Enter number of frames: 2
Frame after page 1: 1 
Frame after page 1: 1 
Frame after page 0: 0 1 
Frame after page 2: 0 2 
Frame after page 3: 3 2 
Total Page Faults (LRU): 4
Program ended with exit code: 0
*/
