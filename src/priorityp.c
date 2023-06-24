#include <stdio.h>

typedef struct priority{
    int arrival;
    int burst;
    int process;
    int priority;
    int remaining_time;
} priority;

void priority_p(){
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

    int n, time = 0, a = 0, smallest,overhead;
    int ad = 0;
    printf("Enter the number of processes you want: ");
    scanf("%d", &n);
    int ft[n], tat[n], wt[n], rft[n];
    priority p[n];

    for(int i = 0; i < n; i++){
        printf("Enter the arrival time for process %d: ", i);
        scanf("%d", &p[i].arrival);
        p[i].process = i;
        printf("Enter the Burst time for process %d: ", i);
        scanf("%d", &p[i].burst);
        p[i].remaining_time = p[i].burst;
        printf("Enter the Priority for process %d: ", i);
        scanf("%d", &p[i].priority);
    }
    printf("Enter Priority Order(Default: Ascending)(1: Descending & 0: Ascending): ");
    scanf("%d", &ad);
    printf("Enter Overhead: ");
    scanf("%d",&overhead);

    if(ad==0){
        for(time = 0; a != n; time++){
        smallest = -1;
        int min = 999999, min_burst = 999999;
        for(int i = 0; i < n; i++){
            if(p[i].arrival <= time && p[i].remaining_time > 0 && p[i].priority <= min){
                if(p[i].priority == min && p[i].burst < min_burst){
                    smallest = i;
                    min_burst = p[i].burst;
                }
                else {
                    smallest = i;
                    min_burst = p[i].burst;
                    min = p[i].priority;
                }
            }
        }
        if(smallest == -1){
            continue;
        }
        p[smallest].remaining_time--;
        fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">process %d</div>\n", p[smallest].process % 4,1,p[smallest].process);
        if (p[smallest].remaining_time == 0) {
            a++;
            time+=overhead;
            ft[smallest] = time + 1;
            rft[smallest]=ft[smallest]-overhead;
            fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">O</div>\n", 4,(overhead)*1);
        }
        }
    }
    else if(ad==1){
         for(time = 0; a != n; time++){
        smallest = -1;
        int min = -1, min_burst = 999999;
        for(int i = 0; i < n; i++){
            if(p[i].arrival <= time && p[i].remaining_time > 0 && p[i].priority >= min){
                if(p[i].priority == min && p[i].burst < min_burst){
                    smallest = i;
                    min_burst = p[i].burst;
                }
                else {
                    smallest = i;
                    min_burst = p[i].burst;
                    min = p[i].priority;
                }
            }

        }
        if(smallest == -1){
            continue;
        }
        p[smallest].remaining_time--;
        fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">process %d</div>\n", p[smallest].process % 4,1,p[smallest].process);
        if (p[smallest].remaining_time == 0) {
            a++;
            time+=overhead;
            ft[smallest] = time + 1;
            rft[smallest] = ft[smallest]-overhead;
            fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">O</div>\n", 4,(overhead)*1);
        }
        }
    }
    else{
        printf("enter the correct priority order..");
        return;
    }

    for(int i = 0; i < n; i++){
        tat[i] = ft[i] - p[i].arrival;
        wt[i] = tat[i] - p[i].burst;
        if(wt[i] < 0) {
            printf("%d to %d is no process zone for Process-%d\n", ft[i-1], p[i].arrival, p[i].process);
            tat[i] = ft[i] - p[i].arrival;
            wt[i] = 0;
        }
    }
    printf("************Table************\n");
    printf("Process\t\tBT\tAT\tWT\tTAT\tFT\tPrio\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < n; i++){
        printf("Process-%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].process, p[i].burst, p[i].arrival, wt[i], tat[i], ft[i], p[i].priority);
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