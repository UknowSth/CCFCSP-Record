#include<iostream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct data{
    int d; // 日期
    int u; // 居民
    int r; // 地区
}Data; // 定义一条漫游数据的结构体

vector<Data> Wander[1010]; // 漫游数据
// 对于大规模的数据集合尽量直接用数组（或者resize），小规模可以尝试直接push_back
map<int,pair<int,int>> EpiZone; // 风险地区信息

bool check(int day,int d,int u,int r){ // 检查该漫游记录对应人是否为风险
    if(EpiZone.count(r)==0){
        return false;
    }
    if(day<=d+6 && day>=d && EpiZone[r].first <= d && EpiZone[r].second >= day){ 
        // 初期由于缺失了前两个条件结果错误
        // 事实证明即使脑测不会有bug也还是直接加个判断语句来得安心
        return true;
    }
    return false;
}

int setData4Zone(int zone,int day){
    if(EpiZone.count(zone)==0){
        EpiZone[zone] = {day,day+6};
    }
    else{
        if(EpiZone[zone].second+1 >= day){
            EpiZone[zone].second = day+6;
        }
        else{
            EpiZone[zone] = {day,day+6};
        }
    }
    return 0;
}

int main(){
    ios::sync_with_stdio(false); // 加快cin的速度
    int n,i,r,m,j,zone,d,u,r_;
    cin >> n; // 总天数
    for(i=0;i<n;i++){
        cin >> r >> m; // 地区数量与漫游数据数量
        for(j=0;j<r;j++){
            cin >> zone;
            setData4Zone(zone,i);
        }
        for(j=0;j<m;j++){
            cin >> d >> u >> r_;
            // 可能收到未来的数据？
            Wander[i].push_back({d,u,r_}); // 对于小规模的vector，使用了push_back操作
        }
        vector<int> ans; // 用来临时存储输出名单
        cout << i << " ";
        for(j=(i-6>=0?i-6:0);j<=i;j++){
            for(auto iter=Wander[j].begin();iter!=Wander[j].end();iter++){
                if(check(i,(*iter).d,(*iter).u,(*iter).r)){
                    ans.push_back((*iter).u);
                }
            }
        }
        sort(ans.begin(),ans.end());
        ans.erase(unique(ans.begin(),ans.end()),ans.end());
        for(auto iter=ans.begin();iter != ans.end();iter++){
            cout << (*iter) << " ";
        }
        cout << endl;
    }
    return 0;
}