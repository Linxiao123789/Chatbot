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
Talk Head;//����ͷ
//int InitList(void);//��ʼ�������Ķ���
int AddItem(char *in,char *out);//��ӽڵ㺯��
//int PrintList(void);//������нڵ��ֵ����
int ReadData(void);//��ȡ���ݺ���
int Parser(char *);//��ģ�麯��
int GetKey(char *,const char *);//�ȶԹؼ��ʺ���

int main(void)
{
    memset(&Head,0,sizeof Head);
    //��ʼ��Head
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
        printf("�ڴ�������\n");
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
            while(in[i]==kw[j]&&in[i]!=0)//��һ���ַ�ƥ������������һ���ַ���ֱ����ƥ��
            {
                i++;
                j++;
            }
            if(kw[j]==0)//�����ƥ��ʱ�ؼ��ֵ������ַ���ƥ����ˣ�����\0����ô������Գɹ�
            {
                return 1;//�ɹ�����1
            }
            else j=0;//j�ǹؼ��ʵ�����ĸָ�룬�����ƥ���Ҫ���ԭλ�ȴ���һ��ƥ��
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
        if(GetKey(in,point->in))//�����Ƿ�ƥ�䣬1 ƥ�� 0 ��ƥ�䣬�ú�����ʹ�����������
        {
            puts(point->out);
            //printf("5 ");
            return 1;
        }
        point = point->next;
    }
    if(point==NULL)
    printf("�������Ǹ�\n");
    return 0;
}
