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


bool burstSort (const process i,const process j)
{
     return i.burstTime < j.burstTime;
}

bool arrivalSort (const process i, const process j)
{
     return i.arrivalTime < j.arrivalTime;
}

struct comp
{
    bool operator()(const process i, const process j)
    {
         return i.priority < j.priority;
    }
};






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
    sort(proc,proc+procNum,burstSort);
    for(int i=0;i<procNum;i++)
    {
        cout<<proc[i].processName<<endl;
    }
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
    long long i;
    int doneCount=0;
    int currPos=0;

    priority_queue<process, vector<process>, comp > pQ;

    for(int i=0;i<procNum;i++)
    {
        cin>>proc[i].priority;
    }   



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




int main()
{
    process *proc;
    int n;
    cout<<"Number of process: ";
    cin>>n;

    proc = new process[n];
    for(int i=0;i<n;i++)
        cin>>proc[i].processName>>proc[i].arrivalTime>>proc[i].burstTime;

    sort(proc,proc+n, arrivalSort);

    //firstComeFirst(proc,n);
    //shortestJobFirst(proc,n);
    //roundRobin(proc,n);
    //priority(proc,n);

    return 0;
}
