#include <stdio.h>
#define MAX 5
int state[MAX];
int sem[MAX];
int mutex=1;
void wait_sem(int *s){
    (*s)--;
}
void signal_sem(int *s){
    (*s)++;
}
void test(int i){
    if(state[i]==1 && state[(i+MAX-1)%MAX]!=2 && state[(i+1)%MAX]!=2){
        state[i]=2;//now the philosopher os eating
        signal_sem(&sem[i]);
    }
}

void take_fork(int i){
    wait_sem(&mutex);
    state[i]=1;
    test(i);
    signal_sem(&mutex);
    wait_sem(&sem[i]);
}

void put_fork(int i){
    wait_sem(&mutex);
    state[i]=0;
    test((i+MAX-1)%MAX);
    test((i+1)%MAX);
    signal_sem(&mutex);
}

void philosopher(int i){
    printf("\nTHE PHILOSPHER %d IS HUNGRY\n",i+1);
    take_fork(i);
    printf("\nTHE PHILOSOPHER %d IS EATING\n",i+1);
    put_fork(i);
    printf("\nTHE PHILOSPHER %d IS THINKING\n",i+1);
    
}
int main(void){
    while(1){
        printf("ENTER THE CHOICE\n1.TO EAT\n3.TO EXIT");
        int choice;
        scanf("%d",&choice);
        if(choice==3){
            break;
        }
        if(choice ==1){
            printf("ENTER THE PHILOSOPHER's ID(0 to %d)",MAX-1);
            int id;
            scanf("%d",&id);
            if(id>=0 && id<MAX){
                philosopher(id);
            }
            else{
                printf("INVALID ENRTY");
                continue;
            }
        }
    }
}


/*
OUTPUT:

ENTER THE CHOICE
1.TO EAT
3.TO EXIT1
ENTER THE PHILOSOPHER's ID(0 to 4)0

THE PHILOSPHER 1 IS HUNGRY

THE PHILOSOPHER 1 IS EATING

THE PHILOSPHER 1 IS THINKING
ENTER THE CHOICE
1.TO EAT
3.TO EXIT2
ENTER THE CHOICE
1.TO EAT
3.TO EXIT1
ENTER THE PHILOSOPHER's ID(0 to 4)2

THE PHILOSPHER 3 IS HUNGRY

THE PHILOSOPHER 3 IS EATING

THE PHILOSPHER 3 IS THINKING
ENTER THE CHOICE
1.TO EAT
3.TO EXIT1
ENTER THE PHILOSOPHER's ID(0 to 4)3

THE PHILOSPHER 4 IS HUNGRY

THE PHILOSOPHER 4 IS EATING

THE PHILOSPHER 4 IS THINKING
ENTER THE CHOICE
1.TO EAT
3.TO EXIT3
Program ended with exit code: 0
*/
