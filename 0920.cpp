#include<bits/stdc++.h>

using namespace std;

struct process
{
    string processName;
    double burstTime;
    double timeTaken=0;
    int priority;
    double arrivalTime;
    double waitingTime=0;
    double turnAroundTime = waitingTime + burstTime;
    bool complete=false;
};



struct burstTimeComp
{
    bool operator()(const process i,const process j)
    {
         return i.burstTime < j.burstTime;
    }
};


struct arrivalComp
{
    bool operator()(const process i, const process j)
    {
         return i.arrivalTime < j.arrivalTime;  
    }
};

struct priorityComp
{
    bool operator()(const process i, const process j)
    {
         return i.priority < j.priority;
    }
};








void schedulingJob(process *proc,int procNum, priority_queue<process, vector<process>, burstTimeComp > &pQ)
{
    long long i;
    int doneCount=0;
    int currPos=0;


     for(i=0; doneCount!=procNum; i++ )
    {


        for(int curr = currPos; curr<procNum; curr++)
        {

            if(i == proc[curr].arrivalTime)
            {
                pQ.push(proc[curr]);   
                currPos= curr+1;
            }
            else break;
        }  

        if(!pQ.empty())
        {

            process currProcess = pQ.top();
            pQ.pop();
            currProcess.timeTaken++;
            currProcess.waitingTime--;

            for(int curr=currPos-1; curr>=0; curr--)
            {
                if(!proc[curr].complete)
                    proc[curr].waitingTime++;
            }

            if(currProcess.burstTime == currProcess.timeTaken)
            {
                currProcess.complete = true;

                if(doneCount) cout<<"->";
                cout<<currProcess.processName<<endl;

                doneCount++;
               
            }
            else pQ.push(currProcess);
        }
    }
}






void firstComeFirst(process *proc,int procNum)
{
    for(int i=0;i<procNum;i++)
    {
        if(i) cout<<"->";
        cout<<proc[i].processName<<endl;
        
        if(i)
        {
            if(proc[i-1].arrivalTime+ proc[i-1].turnAroundTime > proc[i].arrivalTime)
                proc[i].waitingTime = proc[i-1].arrivalTime+ proc[i-1].turnAroundTime - proc[i].arrivalTime;
        }

    }

}


void shortestJobFirst(process *proc,int procNum)
{
    
    priority_queue<process, vector<process>, burstTimeComp > pQ;    
    schedulingJob(proc,procNum,pQ);

}


void roundRobin(process *proc,int procNum)
{
    int doneNum=0;
    int time;
    cin>>time;

    while(true)
    {
        if(doneNum==procNum) break;
        for(int i=0;i<procNum;i++)
        {
            if(proc[i].timeTaken<proc[i].burstTime)
                proc[i].timeTaken+=time;
            else
            {
                if(!proc[i].complete)
                {
                    cout<<proc[i].processName<<endl;
                    doneNum++;
                }
                proc[i].complete=true;
            }
        }
    }
}





void priority(process *proc,int procNum)
{

    priority_queue<process, vector<process>, priorityComp > pQ;
    schedulingJob(proc,procNum,pQ);
}











void showProcessInfo(process *proc, int n)
{
    printf("%-12s%-12s%-12s\n\n", "Process Name", "Waiting Time", "Turn-around Time");

    for(int i=0;i<n;i++)
        printf("%-12s%-12d%-12d\n", proc[i].processName, proc[i].waitingTime, proc[i].turnAroundTime);
}





int main()
{
    process *proc;
    int n;
    cout<<"Number of process: ";
    cin>>n;

    proc = new process[n];
    for(int i=0;i<n;i++)
        cin>>proc[i].processName>>proc[i].arrivalTime>>proc[i].burstTime;

    sort(proc,proc+n, arrivalComp);

    //firstComeFirst(proc,n);
    shortestJobFirst(proc,n);
    //roundRobin(proc,n);
    //priority(proc,n);

    showProcessInfo(proc,n);

    return 0;
}


