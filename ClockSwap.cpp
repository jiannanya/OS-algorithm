//页面置换clock算法
#include<iostream>
using namespace std;

class SimpleClock{
private:
    struct PL{
        int pageNum[7]={0,1,2,3,4,5,6};
        int memLoc[7]={3,-1,1,-1,0,-1,-1};
        bool isLive[7]{1,0,1,0,1,0,0};
    }PageList;

    struct MEM{
        int memLoc[4]={0,1,2,3};
        int pageNum[4]={4,2,-1,0};
        bool access[4]={1,0,-1,0};
        bool modify[4]={1,1,0,0};
        int pointer[4]={1,3,2,0};
    }Memory;

    int busyPointer = 0;
    int idlePointer = 2;

    int cmdLoc[10]={455,1029,2093,2612,3106,4149,5122,6211,6897,875};
    char cmdMode[10]={'r','r','w','w','r','w','r','r','r','w'};

    int cmdPointer = 0;

public:
    SimpleClock(){
        while (cmdPointer<10)
        {
            int page = cmdLoc[cmdPointer]/1024;
            int inLoc = cmdLoc[cmdPointer]%1024;
            char mode = cmdMode[cmdPointer];
            int phyLoc;
            int phyNum;
            int inPage;
            bool flag=false;
            //修改内存
            if(PageList.isLive[page]==0 && idlePointer==-1){//需要执行clock页面置换
                //找到将被替换的页面
                
                bool find = false;
                int i=0;
                int changePointer = busyPointer;
                //第一次扫描
                while (i<4)
                {   
                    if(Memory.access[changePointer]==false && Memory.modify[changePointer]==false){
                        find=true;
                        break;
                    }
                    changePointer = Memory.pointer[changePointer];
                    i++;
                }
                //第二次扫描
                if(!find){
                    i=0;
                    changePointer = busyPointer;
                    while (i<4)
                    {
                        if(Memory.access[changePointer]==false && Memory.modify[changePointer]==true){
                            find=true;
                            break;
                        }
                        Memory.access[changePointer] = 0;
                        changePointer = Memory.pointer[changePointer];
                        i++;
                    }
                }
                //第三次扫描
                if(!find){
                    i=0;
                    changePointer = busyPointer;
                    while (i<4)
                    {   
                        if(Memory.access[changePointer]==false && Memory.modify[changePointer]==false){
                            find = true;
                            break;
                        }
                        changePointer = Memory.pointer[changePointer];
                        i++;
                    }
                }
                //第四次扫描
                if(!find){
                    i=0;
                    changePointer = busyPointer;
                    while (i<4)
                    {
                        if(Memory.access[changePointer]==false && Memory.modify[changePointer]==true){
                            find = true;
                            break;
                        }
                        changePointer = Memory.pointer[changePointer];
                        i++;
                    }
                }

                inPage = Memory.pageNum[changePointer];
                //进行替换
                Memory.pageNum[changePointer] = page;
                Memory.access[changePointer] = 1;                
                if(mode=='w'){
                    Memory.modify[changePointer] = 1;
                }

                phyNum = changePointer;
                phyLoc = phyNum*1024 + inLoc;
                //修改相关指针
                busyPointer = Memory.pointer[changePointer];
                flag = true;

            }else if(PageList.isLive[page]==0 && idlePointer!=-1){
                Memory.pageNum[idlePointer] = page;
                Memory.access[idlePointer] = 1;
                if(mode=='w'){
                    Memory.modify[idlePointer] = 1;
                }
                phyNum = idlePointer;
                phyLoc = phyNum*1024 + inLoc;
                
                int temp = Memory.pointer[busyPointer];
                int  p= busyPointer;
                while(temp!=busyPointer){
                    p = temp;
                    temp = Memory.pointer[temp];
                }
                Memory.pointer[p] = idlePointer;
                Memory.pointer[idlePointer] = busyPointer;

                idlePointer = -1;
                flag = false;
            }else{
                int hitPointer = busyPointer;
                while (Memory.pageNum[hitPointer]!=page)
                {
                    hitPointer = Memory.pointer[hitPointer];
                }

                Memory.access[hitPointer] = 1;                
                if(mode=='w'){
                    Memory.modify[hitPointer] = 1;
                } 

                phyNum = hitPointer;
                phyLoc = phyNum*1024 + inLoc;

                flag = false;
            }

            //修改页表
            if(flag){
                PageList.memLoc[inPage] = -1;
                PageList.memLoc[page] = phyNum;
                PageList.isLive[inPage] = 0;
                PageList.isLive[page] = 1;
            }
            

            cout<<"执行命令 "<<cmdPointer<<", 逻辑地址 "<<cmdLoc[cmdPointer]<<", 请求页号 "<<page
                <<", 页内地址 "<<inLoc<<", 物理块号 "<<phyNum<<", 物理地址 "<<phyLoc<<", 访问模式: "<<mode<<", 是否需要页面置换: "<<flag<<endl;
            cmdPointer++;
        }
    }   
};
int main(){
    system("chcp 65001");
    SimpleClock S = SimpleClock();
    system("pause");
    return 0;
}