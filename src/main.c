#include <stdio.h>
#include "fcfs.c"
#include "prioritynp.c"
#include "priorityp.c"
#include "rr.c"
#include "srtf.c"
#include "sjf.c"

int main(){
    int n;
    char c;
    while(1){
    printf("Enter which process you want to select:\n1) First Come First Serve \n2) Shortest Remaining Time First \n3) Priority (preemptive) \n4) Shortest Job First \n5) Priority (non-preemptive) \n6) Round Robin \n7) exit..\n\nPlease Enter Your Choice:");
    scanf("%d",&n);
    switch(n){
        case 1:
            fcfs_();
            break;
        case 2:
            srtf();
            break;
        case 3:
            priority_p();
            break;
        case 4:
            sjf_();
            break;
        case 5:
            priority_np();
            break;
        case 6:
            round_robin();
            break;
        case 7:
            return 0;
            break;
        default:
            printf("Enter correct option");
            break; 
    }
    printf("\nYour Gantt chart will be in temp.html file created.. if you gave correct parameters\n");
    printf("\nNeed for other algorithms:(y for YES and n for NO)\n");
    scanf(" %c",&c);
    if(c=='n'){
        break;
    }
    else{
        if(c!='y'){
            printf("please enter valid response\n");
            break;
        }
    }
    }
    return 0;
}
