#include<stdio.h>
struct Process{
int pid,at,bt,st,ct,rt,tat,wt;
};
void swap(int *a,int *b){
int temp=*a;
*a=*b;
*b=temp;
}
void sort(struct Process p[],int brt[],int n,int comparator){
int i,j;
for(i=0;i<n-i-1;i++){
for(j=0;j<n-i-1;j++){
if(comparator==1 && p[j].at>p[j+1].at){
swap(&p[j].at,&p[j+1].at);
swap(&p[j].bt,&p[j+1].bt);
swap(&p[j].pid,&p[j+1].pid);
swap(&brt[j],&brt[j+1]);
}
else if(comparator==0 && p[j].pid>p[j+1].pid){
swap(&p[j].at,&p[j+1].at);
swap(&p[j].bt,&p[j+1].bt);
swap(&p[j].pid,&p[j+1].pid);
swap(&p[j].st,&p[j+1].st);
swap(&p[j].ct,&p[j+1].ct);
swap(&p[j].rt,&p[j+1].rt);
swap(&p[j].tat,&p[j+1].tat);
swap(&p[j].wt,&p[j+1].wt);
}
}
}
}
void push(int q[],int *front,int *rear,int val){
if(*front==-1)
*front=0;
q[++(*rear)]=val;
}
int fronte(int q[],int front,int rear){
return q[front];
}
void dequeue(int q[],int *front,int *rear){
if((*front)==(*rear)){
*front=-1;
*rear=-1;
}
else
(*front)++;
}
int empty(int q[],int front,int rear){
if(front==-1 && rear==-1)
return 1;
return 0;
}
int main()
{
int n;
printf("Enter number of processes : ");
scanf("%d",&n);
struct Process p[n];
int queue[50];
int brt[n],mark[n];
int front=-1,rear=-1,complete=0,prev=0,tq;
int curr_time=0,idle_time=0,total_rt=0,total_tat=0,total_wt=0;
float avg_rt,avg_tat,avg_wt,cpu_utilization,throughput;
printf("Enter arrival time and burst time of each process :\nAT BT\n");
for(int i=0;i<n;i++){
scanf("%d%d",&p[i].at,&p[i].bt);
p[i].pid=i+1;
brt[i]=p[i].bt;
mark[i]=0;
}
sort(p,brt,n,1);
printf("Enter time quanta size : ");
scanf("%d",&tq);
push(queue,&front,&rear,0);
while(complete!=n){
int idx=fronte(queue,front,rear);
dequeue(queue,&front,&rear);
if(brt[idx]==p[idx].bt){
if(curr_time>p[idx].at)
p[idx].st=curr_time;
else
p[idx].st=p[idx].at;
idle_time+=p[idx].st-prev;
curr_time=p[idx].st;
}
if(brt[idx]>tq){
curr_time+=tq;
brt[idx]-=tq;
prev=curr_time;
}
else{
curr_time+=brt[idx];
brt[idx]=0;
p[idx].ct=curr_time;
p[idx].rt=p[idx].st-p[idx].at;
p[idx].tat=p[idx].ct-p[idx].at;
p[idx].wt=p[idx].tat-p[idx].bt;
total_rt+=p[idx].rt;
total_tat+=p[idx].tat;
total_wt+=p[idx].wt;
complete++;
}
for(int i=1;i<n;i++){
if(brt[i]>0 && p[i].at<=curr_time && mark[i]==0){
push(queue,&front,&rear,i);
mark[i]=1;
}
}
if(brt[idx]>0)
push(queue,&front,&rear,idx);
if(empty(queue,front,rear)==1){
for(int i=1;i<n;i++){
if(brt[i]>0)
{push(queue,&front,&rear,i);
mark[i]=1;
break;}
}
}
}
sort(p,brt,n,0);
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