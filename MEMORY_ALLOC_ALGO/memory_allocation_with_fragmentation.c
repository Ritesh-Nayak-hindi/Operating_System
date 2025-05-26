//memory allcation in OS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
void print_alloction(int allocated[],int n){
    printf("Process\t\tAllocated Block\n");
    for(int i=0;i<n;i++){
        if(allocated[i]!=-1){
            printf("\t%d\t\t\t%d\n",i+1,allocated[i]);
        }
        else{
            printf("\t%d\t\t\tNot Allocated\n",i+1);
        }
    }
    printf("\n\n");
}

int is_in(int allocated[],int n,int key){
    for(int i=0;i<n;i++){
        if(allocated[i]==key){
            return 1;
        }
    }
    return 0;
}


void first_fit(int process_size[],int p,int block_size[],int b){
    int allocated[MAX];
    for(int i=0;i<p;i++){
        allocated[i]=-1;
    }
    int internal=0;
    int external=0;
    for(int i=0;i<p;i++){
        for(int j=0;j<b;j++){
            if(block_size[j]>=process_size[i]){
                allocated[i]=j;
                block_size[j]-=process_size[i];
                
                break;//i found the required block for the allocation right!!
            }
        }
    }
    
    //calculating the external fragmentation
    for(int i=0;i<b;i++){
        if(!is_in(allocated, p, i)){
            external+=block_size[i];
        }
        else{
            internal+=block_size[i];
        }
    }
    
    printf("-----------FIRST FIT-------------");
    print_alloction(allocated, p);
    printf("INTERNAL FRAGMENTATION:%d\n",internal);
    printf("EXTERNAL FRAGMENTATION:%d\n",external);
}


void best_fit(int process_size[],int p,int block_size[],int b){
    int allocated[MAX];
    for(int i=0;i<p;i++){
        allocated[i]=-1;
    }
    int internal=0;
    int external=0;
    for(int i=0;i<p;i++){
        int best_idx=-1;
        for(int j=0;j<b;j++){
            if(block_size[j]>=process_size[i]){
                if(best_idx==-1 || block_size[best_idx]>block_size[j]){
                    best_idx=j;
                }
            }
        }
        
        if(best_idx!=-1){
            allocated[i]=best_idx;
            block_size[best_idx]-=process_size[i];
            
        }
        
    }
    
        for(int i=0;i<b;i++){
            if(!is_in(allocated, p, i)){
                external+=block_size[i];
            }
            else{
                internal+=block_size[i];
            }
        }
    printf("-----------BEST FIT-------------");
    print_alloction(allocated, p);
    printf("INTERNAL FRAGMENTATION:%d\n",internal);
    printf("EXTERNAL FRAGMENTATION:%d\n",external);
}


void worst_fit(int process_size[],int p,int block_size[],int b){
    int allocated[MAX];
    for(int i=0;i<p;i++){
        allocated[i]=-1;
    }
    int internal=0;
    int external=0;
    for(int i=0;i<p;i++){
        int worst_idx=-1;
        for(int j=0;j<b;j++){
            if(block_size[j]>=process_size[i]){
                if(worst_idx==-1 || block_size[worst_idx]<block_size[j]){
                    worst_idx=j;
                }
            }
        }
        
        if(worst_idx!=-1){
            allocated[i]=worst_idx;
            block_size[worst_idx]-=process_size[i];
            
        }
        
    }
    
        for(int i=0;i<b;i++){
            if(!is_in(allocated, p, i)){
                external+=block_size[i];
            }
            else{
                internal+=block_size[i];
            }
        }
    printf("-----------WORST FIT-------------");
    print_alloction(allocated, p);
    printf("INTERNAL FRAGMENTATION:%d\n",internal);
    printf("EXTERNAL FRAGMENTATION:%d\n",external);
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

Enter number of memory blocks: 5
Enter sizes of 5 memory blocks:
100
500
200
300
600
Enter number of processes: 4
Enter sizes of 4 processes:
212
417
112
426
-----------FIRST FIT-------------Process		Allocated Block
	1			1
	2			4
	3			1
	4			Not Allocated


INTERNAL FRAGMENTATION:359
EXTERNAL FRAGMENTATION:600
-----------BEST FIT-------------Process		Allocated Block
	1			3
	2			1
	3			2
	4			4


INTERNAL FRAGMENTATION:433
EXTERNAL FRAGMENTATION:100
-----------WORST FIT-------------Process		Allocated Block
	1			4
	2			1
	3			4
	4			Not Allocated


INTERNAL FRAGMENTATION:359
EXTERNAL FRAGMENTATION:600
Program ended with exit code: 0


*/
