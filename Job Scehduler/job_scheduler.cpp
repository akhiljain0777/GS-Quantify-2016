#include<bits/stdc++.h>
using namespace std;

typedef long long unsigned int llu;
typedef unsigned int ui;


struct DESC{
    ui duration;
    llu proc_id,start=ULONG_LONG_MAX,end_;
    string origin,instr;
};

typedef struct DESC desc;

typedef pair<llu,desc> JOBS;

map < int, set < JOBS > > aq,nq;
vector < llu > assj;
map <string,map<int,set<JOBS> > > asq,nsq;

inline bool operator<(const desc& A,const desc& B){
    return(A.duration<B.duration);
}

bool compare(const JOBS& A,const JOBS& B){
    return(A.second.end_<B.second.end_);
}

ui ncpu;

void print(const JOBS& itq,int i){
    cout<<"job"<<" "<<itq.first<<" ";
    cout<<itq.second.proc_id<<" "<<itq.second.origin<<" ";
    cout<<itq.second.instr<<" "<<i<<" "<<itq.second.duration<<"\n";
}

void assign_(llu ts,llu k){
    llu i,f;

    f=ncpu;
    for(i=0;i<assj.size()&&f>0;i++){
        if(assj[i]>ts)f--;
    }

    k=min(k,f);
    set<JOBS>::iterator it;
    for(i=100;i>0&&k>0;i--){
        for(it=nq[i].begin();it!=nq[i].end()&&k>0;it++){
            if(it->second.duration>0)k--;
            JOBS temp_job;
            temp_job.first=it->first;
            temp_job.second.origin=(it->second).origin;
            temp_job.second.proc_id=(it->second).proc_id;
            temp_job.second.duration=(it->second).duration;
            temp_job.second.instr=(it->second).instr;
            temp_job.second.start=ts;
            temp_job.second.end_=ts+temp_job.second.duration;
            nsq[temp_job.second.origin][i].erase(nsq[temp_job.second.origin][i].begin());
            print(*it,i);
            asq[temp_job.second.origin][i].insert(temp_job);
            assj.push_back(temp_job.second.end_);
            aq[i].insert(temp_job);
        }
        nq[i].erase(nq[i].begin(),it);
    }
}


void query1(llu ts,llu k){
    int i;
    for(i=100;i>0&&k>0;i--){
        for(set<JOBS>::iterator it = aq[i].begin(); it != aq[i].end()&&it->first<=ts&&k>0;it++){
            if((it->second.start>ts)){
                print(*it,i);
                k--;
            }
        }
        for(set<JOBS>::iterator it = nq[i].begin(); it != nq[i].end()&&it->first<=ts&&k>0;it++){
            print(*it,i);
            k--;
        }
    }
}

void query2(llu ts,string orign){
    int i;
    for(i=100;i>0;i--){
        for(set<JOBS>::iterator it = asq[orign][i].begin(); it != asq[orign][i].end() && (*it).first<=ts;it++){
            if(it->second.start>ts){
                print(*it,i);
            }
        }
        for(set<JOBS>::iterator it = nsq[orign][i].begin(); it != nsq[orign][i].end() && (*it).first<=ts;it++){
            print(*it,i);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    char temp[10];
    cin>>temp;
    cin>>ncpu;
    while(cin>>temp){
        if(!strcmp(temp,"job")){
            JOBS tmp_job;
            int i;
            cin>>tmp_job.first>>tmp_job.second.proc_id;
            cin>>tmp_job.second.origin>>tmp_job.second.instr;
            cin>>i>>tmp_job.second.duration;
            nsq[tmp_job.second.origin][i].insert(tmp_job);
            nq[i].insert(tmp_job);
        }
        else if(!strcmp(temp,"assign")){
            llu ts,k;
            cin>>ts>>k;
            assign_(ts,k);
        }
        else if(!strcmp(temp,"query")){
            llu ts,k=0,i;
            string orig;
            cin>>ts>>orig;
            for(i=0;i<orig.length();i++){
                if(((int)orig[i]-'0')< 0 || ((int)orig[i]-'0')>9){
                    query2(ts,orig);
                    break;
                }
                k=k*10+((int)orig[i]-'0');
            }
            if(i==orig.length())query1(ts,k);
        }
    }
    return 0;
}
