#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int Q[8][8];
int M[8][8];
double M_[8][8];

int Q_M(){ // Q与M对应元素相乘
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            M[i][j] *= Q[i][j];
        }
    }
    return 0;
}

double alpha(int i){ // 辅助的函数alpha
    double res;
    if(i){
        res = 1.0;
    }
    else{
        res = 1/sqrt(2);
    }
    return res;
}

int Cos(){ // 离散余弦变换
    int i,j,u,v;
    double temp;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            temp = 0.0;
            for(u=0;u<8;u++){
                for(v=0;v<8;v++){
                    temp += alpha(u)*alpha(v)*M[u][v]*cos(acos(-1)/8*(i+0.5)*u)*cos(acos(-1)/8*(j+0.5)*v);
                }
            }
            M_[i][j] = temp/4;
        }
    }
    return 0;
}

int Decode(){
    int i,j;
    for(i = 0;i<8;i++){
        for(j = 0;j<8;j++){
            M[i][j] = (int)(M_[i][j]+128+0.5);
            if(M[i][j] > 255){
                M[i][j] = 255;
            }
            else if(M[i][j] < 0){
                M[i][j] = 0;
            }
        }
    }
    return 0;
}

int main(){
    int i,j,k,temp;
    for(i = 0;i<8;i++){
        for(j=0;j<8;j++){
            scanf("%d",&Q[i][j]); // 读入量化矩阵
        }
    }
    int m; 
    scanf("%d",&m); // 填充数据的数量
    int T; 
    scanf("%d",&T); // 输出的模式
    
    // 将数据读入M矩阵,注意如果m不够需要将剩下的位置补充0
    i = 0;j = 0; // 下标置为0,0
    while(!(i==7 && j==7)){
        // printf("%d %d,m=%d\n",i,j,m);
        
        if(m>0){
            scanf("%d",&M[i][j]);
        }
        else{
            M[i][j] = 0; // 补充0
        }
        m--;
        if((i==0||i==7)&&(j%2==0)){
            j++;
        }
        else if((j==0||j==7)&&(i%2==1)){
            i++;
        }
        else if((i+j)%2==1){
            i++; j--;
        }
        else{
            i--; j++;
        }
    }
    if(m>0){
        scanf("%d",&M[7][7]);
    }

    //接下来调用函数来区分不同的输出结果
    if(T == 1){
        Q_M();
    }
    else if(T == 2){
        Q_M();
        Cos();
        Decode();
    }
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            printf("%d ",M[i][j]);
        }
        printf("\n");
    }

    return 0;
}