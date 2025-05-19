//PRODUCER CONSUMER PROBLEM
#include <stdio.h>
#include <stdlib.h>
#define MAX 5
int buffer[MAX];
int empty=MAX;
int full=0;
int mutex=1;
int in=0;
int out=0;
void wait_sem(int *s){
    (*s)--;
}
void signal_sem(int *s){
    (*s)++;
}

void produce(int item){
    wait_sem(&empty);
    wait_sem(&mutex);
    buffer[in]=item;
    printf("PRODUCER HAS CREATED ITEM:%d\n",item);
    in=(in+1)%MAX;
    signal_sem(&mutex);
    signal_sem(&full);
}

void consumer(void){
    wait_sem(&full);
    wait_sem(&mutex);
    int item =buffer[out];
    printf("THE ITEM CONSUMED IS:%d\n",item);
    out=(out+1)%MAX;
    signal_sem(&mutex);
    signal_sem(&empty);
}

int main(void){
    while(1){
        printf("ENTER\n1.PRODUCE\n2.TO CONSUME\n3.TO EXIT\nENTER YOUR CHOICE:");
        int choice;
        int item;
        scanf("%d",&choice);
        if(choice==3){
            break;
        }
        switch (choice) {
            case 1:
                if(empty==0){
                    printf("THE BUFFER IS COMPLETELY FULL");
                }
                else{
                    printf("ENTER THE ITEM\n");
                    scanf("%d",&item);
                    produce(item);
                }
                break;
                
            case 2:
                if(full==0){
                    printf("THE BUFFER IS COMPLETELY EMPTY");
                }
                else{
                    consumer();
                }
                break;
                
            default:
                break;
        }
    }
}



/*
OUTPUT:

ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:1
ENTER THE ITEM
10
PRODUCER HAS CREATED ITEM:10
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:1
ENTER THE ITEM20

PRODUCER HAS CREATED ITEM:20
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:2
THE ITEM CONSUMED IS:10
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:1
ENTER THE ITEM30

PRODUCER HAS CREATED ITEM:30
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:1
ENTER THE ITEM
40
PRODUCER HAS CREATED ITEM:40
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:2
THE ITEM CONSUMED IS:20
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:1
ENTER THE ITEM
50
PRODUCER HAS CREATED ITEM:50
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:1
ENTER THE ITEM
60
PRODUCER HAS CREATED ITEM:60
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:1
ENTER THE ITEM
70
PRODUCER HAS CREATED ITEM:70
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:1
THE BUFFER IS COMPLETELY FULLENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:2
THE ITEM CONSUMED IS:30
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:1
ENTER THE ITEM
80
PRODUCER HAS CREATED ITEM:80
ENTER
1.PRODUCE
2.TO CONSUME.TO EXIT
ENTER YOUR CHOICE:3
Program ended with exit code: 0
*/
