#include<iostream>
#include<map>
#include<string>
#include<vector>

using namespace std;

const int N = 510; // 后加

typedef struct role{
    string name;
    map<string,int> OP;
    map<string,int> ResType;
    map<string,int> ResName;
}Role; // 每一个角色的信息 后加

vector< Role > R; //所有角色的信息
map< string,vector<string>> U; // 用户以及用户组所拥有的角色
map<string,int > Index; // 由角色名到所在下标的映射

bool check(string T,string OP,string Type,string Name){ // T为角色名
    int index = Index[T];
    if((R[index].OP.count("*")==0) && (R[index].OP.count(OP)==0)){return false;}
    if((R[index].ResType.count("*")==0) && (R[index].ResType.count(Type)==0)){return false;}
    if((R[index].ResName.size()!=0) && (R[index].ResName.count(Name)==0)){return false;}
    return true;
}

int main(){

    ios::sync_with_stdio(false); //后加
    // Role tempRole;
    int n,m,q;
    cin >> n >> m >> q;
    R.resize(n);
    int i,j,k,OPsize,ResTypesize,ResNamesize,temp;
    string tempStr,type,name,Cname,OPing;
    for(i=0;i<n;i++){
        cin >> R[i].name >> OPsize;
        for(j=0;j<OPsize;j++){
            cin >> tempStr;
            R[i].OP[tempStr]=1; // 记录权限操作
        }
        cin >> ResTypesize;
        for(j=0;j<ResTypesize;j++){
            cin >> tempStr;
            R[i].ResType[tempStr]=1;
        }
        cin >> ResNamesize;
        for(j=0;j<ResNamesize;j++){
            cin >> tempStr;
            R[i].ResName[tempStr]=1;
        }
        // R.push_back(tempRole);
        Index[R[i].name]=i; // 存储下标 便于查找
    } // 第一个部分的信息存储完毕

    for(i=0;i<m;i++){
        cin >> tempStr >> temp;
        for(j=0;j<temp;j++){
            cin >> type >> name;
            U[name].push_back(tempStr);
        }
    } // 第二个部分的信息存储完毕

    vector< string> Ogn;
    for(i=0;i<q;i++){
        bool flag = false;
        cin >> Cname >> temp; // 用户名
        Ogn.clear();
         // 存储用户组名
        for(j=0;j<temp;j++){
            cin >> tempStr;
            Ogn.push_back(tempStr);
        }
        cin >> OPing >> type >> name;
        for(auto iter=U[Cname].begin();iter!=U[Cname].end();iter++){
            if(check((*iter),OPing,type,name)){
                flag = true;
                cout << 1 << endl;
                break;
            }
        }
        if(!flag){ // 用户名没有权限 看组名
            for(auto iter1=Ogn.begin();iter1!=Ogn.end();iter1++){
                for(auto iter2=U[(*iter1)].begin();iter2!=U[(*iter1)].end();iter2++){
                    if(check((*iter2),OPing,type,name)){
                        flag = true;
                        cout << 1 << endl;
                        break;
                    }
                }
                if(flag){
                    break;
                }
            }
            if(!flag){
                cout << 0 << endl;
            }
        }
    }
    return 0;
}