//进程调度的银行家算法

#include <iostream>
#include<string.h>
using namespace std;

class Banker{
private:
    static const int MaxNumber=10;
    static const int n=5;
    static const int m=3;
    int k,num=0;
    int Available[MaxNumber];
	int Max[MaxNumber][MaxNumber];
	int Allocation[MaxNumber][MaxNumber];
	int Need[MaxNumber][MaxNumber];
	int Request[MaxNumber];
	int SafeOrder[MaxNumber];
    int BackOrder[200][MaxNumber];
    int Work[MaxNumber];
    bool Finish[MaxNumber];

    void initialize(){
        //T0时刻资源分配初始化,0=A,1=B,2=C
        cout<<"system initializing..."<<endl;
        Available[0]=3;Available[1]=3;Available[2]=2;
        for(int i=0;i<n;i++){
            switch (i)
            {
            case 0:
                Max[i][0]=7;Max[i][1]=5;Max[i][2]=3;
                Allocation[i][0]=0;Allocation[i][1]=1;Allocation[i][2]=0;
                Need[i][0]=7;Need[i][1]=4;Need[i][2]=3;
                break;
            case 1:
                Max[i][0]=3;Max[i][1]=2;Max[i][2]=2;
                Allocation[i][0]=2;Allocation[i][1]=0;Allocation[i][2]=0;
                Need[i][0]=1;Need[i][1]=2;Need[i][2]=2;
                break;   
            case 2:
                Max[i][0]=9;Max[i][1]=0;Max[i][2]=2;
                Allocation[i][0]=3;Allocation[i][1]=0;Allocation[i][2]=2;
                Need[i][0]=6;Need[i][1]=0;Need[i][2]=0;
                break;  
            case 3:
                Max[i][0]=2;Max[i][1]=2;Max[i][2]=2;
                Allocation[i][0]=2;Allocation[i][1]=1;Allocation[i][2]=1;
                Need[i][0]=0;Need[i][1]=1;Need[i][2]=1;
                break;          
            case 4:
                Max[i][0]=4;Max[i][1]=3;Max[i][2]=3;
                Allocation[i][0]=0;Allocation[i][1]=0;Allocation[i][2]=2;
                Need[i][0]=4;Need[i][1]=3;Need[i][2]=1;
                break;
            default:
                break;
            }
        }
        cout<<"system initialization completed"<<endl;
    }

    bool check(){
        // int AllocateCopy[MaxNumber][MaxNumber];
        // for(int i=0;i<MaxNumber;i++){
        //     for(int j=0;j<MaxNumber;j++){
        //         AllocateCopy[i][j]=Allocation[i][j];
        //     }
        // }
        for(int i=0;i<n;i++){
            Work[i]=Available[i];
            Finish[i]=false;
        }

        for(int i=0;i<n;i++){
            if(Finish[SafeOrder[i]]==false){
                for(int j=0;j<m;j++){
                    if(Need[SafeOrder[i]][j]>Work[j]){
                        return false;
                    }
                } 
                for(int j=0;j<m;j++){
                    Work[j] += Allocation[SafeOrder[i]][j]; 
                }
                Finish[SafeOrder[i]] = true;
            }
                 
        }
        return true;

        
    }

    void banker(int p){
        //请求检查
        for(int i=0;i<m;i++){
            if(Request[i]>Need[p][i]){
                cout<<"error: process "<<p<<" request more than needed"<<endl;
                return;
            }
            if(Request[i]>Available[i]){
                cout<<"error: process "<<p<<" request more than available"<<endl;
                return;
            }
        }
        //试探分配
        for(int i=0;i<m;i++){
            Available[i] -= Request[i];
            Allocation[p][i] += Request[i];
            Need[p][i] -= Request[i];
        }
        //安全性检查
        safecheck(0);
        //恢复数据以处理下一次进程请求
        for(int i=0;i<m;i++){
            Available[i] += Request[i];
            Allocation[p][i] -= Request[i];
            Need[p][i] += Request[i];
        }
        
        if(BackOrder[0][0]!=-1){
            cout<<"process "<<p<<" request successfully"<<endl;
            cout<<"safe order:";
            for(int i=0;i<n;i++){
                cout<<BackOrder[0][i]<<' ';
            }
            cout<<endl;
        }
        else{
            cout<<"unsafe when execute process "<<p<<" request"<<endl;
        }
    }
    int safecheck(int k){
        int i,j,flag;
        if (k==n) {
            if(check()){
                for(int x=0;x<n;x++){
                    BackOrder[num][x] = SafeOrder[x];
                } 
                num++;
            }
            return 0;

        }
        else{
            for (j=0; j<n; j++) {
                flag=1;
                SafeOrder[k]=j;
                for (i=0; i<k; i++) {
                    if (SafeOrder[i]==SafeOrder[k]) {
                        flag=0;
                        break;
                    }
                }
                if (flag) {
                    safecheck(k+1);
                    SafeOrder[k]=-1;
                }
            }
        }
        return num;
    }

public:
    Banker(){
        initialize();
    }
    
    void request(int t){
        int p;
        num = 0;
        memset(SafeOrder, -1, sizeof(SafeOrder));
        for(int i =0;i<200;i++){
            memset(BackOrder[i], -1, sizeof(BackOrder[i]));
        }
        //根据第几次请求调度来初始化Request
        switch (t)
        {
        case 0:
            p=1;
            Request[0]=1;Request[1]=0;Request[2]=2;
            break;
        case 1:
            p=4;
            Request[0]=3;Request[1]=3;Request[2]=0;
            break;
        case 2:
            p=0;
            Request[0]=0;Request[1]=2;Request[2]=0;
            break;
        case 3:
            p=0;
            Request[0]=0;Request[1]=1;Request[2]=0;
            break;
        default:
            break;
        }
        banker(p);

    }
    
    // void print(){
    //     for(int i=0;i<5;i++){
    //         for(int j=0;j<n;j++){
    //             cout<<' '<<BackOrder[i][j];
    //         }
    //         cout<<endl;
    //     }
    //     cout<<endl;
    //     for(int j=0;j<n;j++){
    //             cout<<' '<<SafeOrder[j];
    //         }
    // }
};

int main(){
    Banker b=Banker();
    cout<<endl<<"------start dipatch 1------"<<endl;
    b.request(0);
    //b.print();
    cout<<endl<<"------start dipatch 2------"<<endl;
    b.request(1);
    cout<<endl<<"------start dipatch 3------"<<endl;
    b.request(2);
    cout<<endl<<"------start dipatch 4------"<<endl;
    b.request(3);
    //b.print();
    system("pause");
    return 0;
}