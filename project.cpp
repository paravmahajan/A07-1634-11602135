#include<iostream>
#include<stdio.h>
#include<queue>
using namespace std;
#define MAX 1000
#define TIME_QUANTUM 2 
int temp[MAX],arr_t[MAX],bur_t[MAX],prior[MAX],Resp_t[MAX],ft[MAX],fe[MAX],fe_flag[MAX],p_id[MAX],tms,qt[MAX];
queue<int> q;  
void RR()
{
     if(!q.empty())
      {
        if(Resp_t[q.front()]>0 && qt[q.front()]<4)
        {
                qt[q.front()]++;
                Resp_t[q.front()]--;
                if(Resp_t[q.front()]==0)
                {
                ft[q.front()]=tms+1;
                q.pop();
                }
                if(Resp_t[q.front()]!=0 && qt[q.front()]==4)
                {
                qt[q.front()]=0;
                q.push(q.front());
                q.pop();
                }
            }
      }
}
int main()
{
    int i=0,n=0,smallest=0,last_smallest=-1,min,sum=0,large=0;
    printf("Enter the Number of Processes:\n");
    scanf("%d",&n);
    int avg;
     int wait=0;
    for(i=0;i<n;i++)
    {       printf("Enter the process id here:\n");
            scanf("%d",&p_id[i]);
            printf("Enter the arrival time of process id %d :\n",p_id[i]);
            scanf("%d",&arr_t[i]);
            printf("Enter the burst time of process id %d :\n",p_id[i]);
            scanf("%d",&bur_t[i]);
            printf("Enter the priority time of process id %d :\n",p_id[i]);
            scanf("%d",&prior[i]);          
            if(arr_t[i]>large)
                large=arr_t[i];
              sum+=bur_t[i];
              Resp_t[i]=bur_t[i];             
        printf("\n-----------------------------------------------------\n");
    }
    min=MAX;
    for(tms=0;!q.empty() || tms<=sum+large ;tms++)
    {
      min=MAX;
      smallest=-1;
      for(i=0;i<n;i++)
      {
        if(arr_t[i]<=tms && prior[i]<min && Resp_t[i]>0 && !temp[i])
        {
            min=prior[i];
                smallest=i;
            }
      }
      if(smallest==-1 && !q.empty())
      {
        if(last_smallest !=-1 && Resp_t[last_smallest]==0)
        {
            ft[last_smallest]=tms;
                temp[last_smallest]=1;
            }
            last_smallest=-1;
            RR();
            continue;
      }
      else if(smallest!=-1 && !q.empty() && last_smallest==-1)
      {
        if(qt[q.front()]<=4 && qt[q.front()]>0)
        {
            q.push(q.front());
            q.pop();
            }
      }
      if(smallest!=-1 && !fe_flag[smallest])
      {
        fe[smallest]=tms-arr_t[smallest];
        fe_flag[smallest]=1;
      }
      if( smallest!=last_smallest && last_smallest!=-1 && !temp[last_smallest])
      {
        q.push(last_smallest);
        temp[last_smallest]=1;
      }
      if(smallest !=-1)
        Resp_t[smallest]--;
     
      if((smallest !=-1) && ((Resp_t[smallest]==0) ||(bur_t[smallest]-Resp_t[smallest])==TIME_QUANTUM))
      {
        if((bur_t[smallest]-Resp_t[smallest])==TIME_QUANTUM && Resp_t[smallest]!=0)
        {
            temp[smallest]=1;
            q.push(smallest);
            }
        else if(smallest!=-1)
        {
                ft[smallest]=tms+1;
                temp[smallest]=1;
            }
      }
      last_smallest=smallest;
    }
   for(int i=0;i<n;i++)
    
   printf("\n  Process Id: %d | Waiting Time : %d | Finish Time : %d | TurnAround Time : %d\n",p_id[i],fe[i],ft[i],ft[i]-bur_t[i]-arr_t[i]);
   }
