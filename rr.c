#include <stdio.h>

typedef struct {
    int arrival;
    int burst;
    int process;
    int remaining_time;
} process;

void round_robin() {
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

    int n, tq, time = 0, overhead;
    printf("Enter the number of processes you want: ");
    scanf("%d", &n);
    int ft[n], tat[n], wt[n], rft[n];
    process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time for process %d: ", i);
        scanf("%d", &p[i].arrival);
        p[i].process = i;
        printf("Enter the burst time for process %d: ", i);
        scanf("%d", &p[i].burst);
        p[i].remaining_time = p[i].burst;
    }
    printf("Enter time quantum (in ms): ");
    scanf("%d", &tq);
    printf("Enter overhead: ");
    scanf("%d", &overhead);
    int i=0,completed=0;
    process temp;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(p[i].arrival>p[j].arrival){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    for(time;completed!=n;){
        if(p[i].arrival>time && p[i].remaining_time){
            printf("%d to %d is no process zone",time,p[i].arrival);
            fprintf(fp, "<div class='cell empty' style=\"width: %d%;\">No Process</div>\n", p[i].arrival);
            time+=p[i].arrival;
        }
        if(p[i].arrival<=time && p[i].remaining_time){
            if(p[i].remaining_time<=tq){
                completed++;
                fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">process %d</div>\n", p[i].process % 4,p[i].remaining_time,p[i].process);
                time+=p[i].remaining_time+overhead;
                fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">O</div>\n", 4,(overhead)*1);
                ft[i]=time;
                rft[i]=ft[i]-overhead;
                p[i].remaining_time=0;
            }
            else{
                time+=tq;
                p[i].remaining_time-=tq;
                fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">process %d</div>\n", p[i].process % 4,tq,p[i].process);
                for (int j = (i + 1) % n; j != i; j = (j + 1) % n){
                    if(p[j].arrival<=time){
                        time+=overhead;
                        fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">O</div>\n", 4,(overhead)*1);
                        break;
                    }
                }
            }
        }
        i = (i+1)%n;
    }

    for (int i = 0; i < n; i++) {
        tat[i] = rft[i] - p[i].arrival;
    }
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - p[i].burst;
        if (wt[i] < 0) {
            ft[i] += -wt[i];
            tat[i] += -wt[i];
            wt[i] += -wt[i];
            printf("%d to %d is no process zone\n", ft[i - 1], p[i].arrival);
        }
    }

    printf("************Table************\n");
    printf("Process\t\tBT\tAT\tWT\tTAT\tFT\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("Process-%d\t%d\t%d\t%d\t%d\t%d\n", p[i].process, p[i].burst, p[i].arrival, wt[i], tat[i], rft[i]);
    }
    printf("-----------------------------------\n");
    fprintf(fp, "</section>\n<div class=\"row\">\n");
    int mine=-1;
    for(int i=0;i<n;i++){
        if(ft[i]>mine){
            mine=ft[i];
        }
    }
for(int i=0;i<=mine;i++){
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
