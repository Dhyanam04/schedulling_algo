#include <stdio.h>

typedef struct fcfs{
        int arrival;
        int burst;
        int process;
    }fcfs;

void fcfs_(){
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

    int n,overhead;
    //fcfs
    printf("Enter the number of processes you want: ");
    scanf("%d",&n);
    int ft[n],tat[n],wt[n],rft[n];
    fcfs f[n];
    for(int i=0;i<n;i++){
        printf("Enter the arrival time for process %d: ",i);
        scanf("%d",&f[i].arrival);
        f[i].process=i;
        printf("Enter the Burst time for process %d: ",i);
        scanf("%d",&f[i].burst);
    }

    printf("Enter Overhead: ");
    scanf("%d",&overhead);
    {
    struct fcfs temp;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(f[i].arrival>f[j].arrival){
                temp=f[i];
                f[i]=f[j];
                f[j]=temp;
            }
        }
    }
}

    if(f[0].arrival>0){
        printf("0 to %d is no process zone\n",f[0].arrival);
        fprintf(fp, "<div class='cell empty' style=\"width: %d%;\">No Process</div>\n", f[0].arrival);
    }
    int sum=f[0].arrival;
    for(int i=0;i<n;i++){
        ft[i]=f[i].burst+sum+overhead;
        rft[i]=ft[i]-overhead;
        sum=ft[i];
    }
    for(int i=0;i<n;i++){
        tat[i]=rft[i]-f[i].arrival;
    }

    for(int i=0;i<n;i++){
        wt[i]=tat[i]-f[i].burst;
        if(wt[i]<0){
            ft[i]+=-(wt[i]);
            tat[i]+=-(wt[i]);
            wt[i]+=-(wt[i]);
            printf("%d to %d is no process zone\n",ft[i-1],f[i].arrival);
        }
    }

    printf("************Table************\n");
    printf("Process\t\tBT\tAT\tWT\tTAT\tFT\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process-%d\t%d\t%d\t%d\t%d\t%d\n",f[i].process,f[i].burst,f[i].arrival,wt[i],tat[i],ft[i]-overhead);
    }
    printf("-----------------------------------\n");

int current_time = f[0].arrival;
for (int i = 0; i < n; i++) {
    int start_time = current_time;
    current_time = ft[i];
    int empty_time = f[i].arrival - start_time;
    if (empty_time > 0) {
        fprintf(fp, "<div class='cell empty'  style=\"width: %d%;\">No Process</div>\n", (empty_time)*1);
    }
    fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">process %d</div>\n", f[i].process % 4,f[i].burst*1,f[i].process);
    if(i!=n-1){
    fprintf(fp, "<div class='cell p%d'  style=\"width: %d%;\">O</div>\n", 4,(overhead)*1);}
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
