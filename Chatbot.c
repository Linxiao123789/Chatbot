#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define SMAX 99999
#define LSMAX 5
//ADT about list
typedef struct talk
{
int power;
char in[SMAX];
char out[SMAX];
struct talk * next;
} Talk;
Talk Head;//链表头
//int InitList(void);//初始化函数的定义
int AddItem(char *in,char *out);//添加节点函数
//int PrintList(void);//输出所有节点的值函数
int ReadData(void);//读取数据函数
int Parser(char *);//答复模块函数
int GetKey(char *,const char *);//比对关键词函数

int main(void)
{
    memset(&Head,0,sizeof Head);
    //初始化Head
    char input[SMAX];
    //printf("1 ");
    ReadData();
    printf("Hello, I'm Mr.zero, what's your name?\n");
    gets(input);
    printf("Oh, nice to meet you, %s!\nTipe q if you want to quit.\n",input);
    //if(input == "q")
    //exit(1);
    while(1)
    {
        gets(input);
        Parser(input);
    }

    return 0;
}
/*
int PrintList(void)
{
    Talk *point = Head.next;
    while(point!=NULL)
    {
        printf("in %s ",point->in);
        printf("out %s \n",point->out);
        point = point->next;
    }
    return 0;
}
*/
int AddItem(char *in,char *out)
{
    Talk *point=&Head;
    while(point->next!=NULL)
    point = point ->next;
    Talk *temp = (Talk *)malloc(sizeof (Talk));
    if(temp==NULL)
    {
        printf("内存分配错误\n");
        exit(1);
    }
    memset(temp,0,sizeof(Talk));
    strcpy(temp->in,in);
    strcpy(temp->out,out);
    point->next=temp;
    //printf("2 ");
    return 1;
}


int ReadData(void)
{
    char inbuf[SMAX];
    char outbuf[SMAX];
    FILE *fp = NULL;
    fp = fopen( "temp.txt", "r+" );
    while(!feof(fp))
    {
    fgets(inbuf,SMAX,fp);
    if (inbuf[strlen(inbuf)-1] == '\n')
        inbuf[strlen(inbuf)-1] = '\0';
    fgets(outbuf,SMAX,fp);
    if (outbuf[strlen(outbuf)-1] == '\n')
        outbuf[strlen(outbuf)-1] = '\0';
    AddItem(inbuf,outbuf);
    }
    fclose(fp);
    //printf("3 ");
    return 0;
}


int GetKey(char *in,const char *kw)
{
    int i,j=0;
    for(i=0;in[i]!=0;i++)
    {
        if(in[i]==kw[j])
        {
            while(in[i]==kw[j]&&in[i]!=0)//第一个字符匹配则继续检查下一个字符，直到不匹配
            {
                i++;
                j++;
            }
            if(kw[j]==0)//如果不匹配时关键字的所有字符都匹配过了，到了\0，那么就是配对成功
            {
                return 1;//成功返回1
            }
            else j=0;//j是关键词的首字母指针，如果不匹配就要归回原位等待下一次匹配
        }
    }
    //printf("4 ");
    return 0;
}

int Parser(char *in)
{
    Talk *point=Head.next;
    while(point!=NULL)
    {
        if(GetKey(in,point->in))//返回是否匹配，1 匹配 0 不匹配，用函数来使程序更加清晰
        {
            puts(point->out);
            //printf("5 ");
            return 1;
        }
        point = point->next;
    }
    if(point==NULL)
    printf("听不懂那个\n");
    return 0;
}
