//first come first server
#include <iostream>
using namespace std;

class FCFS{
private:
    static const int MaxNum=100;
    int ID[MaxNum]; //作业编号
    int ArrivalTime[MaxNum];
    int ServiceTime[MaxNum];
    int FinishTime[MaxNum];
    int WholeTime[MaxNum];
    double WeightWholeTime[MaxNum];
    double startTime[MaxNum]; //开始时间
    double AverageWT_FCFS; 
    double AverageWWT_FCFS;
public:
    FCFS(int n){
        for (int i = 0; i < n; i++){
            ID[i] = i + 1; 
            cout<<" 第"<<ID[i]<<" 个作业： "<<endl; cout<<" 请输入该作业的到达时间： "; cin>>ArrivalTime[i];
            if (i == 0)
                ArrivalTime[i] = 0; 
            cout<<" 请输入该作业的执行时间： ";
            cin >> ServiceTime[i];
            if (i == 0){
                startTime[i] = 0;
                FinishTime[i] = ServiceTime[i];
            }
            else if (ArrivalTime[i] <= FinishTime[i - 1]){
                    startTime[i] = FinishTime[i - 1]; 
                    FinishTime[i] = startTime[i] + ServiceTime[i]; 
                }
            else if (ArrivalTime[i] > FinishTime[i - 1]){
                startTime[i] = ArrivalTime[i]; 
                FinishTime[i] = startTime[i] + ServiceTime[i];
            }
            WholeTime[i] = FinishTime[i] - ArrivalTime[i];
            WeightWholeTime[i] = double(WholeTime[i])/double(ServiceTime[i]);
        }
    }
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
    //打印输出 
    void print(int n){ 
        cout<<"------CPU开始调度------"<<endl;
        for(int i = 0;i<n;i++){
            cout<<"时刻"<<startTime[i]<<"：进程"<<ID[i]<<"开始运行"<<endl;
        }
        cout<<"------各进程调度表------"<<endl;
        cout<< "Id\t"<< "AT\t"<< "ST\t" << "FT\t"<< "WT\t"<<"WWT\t" << endl;
        for (int i = 0; i < n; i++){
            cout << ID[i] << "\t" << ArrivalTime[i] << "\t" << ServiceTime[i] << "\t" << FinishTime[i] << "\t" << WholeTime[i] << "\t" << WeightWholeTime[i] << "\t" << endl;
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
    FCFS f = FCFS(n);
    f.print(n);
    return 0;
}