#include<bits/stdc++.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<mutex>
#include<sys/stat.h>

using namespace std;
typedef unsigned long long ll;
FILE * fout;
//number of total answers.
ll number = 0;
// maybe we can just use int because we had used the mapping mKey?
map<ll, int> mKey;
//trace is to record all node passing by
//recording times and money just for the convient output
class ArcNode{
    public:
        ll dstId;
        ll trace[4];
        ll times[4];
        float money[4];
        ArcNode* nextdst{nullptr};
    ArcNode(){
        this->dstId = 0;
        this->trace[0] = 0;
        nextdst = nullptr;
    }
    ArcNode(ll inits, ll initd, ll initt, float inita){
        this->dstId = initd;
        this->trace[0] = 0;
        add_trace(inits, initt, inita);
        nextdst = nullptr;
    }
    void add_trace(ll t,ll tim, float amo){
        ll trn = this->trace[0];
        trn =trn+1;
        this->trace[0] = trn;
        this->trace[trn] = t;
        this->times[trn] = tim;
        this->money[trn] = amo;
    }
    bool check(ll t){
        for(unsigned int i=1; i<=this->trace[0]; i++){
            if(this->trace[i]==t)
                return true;
        }
        return false;
    }
};


typedef struct Node{
    ll src;
    ArcNode* nextdst;
};
Node nodeList[1000050],node2[1000050],node3[1000050]; 

char* mmapread(char* path, ll &len) {
    ll fd = open(path, O_RDONLY);
    if(fd == -1) {
        fd = open(path, O_RDWR|O_CREAT, 0666);
        if(fd == -1){
            exit(-1);
        }
    }
    len = lseek(fd,0,SEEK_END); 
    char* buf = (char*)mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return buf;
}
// read all node 
// init nodeList and backList 
// node length == nodeList[0].src
// node from 1 to length
// map is mKey which is transform longlong to nodeid for nodeList.
void readin1(char* inputFilePath1) {
    int t = 0;
    ll num = 0;
    ll len1 =0;
    nodeList[0].src = 0;
    char* buf = mmapread(inputFilePath1, len1);
    for (char* p = buf ; *p && p-buf < len1;) {
        while (*p && *p>='0' && *p<='9')
            num = num*10 + (*(p++)-'0');
        p++;
        //printf("%lld\n", num);
        if(num>0){
            nodeList[0].src++;
            t=nodeList[0].src;
            mKey[num]=t;
            nodeList[t].src=num;nodeList[t].nextdst=nullptr;
            node2[t].src = num; node2[t].nextdst = nullptr;
            num=0;
        }
    }
    munmap(buf,len1);
}

// read all edge
// add edge to nodeList and backList
void readin2(char* inputFilePath2) {
    ll num = 0;
    ll src = 0;
    ll dst = 0;
    ll tim = 0;
    ll len2 = 0;
    float amo = 0;
    char* buf = mmapread(inputFilePath2, len2);
    for (char* p = buf ; *p && p-buf < len2 ; ) {
        while (*p && *p>='0' && *p<='9') num = num*10 + (*(p++)-'0'); p++;src = num;num = 0;

        while (*p && *p>='0' && *p<='9') num = num*10 + (*(p++)-'0'); p++;dst = num;num = 0;

        while (*p && *p>='0' && *p<='9') num = num*10 + (*(p++)-'0'); p++;tim = num;num = 0;

        while (*p && *p>='0' && *p<='9') num = num*10 + (*(p++)-'0'); p++;amo = num;num = 0;
        ll ten=1;
        while (*p && *p>='0' && *p<='9') num = num*10 + (*(p++)-'0'), ten = ten * 10; p++;amo = amo + (float)num/ten;num = 0;
        //maybe we can try the adj Maxtrix
        int head = 0;
        int tail = 0;
        head = mKey[src];
        tail = mKey[dst];
        ArcNode *q = new ArcNode(head, tail, tim, amo);
        q->nextdst = nodeList[head].nextdst;nodeList[head].nextdst = q;
        q = nullptr;delete q;q = NULL;
    }
    munmap(buf,len2);
}

// calculate node2
void dfs_2() {
    for (unsigned int i=1; i<=nodeList[0].src; i++) {
    ArcNode *q;
    Node head=nodeList[i];
        q = head.nextdst;
        while (q!=nullptr) {
            ArcNode *d;
            Node dhead = nodeList[q->dstId];
            d = dhead.nextdst;
            while(d!=nullptr) {
                if(d->dstId!=q->trace[1] && d->times[1]>q->times[1] && d->money[1] > q->money[1]*0.9 && d->money[1] < q->money[1]*1.1) {
                    ArcNode *o = new ArcNode(q->trace[1], d->dstId, q->times[1], q->money[1]);
                    o->add_trace(d->trace[1],d->times[1], d->money[1]);
                    o->nextdst = node2[q->trace[1]].nextdst; node2[q->trace[1]].nextdst = o;
                    o = nullptr; delete o; o = NULL;
                }
                d = d->nextdst;
            }
            d = nullptr; delete d; d= NULL;
            q = q->nextdst;
        }
    q = nullptr; delete q; q = NULL;
    }
}
 
// calculate node3
void dfs_3() {
    for (unsigned int i=1; i<=nodeList[0].src; i++) {
    ArcNode *q;
    Node head=nodeList[i];
        q = head.nextdst;
        while (q!=nullptr) {
            ArcNode *d;
            Node dhead = node2[q->dstId];
            d = dhead.nextdst;
            while(d!=nullptr) {                
                if(d->dstId!=q->trace[1] && d->times[1]>q->times[1] && d->money[1] > q->money[1]*0.9 && d->money[1] < q->money[1]*1.1) {
                    ArcNode *o = new ArcNode(q->trace[1], d->dstId, q->times[1], q->money[1]);
                    o->add_trace(d->trace[1],d->times[1], d->money[1]);
                    o->add_trace(d->trace[2],d->times[2], d->money[2]);
                    o->nextdst = node3[q->trace[1]].nextdst; node3[q->trace[1]].nextdst = o;
                    o = nullptr; delete o; o = NULL;
                }
                d = d->nextdst;
            }
            d = nullptr; delete d; d= NULL;
            q = q->nextdst;
        }
    q = nullptr; delete q; q = NULL;
    }

}

//find two links from l1 and l2, link them,  length equal lens, write into l3.
//if find right circle ,gooooood! 
void dfs_com(Node* l1, Node* l2) {
    for(unsigned int i=1; i<= nodeList[0].src; i++) {
        ArcNode* q;
        Node head = l1[i];
        q = head.nextdst;
        while(q!=nullptr) {
            ArcNode* d;
            Node dhead = l2[q->dstId];
            d = dhead.nextdst;
            while(d!=nullptr) {
                bool flag = true;//check same vercex
                for(unsigned int i=1; i<=d->trace[0]; i++){
                    if(q->check(d->trace[i])){
                        flag = false;
                        break;
                    }
                }
                if(flag){
                            if(d->dstId == q->trace[1]){
                                if (d->times[1]>q->times[q->trace[0]] && d->money[1] > q->money[q->trace[0]]*0.9 && d->money[1] < q->money[q->trace[0]]*1.1){
                                    if (q->trace[0]+d->trace[0]>=3 && q->trace[0]+d->trace[0]<=6){//right circle
                                        number +=1;

                                        for(unsigned int i=1; i<=q->trace[0]; i++) {
                                            std::fprintf(fout, "(%lld)-[%lld,%.2f]->",nodeList[q->trace[i]].src,q->times[i],q->money[i]);
                                        }
                                        for(unsigned int i=1; i<=d->trace[0]; i++) {
                                            std::fprintf(fout, "(%lld)-[%lld,%.2f]->",nodeList[d->trace[i]].src,d->times[i],d->money[i]);
                                        }
                                        std::fprintf(fout, "(%lld)\n",nodeList[q->trace[1]].src);
                                        
                                    } 
                                }
                            }
                }
                d = d->nextdst;
            }
            d = nullptr; delete d; d = NULL;
            q = q->nextdst;
        }
        q = nullptr; delete q; q = NULL;
    }

}

void deep(int dep) {
    if(dep==3) {
        dfs_com(nodeList, node2);
    }
    if(dep==4) {
        dfs_com(node2, node2);
    }
    if(dep==5) {
        dfs_com(node2, node3);
    }
    if(dep==6) {
        dfs_com(node3, node3);
    }
}

void dfs_method() {
    dfs_2();
    dfs_3();
    deep(3);
    deep(4);
    deep(5);
    deep(6);

}

int main(){
    //baseline1:
    
    char* inputFilePath1 = (char*)"/home/kaos/Desktop/C++/test/dataset/account.csv";
    char* inputFilePath2 = (char*)"/home/kaos/Desktop/C++/test/dataset/transfer.csv";
    
    /*
    char* inputFilePath1 = (char*)"/home/kaos/Desktop/C++/test/dataset/testaccount.csv";
    char* inputFilePath2 = (char*)"/home/kaos/Desktop/C++/test/dataset/testtransfer.csv";
    */
    char* outputFilePath = (char*)"/home/kaos/Desktop/C++/test/result.csv"; 

    readin1(inputFilePath1);
    readin2(inputFilePath2);

    fout = fopen(outputFilePath,"w+");

    dfs_method();

    fclose(fout);

    return 0;
}