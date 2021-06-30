// 模拟文件管理的存储空间管理和多级目录管理
// 假设有一个磁盘有200个盘块，每块的大小为2KB，所有盘块的初始状态为空

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<cstring>
#include<iostream>

using namespace std;

int WST[256];

typedef struct FreeArea{
    int start_location;
    int free_number;
    struct FreeArea*next;
}free_link;

typedef struct Application{
    char office[20];
    int begin_location;
    int office_number;
    struct Application *next;
}office; 

typedef struct {
    free_link* p;
    office* q;
}work;

void menu(){
    printf(" 文件的存取和回收 \n");
    printf(" 1--分配文件 \n");
    printf(" 2--回收文件 \n");
    printf(" 3--退出 \n\t");
    printf(" 请输入选项 : ");
}

void zero_wst(){
    int i;
    for(i=0;i<256;i++)
    WST[i]=0;
}

void print_wst(int WST[256]){
    int i, j = 0;
    printf("%3s", " ");
    for (i = 0; i < 16; i++){
        printf("%3d", i);
    }
    printf("\n");
    printf("%3d", 0);
    for (i = 0; i < 256; i++){
        j++;
        printf("%3d", WST[i]);
        if (j % 16 == 0 && i != 0 && j != 256){
            printf("\n");
            printf("%3d", j / 16);
        }
    }
    printf("\n");
}

void print_office(work* w){
    office *q;
    q = w->q;
    q = q->next;
    if (q != NULL){
        printf(" 已有文件 :\n");
        while (q != NULL)
        {
            printf("\t%s:%d-%d\n", q->office, q->begin_location, q->begin_location + q->office_number - 1);
            q = q->next;
        }
    }
}

work* start(){
    free_link *p;
    office *q;
    work *w;
    w = (work *)malloc(sizeof(work));
    p = (free_link *)malloc(sizeof(free_link));
    p->start_location = 0;
    p->free_number = 256;
    p->next = NULL;
    q = (office *)malloc(sizeof(office));
    q->next = NULL;
    w->p = p;
    w->q = q;
    return w;
}

work* request(work* w, int WST[256]){
    int i, m, n, flag = 0;
    free_link *p, *r, *e;  //r->free_number 用于查找空闲区的块数
    office *q, *s, *t, *u; //s 创建新节点 ,存储新建文件的信息 ,n 用于查找是否有重复节点
    p = w->p;
    r = p;
    q = w->q;
    t = q;
    u = q->next;
    printf(" 请输入文件名和块数 :");
    s = (office *)malloc(sizeof(office));
    s->next = NULL;
    while (t->next != NULL)
        t = t->next;
    scanf("%s%d", &(s->office), &(s->office_number));
    while (u != NULL)
    {
        if (strcmp(s->office, u->office) == 0)
        {
            flag = 1;
            printf(" 对不起 ,该文件已存在 !\n");
            free(s);
            break;
        }
        u = u->next;
    }
    if (flag == 0)
    {
        while (r != NULL)
        {
            if ((r->free_number) >= (s->office_number)) // 用于查找空闲区中空闲块数是否大于欲分配的块数
                break;
            r = r->next;
        }
        if (r == NULL)
        {
            printf(" 对不起 ,没有足够的空间分配失败 !\n");
            free(s);
        }
        else
        {
            t->next = s;
            m = r->start_location;                                    // 空闲区的起始地址
            s->begin_location = r->start_location;                    // 作业从空闲区的起始地址开始分配
            r->start_location = r->start_location + s->office_number; // 改变空闲区空闲块数的起始地址
            r->free_number = r->free_number - s->office_number;       // 改变空间区块数的大小
            n = (r->start_location - 1);                              // 新的空间区的起始地址 -1
            for (i = m; i <= n; i++)                                  // 模拟分配
                WST[i] = 1;
            if (r->free_number == 0)
            {
                if (p == r)
                { //p==r 说明内存中只有一个整块的空闲区
                    free(r);
                    p = NULL;
                }
                else
                {
                    e = p;
                    while (e != NULL)
                    {
                        if (e->next == r)
                            break;
                        e = e->next;
                    }
                    e->next = r->next;
                    free(r);
                }
            }
        }
    }
    w->p = p;
    w->q = q;
    return w;
}

work* delect(work* w, int WET[])
{
    char name[20];
    int i;
    free_link *p, *r, *t;
    office *q, *s, *e;
    p = w->p;
    r = p;
    t = p;
    q = w->q;
    s = q;
    e = q;
    s = s->next;
    if (s == NULL)
    {
        printf(" 没有可以回收的文件 !\n");
    }
    else
    {
        printf(" 请输入文件名 :");
        cin >> name;
        while (s != NULL)
        {
            if (strcmp(s->office, name) == 0)
                break;
            s = s->next;
        }
        if (s == NULL)
        {
            cout << " 对不起没有找到相关文件 !\n";
        }
        else
        {
            if ((WST[s->begin_location - 1] == 0 && WST[s->begin_location + s->office_number] == 1 && s->begin_location - 1 >= 0) || (WST[s->begin_location - 1] == 0 && s->begin_location + s->office_number == 256 && s->begin_location - 1 >= 0))
            {
                while (r != NULL)
                {
                    if ((r->start_location + r->free_number) == s->begin_location)
                        break;
                    r = r->next;
                }
                r->free_number = r->free_number + s->office_number;
            }
            if ((WST[s->begin_location - 1] == 1 && WST[s->begin_location + s->office_number] == 0 &&
                 s->begin_location + s->office_number < 256) ||
                (s->begin_location == 0 &&
                 WST[s->begin_location + s->office_number] == 0 && s->begin_location + s->office_number < 256))
            {
                while (r != NULL)
                {
                    if ((s->begin_location + s->office_number) == r->start_location)
                        break;
                    r = r->next;
                }
                r->start_location = r->start_location - s->office_number;
                r->free_number = r->free_number + s->office_number;
            }
            if (WST[s->begin_location - 1] == 0 && WST[s->begin_location + s->office_number] == 0 &&
                s->begin_location - 1 >= 0 && s->begin_location + s->office_number < 256)
            {
                while (r != NULL)
                {
                    if ((s->begin_location + s->office_number) == r->start_location)
                    {
                        t = r;
                        break;
                    }
                    r = r->next;
                }
                r->free_number = r->free_number + s->office_number + t->free_number;
                free(t);
            }
            if ((WST[s->begin_location - 1] == 1 && WST[s->begin_location + s->office_number] == 1 && s->begin_location - 1 >= 0 && s->begin_location + s->office_number < 256) || (s->begin_location == 0 && WST[s->begin_location + s->office_number] == 1 && s->begin_location + s->office_number < 256) || (WST[s->begin_location - 1] == 1 && s->begin_location + s->office_number == 256 && s->begin_location - 1 >= 0) || (s->begin_location == 0 && s->begin_location + s->office_number == 256))
            {
                t = (free_link *)malloc(sizeof(free_link));
                t->next = NULL;
                t->start_location = s->begin_location;
                t->free_number = s->office_number;
                if (r == NULL)
                    p = t;
                if (r != NULL && r->next == NULL)
                {
                    if (r->start_location < s->begin_location)
                        r->next = t;
                    else
                    {
                        t->next = r;
                        p = t;
                    }
                }
                if (r != NULL && r->next != NULL)
                {
                    while (r != NULL && r->next != NULL)
                    {
                        if ((r->start_location < s->begin_location) && (s->begin_location < r->next->start_location))
                            break;
                        r = r->next;
                    }
                    t->next = r->next;
                    r->next = t;
                }
            }
            for (i = s->begin_location; i < (s->begin_location + s->office_number); i++)
                WST[i] = 0;
            while (e != NULL)
            {
                if (e->next == s)
                    break;
                e = e->next;
            }
            e->next = s->next;
            free(s);
        }
    }
    w->p = p;
    w->q = q;
    return w;
}

int main(){
    system("chcp 65001");
    int flag=-1;
    work *w;
    zero_wst();
    w=start();
    while(1){
        system("cls");
        print_wst(WST);
        print_office(w); 
        menu();
        cin>>flag;
        if(cin.fail()){
            cin.clear(); 
            cin.sync();
        }
        switch(flag){
            case 1:w=request(w,WST);break;
            case 2:w=delect(w,WST);break;
            case 3:exit(0);
            default:printf(" 输入错误 ,请重新输入 !\n");break;
        }
    }
    return 0;
} 