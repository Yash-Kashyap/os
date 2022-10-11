#include<stdio.h>
struct Process{
int pid,at,bt,st,ct,rt,tat,wt,pri;
};
int main()
{
int n;
printf("Enter number of processes : ");
scanf("%d",&n);
struct Process p[n];
int brt[n];
int idle_time=0,completed=0,total_rt=0,total_tat=0,total_wt=0;
float avg_rt,avg_tat,avg_wt,cpu_utilization,throughput;
printf("Enter arrival time, burst time and priority of each process : \nAT BT P\n");
for(int i=0;i<n;i++){
scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pri);
p[i].pid=i+1;
brt[i]=p[i].bt;
}
int curr_time=0,prev=0;
while(completed!=n) {
int mx=-1,idx=-1;
for(int i=0;i<n;i++) {
if(brt[i]>0 && p[i].at<=curr_time && p[i].pri>mx){
mx=p[i].pri;
idx=i;
}
if(p[i].pri==mx && p[i].at<p[idx].at){
idx=i;
}
}
if(idx!=-1){
if(brt[idx]==p[idx].bt) {
p[idx].st=curr_time;
idle_time+=p[idx].st-prev;
}
curr_time++;
brt[idx]--;
prev=curr_time;
if(brt[idx]==0){
p[idx].ct=curr_time;
completed++;
p[idx].rt=p[idx].st-p[idx].at;
p[idx].tat=p[idx].ct-p[idx].at;
p[idx].wt=p[idx].tat-p[idx].bt;
total_rt+=p[idx].rt;
total_tat+=p[idx].tat;
total_wt+=p[idx].wt;
}
}
else
curr_time++;
}
avg_rt=(float)total_rt/n;
avg_tat=(float)total_tat/n;
avg_wt=(float)total_wt/n;
cpu_utilization=(float)(curr_time-idle_time)/curr_time;
throughput=(float) n/ curr_time;
printf("PId AT BT Pri ST CT RT TAT WT\n");
for(int i=0;i<n;i++){
printf("%2d %2d %2d %2d %2d %2d %2d %2d %2d\n",p[i].pid,p[i].at,p[i].bt,p[i].pri,p[i].st,p[i].ct,p[i].rt,p[i].tat,p[i].wt);
}
printf("Average Response Time : %.2f\n",avg_rt);
printf("Average Turn around Time : %.2f\n",avg_tat);
printf("Average Waiting Time : %.2f\n",avg_wt);
printf("CPU Utilization : %.2f\n",cpu_utilization);
printf("ThroughPut : %.2f\n",throughput);
}