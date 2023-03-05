#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int ** Map;
int n,S,L;

int FindTree(int i,int j){ // 查找在地图上i.j位置是否存在树的函数
    // 如果该位置不存在地图上(下标不符合),那么会返回2
    int flag = 0;
    int k;
    if(i > L || j > L || i < 0 || j < 0){
        return 2;
    }
    for(k=0;k<n;k++){
        if(Map[k][0] == i && Map[k][1] == j){
            flag = 1;
            break;
        }
    }
    return flag;
}

int main(){
    int i,j,k;
    scanf("%d%d%d",&n,&L,&S);
    Map = (int**)malloc(n*sizeof(int*));
    for(i=0;i<n;i++){
        Map[i] = (int*)malloc(2*sizeof(int));
    } // 分配好用来存储地图上树的点对的数组
    for(i=0;i<n;i++){
        scanf("%d%d",&Map[i][0],&Map[i][1]);
    }
    int** MiniMap = (int**)malloc((S+1)*sizeof(int*));
    for(i=0;i<=S;i++){
        MiniMap[i] = (int*)malloc((S+1)*sizeof(int));
    }
    for(i=S;i>=0;i--){
        for(j=0;j<=S;j++){
            scanf("%d",&MiniMap[i][j]);
        }
    }// 读入藏宝图对应的矩阵
    
    //接下来对于每一个存储的点对，确认其所在的宫格是否能够和藏宝图重合
    int tempi,tempj,flag,count=0;
    for(i=0;i<n;i++){
        flag = 1;
        tempi = Map[i][0];
        tempj = Map[i][1]; // 读取左上角位置
        for(j=0;j<=S;j++){
            for(k=0;k<=S;k++){
                if(MiniMap[j][k] != FindTree(tempi+j,tempj+k)){
                    flag = 0;
                    break;
                }
            }
            if(!flag){
                break;
            }
        }
        if(flag){
            count++;
        }
    }
    printf("%d",count);
    return 0;
}