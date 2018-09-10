#include<bits/stdc++.h>

using namespace std;

struct process
{
    int pid ;
    string processName;
    double burstTime;
    double timeTaken=0;
    int priority;
    double arrivalTime;
    double waitingTime=0;
    double turnAroundTime = waitingTime + burstTime;
    bool isComplete=false;
};



struct burstTimeComp
{
    bool operator()(const process i,const process j)
    {
         return (i.burstTime-i.timeTaken) > (j.burstTime-j.timeTaken);
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
         return i.priority > j.priority;
    }
};












void firstComeFirst(process *proc,int procNum)
{
    for(int i=0;i<procNum;i++)
    {
        if(i) cout<<"->";
        cout<<proc[i].processName;
        
        if(i)
        {
            if(proc[i-1].arrivalTime+ proc[i-1].turnAroundTime > proc[i].arrivalTime)
                proc[i].waitingTime = proc[i-1].arrivalTime+ proc[i-1].turnAroundTime - proc[i].arrivalTime;

            proc[i].turnAroundTime = proc[i].waitingTime + proc[i].burstTime;
        }

    }

}


void shortestJobFirst(process *proc,int procNum)
{
    long long i;
    int doneCount=0;
    int currPos=0;

    priority_queue<process, vector<process>, burstTimeComp > que;    
    


    for(i=0; doneCount!=procNum; i++ )
    {


        for(int curr = currPos; curr<procNum; curr++)
        {

            if(i == proc[curr].arrivalTime)
            {
                que.push(proc[curr]);   
                currPos= curr+1;
            }
            else break;
        }  

        if(!que.empty())
        {

            process currProcess = que.top();
            que.pop();
            proc[currProcess.pid].timeTaken++;
            proc[currProcess.pid].waitingTime--;

    
            for(int curr=currPos-1; curr>=0; curr--)
            {
                if(!proc[curr].isComplete)
                    proc[curr].waitingTime++;
            }
           


            if(proc[currProcess.pid].burstTime == proc[currProcess.pid].timeTaken)
            {
                proc[currProcess.pid].isComplete = true;
                proc[currProcess.pid].turnAroundTime = proc[currProcess.pid].waitingTime + proc[currProcess.pid].burstTime;


                if(doneCount) cout<<"->";
                cout<<proc[currProcess.pid].processName;

                doneCount++;
               
            }
            else que.push(proc[currProcess.pid]);
        }
    }
   
}


void roundRobin(process *proc,int procNum)
{
    long long i;
    int roundTime, roundTimeSpent=0;
    int doneCount=0;
    int currPos=0;

    queue<process> que;
        
    cout<<"Enter Round Time: ";
    cin>>roundTime;
    cout<<endl<<endl;

    for(i=0; doneCount!=procNum; i++ )
    {


        for(int curr = currPos; curr<procNum; curr++)
        {

            if(i == proc[curr].arrivalTime)
            {
                que.push(proc[curr]);   
                currPos= curr+1;
            }
            else break;
        }  

        if(!que.empty())
        {

            process currProcess = que.front();
            proc[currProcess.pid].timeTaken++;
            proc[currProcess.pid].waitingTime--;

    
            for(int curr=currPos-1; curr>=0; curr--)
            {
                if(!proc[curr].isComplete)
                    proc[curr].waitingTime++;
            }
           


            if(proc[currProcess.pid].burstTime == proc[currProcess.pid].timeTaken)
            {
                proc[currProcess.pid].isComplete = true;
                proc[currProcess.pid].turnAroundTime = proc[currProcess.pid].waitingTime + proc[currProcess.pid].burstTime;
                roundTimeSpent=-1;

                que.pop();
                proc[currProcess.pid].turnAroundTime = proc[currProcess.pid].waitingTime + proc[currProcess.pid].burstTime;
    

                if(doneCount) cout<<"->";
                cout<<proc[currProcess.pid].processName;

                doneCount++;
               
            }
            else if(roundTimeSpent == roundTime)
            {
                roundTimeSpent=-1;
                que.pop();
                que.push(proc[currProcess.pid]);
            }
            

            roundTimeSpent++;

            
        }
   
    }
}





void priority(process *proc,int procNum)
{
    long long i;
    int doneCount=0;
    int currPos=0;

    priority_queue<process, vector<process>, priorityComp > que;
        
    cout<<"Enter process priority: "<<endl;
    for(int i=0;i<procNum;i++)
        cin>>proc[i].priority;

    for(i=0; doneCount!=procNum; i++ )
    {


        for(int curr = currPos; curr<procNum; curr++)
        {

            if(i == proc[curr].arrivalTime)
            {
                que.push(proc[curr]);   
                currPos= curr+1;
            }
            else break;
        }  

        if(!que.empty())
        {

            process currProcess = que.top();
            que.pop();
            proc[currProcess.pid].timeTaken++;
            proc[currProcess.pid].waitingTime--;

            for(int curr=currPos-1; curr>=0; curr--)
            {
                if(!proc[curr].isComplete)
                    proc[curr].waitingTime++;
            }

            if(proc[currProcess.pid].burstTime == proc[currProcess.pid].timeTaken)
            {
                proc[currProcess.pid].isComplete = true;
                proc[currProcess.pid].turnAroundTime = proc[currProcess.pid].waitingTime + proc[currProcess.pid].burstTime;

                if(doneCount) cout<<"->";
                cout<<proc[currProcess.pid].processName;

                doneCount++;
               
            }
            else que.push(proc[currProcess.pid]);
        }
    }
}











void showProcessInfo(process *proc, int n)
{

    printf("%-15s%-15s%-15s\n\n", "Process Name", "Waiting Time", "Turn-around Time");
    for(int i=0;i<n;i++)
        cout<< proc[i].processName <<"\t\t" << proc[i].waitingTime <<"\t\t"<< proc[i].turnAroundTime<<endl;
}





int main()
{
    process *proc;
    int n;
    cout<<"Number of process: ";
    cin>>n;

    proc = new process[n];
    for(int i=0;i<n;i++)
    {
        cin>>proc[i].processName>>proc[i].arrivalTime>>proc[i].burstTime;\
        
    }
    cout<<endl<<endl<<endl;

    sort(proc, proc+n, arrivalComp() );
    for(int i=0;i<n;i++)
        proc[i].pid = i;

    //firstComeFirst(proc,n);
    //shortestJobFirst(proc, n);
    //roundRobin(proc,n);
    priority(proc,n);
   
    cout<<endl<<endl;

    showProcessInfo(proc, n);

    return 0;
}


