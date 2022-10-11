#include<stdio.h>
struct Process
{
int i,at,bt,st,ct,rt,tat,wt;
};
void swap(int* a,int* b)
{
int temp=*a;
*a=*b;
*b=temp;
}
void sort(struct Process p[],int n)
{
int i,j;
for(i=0;i<n-1;i++)
{
for(j=0;j<n-i-1;j++)
{
if(p[j].at>p[j+1].at)
{
swap(&p[j].at,&p[j+1].at);
swap(&p[j].i,&p[j+1].i);
swap(&p[j].bt,&p[j+1].bt);
}
}
}
}
int main()
{
int n;
printf("Enter no. of processes : ");
scanf("%d",&n);
struct Process p[n];
int rq[n];
printf("Enter Arrival time and Burst time of each process : \n");
printf("Process AT BT \n");
for(int i=0;i<n;i++)
{
printf("P%d : ",i+1);
scanf("%d%d",&p[i].at,&p[i].bt);
p[i].i=i+1;
}
sort(p,n);
int temp=p[0].at,idle=0;
for(int i=0;i<n;i++)
{
if(p[i].at>temp)
{
idle+=p[i].at-temp;
temp=p[i].at;
}
p[i].st=temp;
temp+=p[i].bt;
p[i].ct=temp;
}
float avgRt,avgTat,avgWt,cpu_utilization,throughput;
printf("\nProcess ST CT RT TAT WT\n");
for(int i=0;i<n;i++)
{
p[i].rt=p[i].st-p[i].at;
p[i].tat=p[i].ct-p[i].at;
p[i].wt=p[i].tat-p[i].bt;
avgRt+=p[i].rt;
avgTat+=p[i].tat;
avgWt+=p[i].wt;
printf("P%d %2d %2d %2d %2d %2d\n",p[i].i,p[i].st,p[i].ct,p[i].rt,p[i].tat,p[i].wt);
}
cpu_utilization=((float)(temp-idle)/temp)*100;
throughput=(float)n/temp;
printf("Idle Time : %d\nAverage RT : %.2f\nAverage TAT : %.2f\nAverage WT : %.2f\nCPU Utilization : %.2f\nThroughput : %.2f\n",idle,(avgRt/n),(avgTat/n),(avgWt/n),cpu_utilization,throughput);
}