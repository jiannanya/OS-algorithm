//虚拟内存页面置换

#include<iostream>
#include<queue>
using namespace std;

class VirMem{
private:
    //static const int MaxNumber=100;
	int  PageOrder[20]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	//int  Simulate[MaxNumber][MaxNumber];
	int  PageNum,LackNum;
	double  LackPageRate;
    bool Found=false;

public:
    void FIFO(int m,int n){
        cout<<endl<<"------FIFO------"<<endl;
        queue<int> que;
        int count=0;
        LackNum=0;
         
        while (count<n)
        {   
            PageNum=PageOrder[count];             
            for(int i =0; i < que.size(); i ++){ 
                int bufer;
                bufer=que.front();que.push(bufer);que.pop();
                if(bufer==PageNum){
                    Found=true;
                }              
            }
            if(Found){
                count++;
                Found=false;
            }
            else//当内存找不到的所需的页面时
            {
                if(que.size()<m){
                    que.push(PageOrder[count]);
                    LackNum++;
                    count++;
                }
                else
                {
                    que.pop();
                    que.push(PageNum);
                    LackNum++;
                    count++;
                }
            }    
        }
        LackPageRate=double(LackNum)/double(n);
        cout<<"Lack Num:"<<LackNum<<endl;
        cout<<"Lack Page Rate:"<<LackPageRate<<endl;
    }

    void OPI(int m,int n){
        cout<<endl<<"------OPI------"<<endl;
        int count=0;
        int PageCount[m];
        for(int i=0;i<m;i++){
            PageCount[i]=-1;
        }
        LackNum=0;
        while (count<n)
        {
            PageNum=PageOrder[count]; 
            for(int i=0;i<m;i++){
                if(PageCount[i]==PageNum){
                    Found=true;
                }
            }
            if(Found){
                count++;
                Found=false;
            }
            else
            {
                if(count<m){
                    PageCount[count]=PageNum;
                    count++;
                    LackNum++;
                }
                else
                {
                    //为内存里的每个页面寻找最近将被访问的索引，索引最大的被替换出去
                    int max=-1,index=0;
                    for(int i=0;i<m;i++){
                        bool virfound=false;
                        int vircount=count;
                        while (vircount<n)
                        {
                            vircount++;
                            if(PageOrder[vircount]==PageCount[i]){
                                break;
                            }
                        }
                        if(max<vircount){
                            max=vircount;
                            index=i;
                        }
                    }
                    PageCount[index]=PageNum;
                    count++;
                    LackNum++;

                }
                
            }
            
        }
        LackPageRate=double(LackNum)/double(n);
        cout<<"Lack Num:"<<LackNum<<endl;
        cout<<"Lack Page Rate:"<<LackPageRate<<endl;        
    }

    void LRU(int m,int n){
        cout<<endl<<"------LRU------"<<endl;
        int count=0;
        int PageCount[m];
        for(int i=0;i<m;i++){
            PageCount[i]=-1;
        }
        LackNum=0;
        while (count<n)
        {
            PageNum=PageOrder[count]; 
            for(int i=0;i<m;i++){
                if(PageCount[i]==PageNum){
                    Found=true;
                }
            }
            if(Found){
                count++;
                Found=false;
            }
            else
            {
                if(count<m){
                    PageCount[count]=PageNum;
                    count++;
                    LackNum++;
                }
                else
                {
                    //为内存里的每个页面寻找最久最近未被访问的索引
                    int max=-1,index=0;
                    for(int i=0;i<m;i++){
                        bool virfound=false;
                        int vircount=0;
                        while (vircount<count)
                        {
                            if(PageOrder[vircount]==PageCount[i]){
                                break;
                            }
                            vircount++;
                        }
                        if(max<vircount){
                            max=vircount;
                            index=i;
                        }
                    }
                    PageCount[index]=PageNum;
                    count++;
                    LackNum++;

                }
                
            }
            
        }
        LackPageRate=double(LackNum)/double(n);
        cout<<"Lack Num:"<<LackNum<<endl;
        cout<<"Lack Page Rate:"<<LackPageRate<<endl;        
    }


};

int main(){
    system("chcp 65001");
    int m,n;
    cout<<"请输入内存物理块数：";cin>>m;
    cout<<"请输入要访问的页面个数：";cin>>n;
    VirMem F=VirMem();
    F.FIFO(m,n);
    F.OPI(m,n);
    F.LRU(m,n);
    system("pause");
    return 0;

}