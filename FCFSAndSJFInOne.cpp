#include <iostream>
#include <iomanip>
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

class SJF{
private:
    static const int MaxNum=100;
    int  ID[MaxNum]; //作业编号 
    int  ArrivalTime[MaxNum];
    int  ServiceTime[MaxNum];
    int  FinishTime[MaxNum];
    int  WholeTime[MaxNum];
    double  WeightWholeTime[MaxNum];
    double startTime[MaxNum]; //开始时间
    double AverageWT_SJF; 
    double AverageWWT_SJF;
public:
    SJF(int n){
        int i;
        for (i = 0; i < n; i++){
            ID[i] = i + 1; // 给作业编号 
            cout<<" 第"<<ID[i]<<" 个作业： "<<endl; 
            cout<<" 请输入该作业的到达时间： "; 
            cin >> ArrivalTime[i];
            if (i == 0)
                ArrivalTime[i] = 0; // 默认第一个作业的到达时间为 0 
            cout<<" 请输入该作业的执行时间： "; 
            cin >> ServiceTime[i];
            if (i == 0){
                startTime[i] = 0;
                FinishTime[i] = ServiceTime[i];
                WholeTime[i] = FinishTime[i] - ArrivalTime[i];
            }
            else{ //根据ServiceTime对作业进行冒泡排序
                for (int j = 1; j < i; j++){ //当前已经有i个作业数
                    for (int k = 1; k <= i - j; k++){
                        if (ServiceTime[k] > ServiceTime[k + 1]){
                            double temp;
                            temp = ID[k];
                            ID[k] = ID[k + 1];
                            ID[k + 1] = temp;

                            temp = ArrivalTime[k];
                            ArrivalTime[k] = ArrivalTime[k + 1];
                            ArrivalTime[k + 1] = temp;

                            temp = ServiceTime[k];
                            ServiceTime[k] = ServiceTime[k + 1];
                            ServiceTime[k + 1] = temp;
                        }
                    }       
                }
            }
        }
        for (i = 1; i < n; i++){ // 排序后计算各作业的开始、结束、周转时间
            startTime[i] = FinishTime[i - 1];
            FinishTime[i] = startTime[i] + ServiceTime[i];
            WholeTime[i] = FinishTime[i] - ArrivalTime[i];
        }
        for(i = 0; i < n; i++)//计算带权周转时间
            WeightWholeTime[i] = double(WholeTime[i])/double(ServiceTime[i]);
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
    //打印输出 
    void print(int n) {
        cout<<"------CPU开始调度------"<<endl;
        for(int i = 0;i<n;i++){
            cout<<"时刻"<<startTime[i]<<"：进程"<<ID[i]<<"开始运行"<<endl;
        }
        cout<<"------各进程调度表------"<<endl;
        cout << "ID\t"<< "AT\t"<< "ST\t"<< "FT\t"<< "WT\t" << "WWT\t"<<endl;
        for (int i = 0; i < n; i++){
            cout << ID[i] << "\t" << ArrivalTime[i] << "\t" << ServiceTime[i] << "\t" << FinishTime[i] << "\t" << WholeTime[i] << "\t" <<setiosflags(ios::fixed) << setprecision(2)<< WeightWholeTime[i] << "\t" << endl;
        }
        cout << endl;
        cout << " 平均周转时间： " <<setiosflags(ios::fixed) << setprecision(1)<< getWT(n) << endl;
        cout << " 带权平均周转时间： " << getWWT(n) << endl;
    }
};

int main(){   
    int n,mode; 
    system("chcp 65001");
    cout<< "请选择调度算法（1=FCFS,2=SJF）：";
    cin>>mode;
    cout << "请输入作业数目： ";
    cin >> n;
    if(mode==1){
        cout << "------ FCFS ------" << endl;
        FCFS f = FCFS(n);
        f.print(n);
    }
    if(mode==2){
        cout << "------ SJF ------" << endl;
        SJF f = SJF(n);
        f.print(n);
    }
    return 0;
}