#include<iostream>
#include<math.h>
using namespace std;

class FCFS{
private:
    const static int MaxNumber=9;
    int CurrentStage = 100;
    const int TrackList[MaxNumber]={55,58,39,18,90,160,150,38,184};
	int TrackOrder[MaxNumber];
	int MoveDistance[MaxNumber];
	double AverageDistance = 0;

    float averagedistance(){
        float total = 0;
        for(int i=0;i<MaxNumber;i++){
            total += MoveDistance[i];    
        }
        return total/MaxNumber;
    }

public:
    FCFS(){
        cout<<"------FCFS------"<<endl;
        for(int i=0;i<MaxNumber;i++){
            TrackOrder[i] = TrackList[i];
            MoveDistance[i] = abs(CurrentStage -TrackOrder[i]);
            CurrentStage = TrackOrder[i];
            cout<<TrackList[i]<<endl;
        }
        cout<<endl;
        cout<<"AverageDistance: "<<averagedistance()<<endl;
    }

};

class SSTF{
private:
    const static int MaxNumber=9;
    int CurrentStage = 100;
    const int TrackList[MaxNumber]={55,58,39,18,90,160,150,38,184};
	int TrackOrder[MaxNumber];
	int MoveDistance[MaxNumber];
	double AverageDistance;

    //初始化
    void initorder(){
        for(int i=0;i<MaxNumber;i++){
            TrackOrder[i]=-1;
        } 
    }
    
    bool intrackorder(int n){
        for(int i=0;i<MaxNumber;i++){
            if(TrackOrder[i]==n){
                return true;
            }
        }
    }

    float averagedistance(){
        float total = 0;
        for(int i=0;i<MaxNumber;i++){
            total += MoveDistance[i];    
        }
        return total/MaxNumber;
    }
public:
    SSTF(){
        initorder();
        cout<<"------SSTF------"<<endl;
        for(int i=0;i<MaxNumber;i++ ){
            int gap = 1000;
            int NextIndex = -1;
            for(int j=0;j<MaxNumber;j++){
                int g = abs(CurrentStage-TrackList[j]);
                if(g<gap&&!intrackorder(TrackList[j])){
                    gap = g;
                    NextIndex = j;
                }
            }
            TrackOrder[i] = TrackList[NextIndex];
            MoveDistance[i] = gap;
            CurrentStage = TrackOrder[i];
            cout<<TrackOrder[i]<<endl;
        }
        cout<<endl;
        cout<<"AverageDistance: "<<averagedistance()<<endl;
    }

};

class SCAN{
private:
    const static int MaxNumber=9;
    int CurrentStage = 100;
    const int TrackList[MaxNumber]={55,58,39,18,90,160,150,38,184};
	int TrackOrder[MaxNumber];
	int MoveDistance[MaxNumber];
	double AverageDistance;
	bool Direction = true;//磁道数增长方向

    //初始化
    void initorder(){
        for(int i=0;i<MaxNumber;i++){
            TrackOrder[i]=-1;
        } 
    }
    
    bool intrackorder(int n){
        for(int i=0;i<MaxNumber;i++){
            if(TrackOrder[i]==n){
                return true;
            }
        }
    }

    float averagedistance(){
        float total = 0;
        for(int i=0;i<MaxNumber;i++){
            total += MoveDistance[i];    
        }
        return total/MaxNumber;
    }

    int getlasttrack(){
        int last=0;
        for(int i=0;i<MaxNumber;i++){
            if(TrackList[i]>last){
                last=TrackList[i];
            }
        }
        return last;
    }
    int getfirsttrack(){
        int first=1000;
        for(int i=0;i<MaxNumber;i++){
            if(TrackList[i]<first){
                first=TrackList[i];
            }
        }
        return first;
    }
public:
    SCAN(){
        initorder();
        cout<<"------SCAN------"<<endl;
        for(int i=0;i<MaxNumber;i++ ){
            int gap = 1000;
            int NextIndex = -1;
            if(Direction){
                if(CurrentStage==getlasttrack()){
                    Direction = !Direction;
                    i--;
                    continue;
                }
                for(int j=0;j<MaxNumber;j++){
                    int g = abs(CurrentStage-TrackList[j]);
                    if(g<gap&&!intrackorder(TrackList[j])&&CurrentStage<=TrackList[j]){
                        gap = g;
                        NextIndex = j;
                    }
                }
            }else{
                if(CurrentStage==getfirsttrack()){
                    Direction = !Direction;
                    i--;
                    continue;
                }
                for(int j=MaxNumber-1;j>=0;j--){
                    int g = abs(CurrentStage-TrackList[j]);
                    if(g<gap&&!intrackorder(TrackList[j])&&CurrentStage>=TrackList[j]){
                        gap = g;
                        NextIndex = j;
                    }

                }
            }
            TrackOrder[i] = TrackList[NextIndex];
            MoveDistance[i] = gap;
            CurrentStage = TrackOrder[i];
            cout<<TrackOrder[i]<<endl;
        }
        cout<<endl;
        cout<<"AverageDistance: "<<averagedistance()<<endl;
    }

};


class CSCAN{
private:
    const static int MaxNumber=9;
    int CurrentStage = 100;
    const int TrackList[MaxNumber]={55,58,39,18,90,160,150,38,184};
	int TrackOrder[MaxNumber];
	int MoveDistance[MaxNumber];
	double AverageDistance;
	bool Direction = true;//磁道数增长方向

    //初始化
    void initorder(){
        for(int i=0;i<MaxNumber;i++){
            TrackOrder[i]=-1;
        } 
    }
    
    bool intrackorder(int n){
        for(int i=0;i<MaxNumber;i++){
            if(TrackOrder[i]==n){
                return true;
            }
        }
    }

    float averagedistance(){
        float total = 0;
        for(int i=0;i<MaxNumber;i++){
            total += MoveDistance[i];    
        }
        return total/MaxNumber;
    }

    int getlasttrack(){
        int last=0;
        for(int i=0;i<MaxNumber;i++){
            if(TrackList[i]>last){
                last=TrackList[i];
            }
        }
        return last;
    }
    int getfirsttrack(){
        int first=1000;
        for(int i=0;i<MaxNumber;i++){
            if(TrackList[i]<first){
                first=TrackList[i];
            }
        }
        return first;
    }
public:
    CSCAN(){
        initorder();
        cout<<"------CSCAN------"<<endl;
        for(int i=0;i<MaxNumber;i++ ){
            int gap = 1000;
            int NextIndex = -1;
            bool flag0 = false;
            bool flag1 = false;
            if(Direction){
                if(CurrentStage==getlasttrack()){
                    CurrentStage = 0;
                    flag0 = true;
                }
                for(int j=0;j<MaxNumber;j++){
                    int g = abs(CurrentStage-TrackList[j]);
                    if(g<gap&&!intrackorder(TrackList[j])&&CurrentStage<=TrackList[j]){
                        gap = g;
                        NextIndex = j;
                    }
                }
            }else{
                if(CurrentStage==getfirsttrack()){
                    CurrentStage=getlasttrack();
                    flag1 = true;
                }
                for(int j=MaxNumber-1;j>=0;j--){
                    int g = abs(CurrentStage-TrackList[j]);
                    if(g<gap&&!intrackorder(TrackList[j])&&CurrentStage>=TrackList[j]){
                        gap = g;
                        NextIndex = j;
                    }

                }
            }
            TrackOrder[i] = TrackList[NextIndex];
            if(flag0){
                gap=abs(gap-getlasttrack());
            }
            if(flag1){
                gap=abs(getlasttrack()-getfirsttrack());
            }
            MoveDistance[i] = gap;
            CurrentStage = TrackOrder[i];
            cout<<TrackOrder[i]<<endl;
        }
        cout<<endl;
        cout<<"AverageDistance: "<<averagedistance()<<endl;
    }

};

int main(){
    FCFS f = FCFS();
    SSTF s = SSTF();
    SCAN d = SCAN();
    CSCAN c = CSCAN();
    system("pause");
}