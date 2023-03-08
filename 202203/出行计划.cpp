#include<iostream>
#include<algorithm>
#include<map>
#include<vector>

using namespace std;

int main(){
    vector<int> V1;
    vector<int> V2;
    int n,m,k,i,temp1,temp2;
    cin >> n >> m >> k;
    V1.resize(n);
    V2.resize(n);
    for(i=0;i<n;i++){
        cin >> temp1 >> temp2;
        V1[i] = temp1+1-k-temp2;
        V2[i] = temp1-k;
    }
    sort(V1.begin(),V1.end());
    for(i=0;i<m;i++){
        cin >> temp1;
        auto index1 = lower_bound(V2.begin(),V2.end(),temp1)-V2.begin();
        auto index2 = upper_bound(V1.begin(),V1.end(),temp1)-V1.begin();
        cout << index2-index1 << endl;
    }
    return 0;
}