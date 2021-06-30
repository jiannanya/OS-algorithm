#include<iostream>
#include<queue>
using namespace std;
//高响应比优先算法
class PR{
private:
    static const int MaxNum=100;
    double Pr[MaxNum]; //响应比
    int WaitTime[MaxNum];//等待时间
    int ID[MaxNum]; //作业编号
    int ArrivalTime[MaxNum];
    int ServiceTime[MaxNum];
    int STCopy[MaxNum];
    int FinishTime[MaxNum];
    int WholeTime[MaxNum];
    double WeightWholeTime[MaxNum];
    double startTime[MaxNum]; //开始时间
    double AverageWT_RR; 
    double AverageWWT_RR;

    //计算响应比
    void calculate(int n){
        for(int i=0;i<n;i++){
            if(ServiceTime[i]!=0){
                Pr[i]=(double(WaitTime[i])+double(ServiceTime[i]))/double(ServiceTime[i]);
            }
            else{
                Pr[i]=-1;
            }
            
        }
    }

    //排序
    void sort(int n){
        int k;
        int temp;
        bool flag=true;
        for(int i=0;i<n-1;i++){
            temp=Pr[i];
            for(int j=i;j<n;j++){    
                if(Pr[j]>temp){
                    flag=false;
                    k=j;
                    temp=Pr[j];
                }
            }
            if(flag)break;

            temp = ID[k];
            ID[k] = ID[i];
            ID[i] = temp;

            temp = ArrivalTime[k];
            ArrivalTime[k] = ArrivalTime[i];
            ArrivalTime[i] = temp;

            temp = ServiceTime[k];
            ServiceTime[k] = ServiceTime[i];
            ServiceTime[i] = temp;

            temp = startTime[k];
            startTime[k]=startTime[i];
            startTime[i]=temp;

            temp =FinishTime[k];
            FinishTime[k]=FinishTime[i];
            FinishTime[i]=temp;

            temp = STCopy[k];
            STCopy[k]=STCopy[i];
            STCopy[i]=temp;
        }
    }

    //计算平均周转时间 
    double getWT(int n){
        double AverageWT_SJF, sum = 0;
        for (int i = 0; i < n; i++)
            sum += WholeTime[i];
        AverageWT_SJF = sum / n;
        return AverageWT_SJF;
    } 

    //计算带权平均周转时间
    double getWWT(int n){
        double AverageWWT_SJF, sum = 0;
        for (int i = 0; i < n; i++)
            sum += WeightWholeTime[i];
        AverageWWT_SJF = sum / n;
        return AverageWWT_SJF;
    }

public:
    PR(int n){
        for (int i = 0; i < n; i++){  
            ID[i] = i + 1;
            cout<<" 第"<<ID[i]<<" 个作业："<<endl; cout<<" 请输入该作业的到达时间： "; cin>>ArrivalTime[i];
            if (i == 0)
                ArrivalTime[i] = 0; 
            cout<<" 请输入该作业的执行时间： ";
            cin >> ServiceTime[i];
            STCopy[i]=ServiceTime[i];
            startTime[i]=-1;
            WaitTime[i]=0;
        }
        int flag=0;
        int Time=0;
        while (flag<5){
            calculate(n);
            sort(n);
            startTime[0]=Time;
            Time+=ServiceTime[0];
            FinishTime[0]=Time;
            ServiceTime[0]=0;
            for(int i=0;i<n;i++){
                if(ServiceTime[i]!=0){
                    WaitTime[i]+=Time;
                    WaitTime[i]-=ArrivalTime[i];
                }
                else
                {
                    WaitTime[i]=-1;
                }  
            }
            flag++;
        }
        for(int i = 0; i < n; i++){
            WholeTime[i] = FinishTime[i] - ArrivalTime[i];
            WeightWholeTime[i] = double(WholeTime[i])/double(STCopy[i]);
        }
    }


    //打印输出 
    void print(int n){ 
        cout<<"------CPU开始调度------"<<endl;
        for(int i = 0;i<n;i++){
            cout<<"时刻"<<startTime[i]<<"：进程"<<ID[i]<<"开始运行"<<endl;
        }
        cout<<"------各进程调度表------"<<endl;
        cout<< "Id\t"<< "AT\t"<< "ST\t" << "FT\t"<< "WT\t"<<"WWT\t" << endl;
        for (int i = 0; i < n; i++){
            cout << ID[i] << "\t" << ArrivalTime[i] << "\t" << STCopy[i] << "\t" << FinishTime[i] << "\t" << WholeTime[i] << "\t" << WeightWholeTime[i] << "\t" << endl;
        }
        cout << endl;
        cout << " 平均周转时间： " << getWT(n) << endl;
        cout << " 带权平均周转时间： " << getWWT(n) << endl;
    }
};

int main(){
    int n; 
    system("chcp 65001");
    cout << "请输入作业数目： ";
    cin >> n;
    PR f = PR(n);
    f.print(n);
    return 0;
}