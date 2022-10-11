#include<stdio.h>
#include<limits.h>
struct Process{
int pid,at,bt,st,ct,rt,tat,wt;
};
int main()
{
int n;
printf("Enter number of Process : ");
scanf("%d",&n);
struct Process p[n];
int brt[n];
int is_complete[n];
printf("Enter arrival time and burst time : \nAT BT\n");
for(int i=0;i<n;i++){
scanf("%d%d",&p[i].at,&p[i].bt);
p[i].pid=i+1;
brt[i]=p[i].bt;
is_complete[i]=0;
}
int prev=0,curr_time=0,complete=0,idle_time=0;
int total_rt=0,total_tat=0,total_wt=0;
float avg_rt,avg_tat,avg_wt,cpu_utilization,throughput;
while(complete!=n){
int idx=-1,mn=INT_MAX;
for(int i=0;i<n;i++){
if(p[i].at<=curr_time && brt[i]!=0 && is_complete[i]==0){
if(brt[i]<mn){
mn=brt[i];
idx=i;
}
if(brt[i]==mn && p[i].at<p[idx].at){
idx=i;
mn=brt[i];
}
}
}
if(idx!=-1){
if(brt[idx]==p[idx].bt){
p[idx].st=curr_time;
idle_time+=p[idx].st-prev;
}
brt[idx]--;
curr_time++;
prev=curr_time;
if(brt[idx]==0){
p[idx].ct=curr_time;
p[idx].rt=p[idx].st-p[idx].at;
p[idx].tat=p[idx].ct-p[idx].at;
p[idx].wt=p[idx].tat-p[idx].bt;
total_rt+=p[idx].rt;
total_tat+=p[idx].tat;
total_wt+=p[idx].wt;
is_complete[idx]=1;
complete++;
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
printf("PId AT BT ST CT RT TAT WT\n");
for(int i=0;i<n;i++){
printf("%2d %2d %2d %2d %2d %2d %2d %2d\n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].rt,p[i].tat,p[i].wt);
}
printf("Average Response Time : %.2f\n",avg_rt);
printf("Average Turn around Time : %.2f\n",avg_tat);
printf("Average Waiting Time : %.2f\n",avg_wt);
printf("CPU Utilization : %.2f\n",cpu_utilization);
printf("ThroughPut : %.2f\n",throughput);
}