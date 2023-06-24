#include <stdio.h>

typedef struct sjf{
    int arrival;
    int burst;
    int process;
    int remaining_time;
} sjf;

void srtf() {
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

    int n, time = 0, a = 0, smallest, overhead;
    printf("Enter the number of processes you want: ");
    scanf("%d", &n);
    int ft[n], tat[n], wt[n], rft[n];
    sjf s[n];
    for(int i = 0; i < n; i++){
        printf("Enter the arrival time for process %d: ", i);
        scanf("%d", &s[i].arrival);
        s[i].process = i;
        printf("Enter the Burn time for process %d: ", i);
        scanf("%d", &s[i].burst);
        s[i].remaining_time = s[i].burst;
    }
    printf("Enter Overhead: ");
    scanf("%d", &overhead);
int d=-1;
    for(time = 0; a != n; time++){
        smallest = -1;
        int min_rm = 999999;
        for(int i = 0; i < n; i++){
            if(s[i].remaining_time!=0 && s[i].arrival <= time && s[i].remaining_time < min_rm){
                smallest = i;
                min_rm = s[i].remaining_time;
            }}
            if(smallest == -1){
            fprintf(fp, "<div class='cell empty' style=\"width: %d%;\">No Process</div>\n", 1);
            d=-1;
            continue;
            }
            s[smallest].remaining_time--;
            if(d!=smallest && d!=-1){
            time+=overhead;
            fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">O</div>\n", 4,(overhead)*1);
            fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">process %d</div>\n", s[smallest].process % 4,1,s[smallest].process);
            }
            else{
            fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">process %d</div>\n", s[smallest].process % 4,1,s[smallest].process);
            }
            d=smallest;
            if(s[smallest].remaining_time == 0){
            a++;
            ft[smallest] = time+1;
            rft[smallest] = ft[smallest] - overhead;
            }
        }
    for(int i = 0; i < n; i++){
        tat[i] = ft[i] - s[i].arrival;
    }
    for(int i = 0; i < n; i++){
        wt[i] = tat[i] - s[i].burst;
    }

    printf("************Table************\n");
    printf("Process\t\tBT\tAT\tWT\tTAT\tFT\n");
    printf("-----------------------------------\n");
    for(int i = 0; i < n; i++){
        printf("Process-%d\t%d\t%d\t%d\t%d\t%d\n", s[i].process, s[i].burst, s[i].arrival, wt[i], tat[i], ft[i]);
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