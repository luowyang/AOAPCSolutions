#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
struct topic
{
    int t;
    queue<int> table;
};
map<int,topic> mpt;
struct person
{///pid is the name,k is the number of serv,st denote 上一次任务开始的时间
    int pid,k,time,st,level[25];///time denote 处理完当前请求的时间
    bool operator < (const person r)const
    {
        return st < r.st || (st == r.st && pid < r.pid);
    }
};
int n,m;///n denote the amount of types and m is the amount of person
int main()
{
    int cnt = 0;
    while(scanf("%d",&n) && n)
    {
        int time = INF,ans = 0;
        for(int i = 0 ; i < n ; i++ )
        {
            int tid,num,t0,dt;
            topic top;
            scanf("%d%d%d%d%d",&tid,&num,&t0,&top.t,&dt);
            time = min(time,t0);
            mpt[tid] = top;
            while(num--)
            {
                mpt[tid].table.push(t0);
                t0 += dt;
            }
        }
        scanf("%d",&m);
        vector<person> vec(m);
        for(int i = 0 ; i < m ; i++ )
        {
            scanf("%d%d",&vec[i].pid,&vec[i].k);
            for(int j = 0 ; j < vec[i].k ; j++ )
                scanf("%d",&vec[i].level[j]);
        }
        while(n)
        {
            int jump = INF;
            sort(vec.begin(),vec.end());
            for(int i = 0 ; i < m ; i++ )
            {
                int nexttime = INF;
                if(vec[i].time > time)
                    nexttime = vec[i].time;
                else
                {
                    for(int j = 0 ; j < vec[i].k ; j++ )
                    {
                        topic & x = mpt[vec[i].level[j]];
                        if(x.table.empty())
                            continue;
                        if(x.table.front() < nexttime)
                            nexttime = x.table.front();
                        if(x.table.front() <= time)
                        {
                            nexttime = time + x.t;
                            ans = max(ans,nexttime);
                            vec[i].st = time;
                            x.table.pop();
                            if(x.table.empty())
                                n--;
                            break;
                        }
                    }
                    vec[i].time = nexttime;
                }
                jump = min(jump,nexttime);
            }
            time = jump;
        }
        printf("Scenario %d: All requests are serviced within %d minutes.\n",++cnt,ans);
    }
    return 0;
}