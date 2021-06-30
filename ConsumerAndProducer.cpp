#include <windows.h>
#include <iostream>
#include<ctime>
#include <cstdlib>
using namespace std;

#define NAME   40
const int N =16; 
const int MIN_VALUE = 1;
const int MAX_VALUE = 16;
//定义线程函数传入参数的结构体
typedef struct __THREAD_DATA{
    int nMaxNum;
    char strThreadName[NAME];
 
    __THREAD_DATA() : nMaxNum(0)
    {
        memset(strThreadName, 0, NAME * sizeof(char));
    }
}THREAD_DATA;



struct __BUFF{
    int id;
    HANDLE MUTEX = NULL;     //互斥量
    HANDLE EMPTY = NULL;
    HANDLE FULL = NULL;
}buffer[N];//缓存区列表

HANDLE PRINT;

//生产者
DWORD WINAPI Producer(LPVOID lpParameter){
    THREAD_DATA* pThreadData = (THREAD_DATA*)lpParameter;
    for (int i = 0; i < pThreadData->nMaxNum; ++ i){
        int seed = time(NULL);
        srand(seed);
        int No = rand()% (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;//随机操作一个缓存区
        //请求获得一个互斥量锁
        WaitForSingleObject(buffer[No].MUTEX, INFINITE);
        WaitForSingleObject(buffer[No].EMPTY,INFINITE);
        WaitForSingleObject(PRINT, INFINITE);
        cout << pThreadData->strThreadName << " 写缓存区"<<No<< endl;
        ReleaseMutex(PRINT);
        Sleep(1000);
        //释放互斥量锁
        ReleaseMutex(buffer[No].FULL);
        ReleaseMutex(buffer[No].MUTEX);
    }
    return 0L;
} 
 
//消费者
DWORD WINAPI Consumer(LPVOID lpParameter){
    THREAD_DATA* pThreadData = (THREAD_DATA*)lpParameter;
    for (int i = 0; i < pThreadData->nMaxNum; ++ i){
        int seed = time(NULL);
        srand(seed);
        int No = rand()% (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;//随机操作一个缓存区
        //请求获得一个互斥量锁
        WaitForSingleObject(buffer[No].MUTEX, INFINITE);
        WaitForSingleObject(buffer[No].FULL,INFINITE);
        WaitForSingleObject(PRINT, INFINITE);
        cout << pThreadData->strThreadName << " 读缓存区 " << No << endl;
        ReleaseMutex(PRINT);
        Sleep(1000);
        //释放互斥量锁
        ReleaseMutex(buffer[No].EMPTY);
        ReleaseMutex(buffer[No].MUTEX);
    }
    return 0L;
}
 
int main()
{
    system("chcp 65001");
    //初始化缓存区
    PRINT = CreateMutex(NULL, FALSE, NULL);//有序输出互斥量
    for(int i=0;i<N;i++){
        buffer[i].id=i+1;
        buffer[i].MUTEX = CreateMutex(NULL, FALSE, NULL);
        buffer[i].EMPTY = CreateMutex(NULL, FALSE, NULL);
        buffer[i].FULL = CreateMutex(NULL, FALSE, NULL);
    }
    
 
    //初始化线程数据
    THREAD_DATA threadData1, threadData2;
    threadData1.nMaxNum = 20;
    strcpy(threadData1.strThreadName, "生产者");
    threadData2.nMaxNum = 30;
    strcpy(threadData2.strThreadName, "消费者");
 
 
    //创建第一个子线程
    HANDLE producer = CreateThread(NULL, 0, Producer, &threadData1, 0, NULL);
    //创建第二个子线程
    HANDLE consumer = CreateThread(NULL, 0, Consumer, &threadData2, 0, NULL);
    //关闭线程
    CloseHandle(producer);
    CloseHandle(consumer);
 
    system("pause");
    return 0;
}