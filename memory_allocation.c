//contiguous memory allocation
#include <stdio.h>
#define MAX 100
void print_allocation(int allocated[],int n){
    printf("\nProcess No.\t\tAllocated block\n");
    for(int i=0;i<n;i++){
        printf("  %d\t\t",i+1);
        if(allocated[i]!=-1){
            printf("%d\n",allocated[i]+1);
        }
        else{
            printf("NOT ALLCOATED\n");
        }
    }
}

void first_fit(int process_size[],int n,int blocksize[],int m){
    int allocated[MAX];
    for(int i=0;i<n;i++){
        allocated[i]=-1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(blocksize[j]>=process_size[i]){
                allocated[i]=j;
                blocksize[j]-=process_size[i];
                break;
            }
        }
    }
    printf("\n-----FIRST FIT ALLOCATION------\n");
    print_allocation(allocated,n);
}

void best_fit(int process_size[],int n,int blocksize[],int m){
    int allocated[MAX];
    for(int i=0;i<n;i++){
        allocated[i]=-1;
    }
    for(int i=0;i<n;i++){
        int best_idx=-1;
        for(int j=0;j<m;j++){
            if(blocksize[j]>=process_size[i]){
                if(best_idx==-1 ||blocksize[best_idx]>blocksize[j] ){
                    best_idx=j;
                }
            }
        }
        if(best_idx!=-1){
            allocated[i]=best_idx;
            blocksize[best_idx]-=process_size[i];
        }
    }
    
    printf("\n------BEST FIT ALLOCATION-------\n");
    print_allocation(allocated,n);
}

void worst_fit(int process_size[],int n,int blocksize[],int m){
    int allocated[MAX];
    for(int i=0;i<n;i++){
        allocated[i]=-1;
    }
    for(int i=0;i<n;i++){
        int worst_idx=-1;
        for(int j=0;j<m;j++){
            if(blocksize[j]>=process_size[i]){
                if(worst_idx==-1 || blocksize[worst_idx]<blocksize[j]){
                    worst_idx=j;
                }
            }
        }
        if(worst_idx!=-1){
            allocated[i]=worst_idx;
            blocksize[worst_idx]-=process_size[i];
        }
    }
    
    printf("\n-------WORST FIT ALLOCATION----------\n");
    print_allocation(allocated,n);
}

int main(void){
    int process_size[MAX];
    int block_size[MAX];
    int m,n;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter sizes of %d memory blocks:\n", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &block_size[i]);
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter sizes of %d processes:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &process_size[i]);
    
    int block_size1[MAX],block_size2[MAX],block_size3[MAX];
    for(int i=0;i<m;i++){
        block_size1[i]=block_size2[i]=block_size3[i]=block_size[i];
    }
    
    first_fit(process_size, n, block_size1, m);
    best_fit(process_size, n, block_size2, m);
    worst_fit(process_size, n, block_size3, m);


}



/*
OUTPUT:

Enter number of memory blocks: 3
Enter sizes of 3 memory blocks:
100
200
500
Enter number of processes: 4
Enter sizes of 4 processes:
212
417
112
426

-----FIRST FIT ALLOCATION------

Process No.		Allocated block
  1		3
  2		NOT ALLCOATED
  3		2
  4		NOT ALLCOATED

------BEST FIT ALLOCATION-------

Process No.		Allocated block
  1		3
  2		NOT ALLCOATED
  3		2
  4		NOT ALLCOATED

-------WORST FIT ALLOCATION----------

Process No.		Allocated block
  1		3
  2		NOT ALLCOATED
  3		3
  4		NOT ALLCOATED
Program ended with exit code: 0
*/
