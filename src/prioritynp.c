#include <stdio.h>

typedef struct prioritynp{
        int arrival;
        int burst;
        int process;
        int priority;
    }prioritynp;

void minprocess(prioritynp p[],int *time,int *a,int n,int ft[],int overhead,int rft[]){
    int min=999999;
    int index;
    struct prioritynp temp;
    for(int i=*a;i<n;i++){
        if(p[i].arrival<=*time){
            if(p[i].priority<min){
                min=p[i].priority;
                index=i;
            }
        }
    }
    if(min!=999999){
        temp=p[*a];
        p[*a]=p[index];
        p[index]=temp;
    (*time)+=p[*a].burst+overhead;
    ft[*a]=(*time);
    rft[*a]=ft[*a]-overhead;
    (*a)++;
    }
    if(min==999999){
        int min_priority=999999;
        for(int i=*a;i<n;i++){
            if(p[i].arrival>*time){
                if(p[i].arrival<min){
                min=p[i].arrival;
                min_priority=p[i].priority;
                index=i;}
                if(p[i].arrival==min){
                    if(p[i].priority<min_priority){
                min=p[i].arrival;
                min_priority=p[i].priority;
                index=i;
                    }
                }
            }
        }
        temp=p[*a];
        p[*a]=p[index];
        p[index]=temp;
    (*time)=(p[*a].arrival-(*time))+p[*a].burst+overhead;
    ft[*a]=(*time);
    rft[*a]=ft[*a]-overhead;
    (*a)++;
    }
};

void maxprocess(prioritynp p[],int *time,int *a,int n,int ft[],int overhead,int rft[]){
    int min=-1;
    int index;
    struct prioritynp temp;
    for(int i=*a;i<n;i++){
        if(p[i].arrival<=*time){
            if(p[i].priority>min){
                min=p[i].priority;
                index=i;
            }
        }
    }
    if(min!=-1){
        temp=p[*a];
        p[*a]=p[index];
        p[index]=temp;
    
    (*time)+=p[*a].burst+overhead;
    ft[*a]=(*time);
    rft[*a]=ft[*a]-overhead;
    (*a)++;
    }
    if(min==-1){
        min=999999;
        int min_priority=-1;
        for(int i=*a;i<n;i++){
            if(p[i].arrival>*time){
                if(p[i].arrival<min){
                min=p[i].arrival;
                min_priority=p[i].priority;
                index=i;}
                if(p[i].arrival==min){
                if(p[i].priority>min_priority){
                min=p[i].arrival;
                min_priority=p[i].priority;
                index=i;}}
            }
        }
        temp=p[*a];
        p[*a]=p[index];
        p[index]=temp;
    
    (*time)=(p[*a].arrival-(*time))+p[*a].burst+overhead;
    ft[*a]=(*time);
    rft[*a]=ft[*a]-overhead;
    (*a)++;
    }
    //aa time aj finish time che f[a] no
};

void priority_np(){
    FILE *fp;
fp = fopen("temp.html", "w");
fprintf(fp, "<html>\n<head>\n<style>\n");
fprintf(fp, ".gantt-chart {\n     display: flex;flex-direction: column;height: 250px;\nwidth: 300%\n}\n");
fprintf(fp, ".row {\ndisplay: flex;align-items: center;height: 50px;\n}\n");
fprintf(fp, ".cell {\nheight: 100%;display: flex;align-items: center;justify-content: center;border: 1px solid black;box-sizing: border-box;font-size: 12px;font-weight: bold;text-align: center;\n}\n");

fprintf(fp, ".empty {\nbackground-color: #e6e6e6;\n}\n");
fprintf(fp, ".p0 {\nbackground-color: #e60000;\n}\n");
fprintf(fp, ".p1 {\nbackground-color: #00e600;\n}\n");
fprintf(fp, ".p2 {\nbackground-color: #0000e6;\n}\n");
fprintf(fp, ".p3 {\nbackground-color: #e6e600;\n}\n");
fprintf(fp, ".p4 {\nbackground-color: #000000;\n}\n");
fprintf(fp, "</style>\n</head>\n<body>\n");
fprintf(fp, "<h1>Gantt Chart</h1>\n<div class=\"gantt-chart\">\n<section class=\"row\">\n");

    int n,time=0,a=0,overhead;
    int ad=0;
    printf("Enter the number of processes you want: ");
    scanf("%d",&n);
    int ft[n],tat[n],wt[n],rft[n];
    prioritynp p[n];
    for(int i=0;i<n;i++){
        printf("Enter the arrival time for process %d: ",i);
        scanf("%d",&p[i].arrival);
        p[i].process=i;
        printf("Enter the Burst time for process %d: ",i);
        scanf("%d",&p[i].burst);
        printf("Enter the Priority for process %d: ",i);
        scanf("%d",&p[i].priority);
    }
    printf("Enter Priority Order(Default: Ascending)(1: Descending & 0: Ascending): ");
    scanf("%d",&ad);
    printf("Enter Overhead: ");
    scanf("%d",&overhead);
    while(a<n){
    if(ad==0){
        minprocess(p,&time,&a,n,ft,overhead,rft);
    }
    else if(ad==1){
     maxprocess(p,&time,&a,n,ft,overhead,rft);
    }
    else{
        printf("write correct order:");
        return ;
        break;
    }
    }
    for(int i=0;i<n;i++){
        tat[i]=rft[i]-p[i].arrival;
    }
     for(int i=0;i<n;i++){
        wt[i]=tat[i]-p[i].burst;
        if(wt[i]<0){
            ft[i]+=-(wt[i]);
            tat[i]+=-(wt[i]);
            wt[i]+=-(wt[i]);
            printf("%d to %d is no process zone\n",ft[i-1],p[i].arrival);
        }
    }

      printf("************Table************\n");
    printf("Process\t\tBT\tAT\tWT\tTAT\tFT\tPrio\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process-%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].process,p[i].burst,p[i].arrival,wt[i],tat[i],ft[i]-overhead,p[i].priority);
    }
    printf("-----------------------------------\n");

    
    if(p[0].arrival>0){
        printf("0 to %d is no process zone\n",p[0].arrival);
        fprintf(fp, "<div class='cell empty' style=\"width: %d%;\">No Process</div>\n", p[0].arrival);
    }

    int current_time = p[0].arrival;
for (int i = 0; i < n; i++) {
    int start_time = current_time;
    current_time = ft[i];
    int empty_time = p[i].arrival - start_time;
    if (empty_time > 0) {
        fprintf(fp, "<div class='cell empty'  style=\"width: %d%;\">No Process</div>\n", (empty_time)*1);
    }
    fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">process %d</div>\n", p[i].process % 4,p[i].burst*1,p[i].process);
    if(i!=n-1){
    fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">O</div>\n", 4,(overhead)*1);}
    //pela ma 15 sudhi jatu tu pan last 16 hatu to mast right align karva ane i+1 leva thi thai jase
}
fprintf(fp, "</section>\n<div class=\"row\">\n");
for(int i=0;i<=ft[n-1];i++){
    fprintf(fp, "<div class=\"cell\" style=\"text-align: right; width: %d%;\">%d</div>\n",1,i+1);
}
float avg_tat=0,avg_wt=0;
for(int i=0;i<n;i++){
    avg_tat+=tat[i];
    avg_wt+=wt[i];
}
printf("\nThe Average Turn Around time is: %f\nThe average Waiting time is: %f\n",(avg_tat/n),(avg_wt/n));
fprintf(fp, "</div>\n</body>\n</html>");
fclose(fp);
}