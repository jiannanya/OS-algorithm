#include<iostream>
#include<queue>
using namespace std;

//时间片轮转算法
class RR{
private:
    static const int MaxNum=100;
    static const int Q=1;
    int Time=0;
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

    //计算平均周转时间 
    double getWT(int n) {
        double AverageWT_FCFS, sum = 0;
        for (int i = 0; i < n; i++)
            sum += WholeTime[i];
        AverageWT_FCFS = sum / n;
        return AverageWT_FCFS;
    } 
    //计算带权平均周转时间
    double getWWT(int n){
        double AverageWWT_FCFS, sum = 0;
        for (int i = 0; i < n; i++)
            sum += WeightWholeTime[i];
        AverageWWT_FCFS = sum / n;
        return AverageWWT_FCFS;
    } 

public:
    RR(int n){
        for (int i = 0; i < n; i++){  
            ID[i] = i + 1;
            cout<<" 第"<<ID[i]<<" 个作业："<<endl; cout<<" 请输入该作业的到达时间： "; cin>>ArrivalTime[i];
            if (i == 0)
                ArrivalTime[i] = 0; 
            cout<<" 请输入该作业的执行时间： ";
            cin >> ServiceTime[i];
            STCopy[i]=ServiceTime[i];
            startTime[i]=-1;
        }
        int Ps;
        queue<int> Que;   
        Que.push(ID[0]);
        while(!Que.empty()){
            Ps=Que.front()-1;Que.pop();
            if(startTime[Ps]==-1){
                startTime[Ps]=Time;
            }
            if(ServiceTime[Ps]-Q>0){
                ServiceTime[Ps]-=Q;
                Time+=Q;
            }
            else if(ServiceTime[Ps]-Q==0){
                ServiceTime[Ps]=0;
                Time+=Q;
                FinishTime[Ps]=Time;
            }
            else{
                FinishTime[Ps]=Time+ServiceTime[Ps];
                Time+=ServiceTime[Ps];
                ServiceTime[Ps]=0;
            }
            for(int i=0;i<n;i++){
                if(Time==ArrivalTime[i]||Time>ArrivalTime[i]&&Time-Q<ArrivalTime[i]){
                  Que.push(ID[i]);  
                }
            }
            if(ServiceTime[Ps]!=0){
                Que.push(ID[Ps]);
            }
            
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
        cout<<"------各进程调度表------"<<"q= "<<Q<<endl;
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
    RR f = RR(n);
    f.print(n);
    return 0;
}