#include<iostream>
#include<map>
#include<vector>
#include<set>

using namespace std;

vector<map<int,int>> ZT; // 一个区上是否有某应用
vector<int> Z; // 每个节点对应一个区
vector<int> C; // 每个节点有几个任务
vector<map<int,int>> V; // 对于每一个节点 上面是否有某应用

bool check1(int index,int nodeQh,int taskQh){ // 判断该节点是否可以作为结果
    if((nodeQh==0 || Z[index]==nodeQh) && (taskQh==0 || ZT[Z[index]][taskQh]==1)){return true;}
    return false;
}

bool check2(int index,int AntiQh){
    if(V[index][AntiQh]==0){return true;}
    return false;
}

int main(){
    int n,m,i,temp,k,j,app,nodeQh,taskQh,AntiQh,AlwAnti,l,tempRes,flag,flag1=1;
    cin >> n >> m;
    
    C.resize(n+1); // 初始化任务数为0
    V.resize(n+1); // 每个节点对应一个map
    Z.resize(n+1);
    ZT.resize(m+1);
    for(i=1;i<=n;i++){
        cin >> Z[i];
    }
    cin >> k;
    // cout << "k:" << k << endl;
    for(i=0;i<k;i++){ // 一共操作
        cin >> temp >> app >> nodeQh >> taskQh >> AntiQh >> AlwAnti; // 需要几次操作
        // app表示所属任务的编号
        flag1 = 1; // 默认可以输出
        // cout << "output:" ;
        for(j=0;j<temp;j++){ // real一次判断
            if(!flag1){
                cout << 0 << " ";
                continue;
            }
            set<pair<int,int>> S;
            for(l=1;l<=n;l++){ // 遍历节点
                if(check1(l,nodeQh,taskQh)){
                    S.insert({C[l],l}); 
                }
            }
            if(S.size()!=0){
                tempRes = (*S.begin()).second; //在不考虑反清和的情况下的结果
            }
            else{
                cout << 0 << " ";
                flag1 = 0;
                continue; // 如果已经没有可以选的点了那么直接不能分配，下一个
            }
            if(!AntiQh){ // 是否有反亲和的要求
                cout << tempRes << " ";
                C[tempRes]++;
                V[tempRes][app] = 1; //表示第tempRes分区有了应用app的任务
                ZT[Z[tempRes]][app] = 1 ;
            }
            else{
                flag=0;
                for(auto iter=S.begin();iter!=S.end();iter++){
                    if(check2((*iter).second,AntiQh)){ // 检查节点是否满足反亲和的要求
                        cout << (*iter).second << " ";
                        C[(*iter).second]++;
                        V[(*iter).second][app] = 1;
                        ZT[Z[(*iter).second]][app] = 1 ;
                        flag= 1;
                        break;
                    }
                }
                if(!flag){
                    if (AlwAnti) {cout << 0 << " ";}
                    else{ 
                        cout << tempRes << " ";
                        C[tempRes]++;
                        V[tempRes][app] = 1;
                        ZT[Z[tempRes]][app] = 1 ;
                    }
                }
            }
        }
        cout << endl;
    }
    return 0;
}