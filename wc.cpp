#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
void CharCount(char path[]);  //�ַ�ͳ��
void WordCount(char path[]);  //����ͳ��
void LineCount(char path[]);  //����ͳ��
void AllCount(char path[]);  //�ۺ�ͳ��(�����У����У�ע����)
int main()
{
    char input[100],path[50];
    printf("-c �ļ���ַ �����ַ���\n");
    printf("-w �ļ���ַ ���ص�����\n");
    printf("-l �ļ���ַ ��������\n");
    printf("-a �ļ���ַ ���ش����С����С�ע������\n");
    printf("����������:");
    gets(input);
    int count=strlen(input);
    strncpy(path, input + 10,  count - 10);//������������ĵ�ַ��ֵ��path
    path[count - 9] = '\0';//·����β��ӽ�����������ͳ������ʱ����
    int check = 1; 
    //�������
    while (check)
    {
        int i = 7;
        if ((input[i] == '-') && (input[i + 1] == 'c'))
        {
            CharCount(path);
            break;
        }
        if ((input[i] == '-') && (input[i + 1] == 'w'))
        {
            WordCount(path);
            break;
        }
        if ((input[i] == '-') && (input[i + 1] == 'l'))
        {
            LineCount(path);
            break;
        }
        if ((input[i] == '-') && (input[i + 1] == 'a'))
        {
            AllCount(path);
            break;
        }
    }
    return 0;
}

void CharCount(char path[]) //�ַ�ͳ�ƺ���
{
    FILE *fp=NULL;
    int a = 0;
    char ch;
    char *path_1 = path;
    int k = strlen(path);
    *(path_1 + k-1) = '\0';
    if ((fp = fopen(path_1 , "r")) == NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    ch = fgetc(fp);
    while (ch != EOF)
    {
        a++;
        ch = fgetc(fp);
    }
    printf("�ַ��� ��%d\n", a);
    fclose(fp);
}

void WordCount(char path[]) //����ͳ�ƺ���
{
    FILE *fp;
    int b = 0;
    char ch;
    char *path_1 = path;
    int k = strlen(path);
    *(path_1 + k - 1) = '\0';
    if ((fp = fopen(path_1, "r")) == NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    //fgetc()�᷵�ض�ȡ�����ַ���������EOF���ʾ�����ļ�β��������˴���
    ch = fgetc(fp);
    while (ch != EOF)
    {
        if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9'))//�ǿ�
        {
            while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9') || ch == '_')
            {
                ch = fgetc(fp);//ֱ����������ĸ/����/�»���
            }
            b++;
            ch = fgetc(fp);
        }
        else
        {
            ch = fgetc(fp);
        }
    }
    printf("��������%d.\n", b);
    fclose(fp);

}

void LineCount(char path[]) //����ͳ�ƺ���
{
    FILE *fp;
    int c = 1;
    char ch;
    char *path_1 = path;
    int k = strlen(path);
    *(path_1 + k - 1) = '\0';
    if ((fp = fopen(path_1, "r")) == NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    //fgetc()�᷵�ض�ȡ�����ַ���������EOF���ʾ�����ļ�β��������˴���
    ch = fgetc(fp);
    //����ǻ��з���l��line��++�����������ȡ��һ���ַ�
    while (ch != EOF)
    {
        if (ch == '\n')
        {
            c++;
            ch = fgetc(fp);
        }
        else
        {
            ch = fgetc(fp);
        }
    }
    printf("������%d.\n", c);
    fclose(fp);
}

void AllCount(char path[])  //�ۺ�ͳ�ƺ��������������У����У�ע����
{
    FILE *fp;
    char ch;
    char *path_1 = path;
    int k = strlen(path);
    *(path_1 + k - 1) = '\0';
    int d = 0, e = 0, f = 0;
    if ((fp = fopen(path_1, "r")) == NULL)
    {
        printf("�ļ���ȡʧ��");
        exit(0);
    }
    //fgetc()�᷵�ض�ȡ�����ַ���������EOF���ʾ�����ļ�β��������˴���
    ch = fgetc(fp);
    while (ch != EOF)
    {
        if (ch == '{' || ch == '}')
        {
            e++;
            ch = fgetc(fp);
        }
        else if (ch == '\n')
        {
            ch = fgetc(fp);
            while (ch == '\n')
            {
                e++;
                ch = fgetc(fp);
            }
        }
        else if (ch == '/')
        {
            ch = fgetc(fp);
            if (ch == '/')
            while (ch != '\n')
            {
                ch = fgetc(fp);
            }
            f++;
            ch = fgetc(fp);
        }
        else
        {
            d++;
            while (ch != '{'&&ch != '}'&&ch != '\n'&&ch != '/'&&ch != EOF)
            {
                ch = fgetc(fp);
            }
        }

    }
    printf("�������� ��%d.\n", d);
    printf("������ ��%d.\n", e);
    printf("ע������ ��%d.\n", f);
    fclose(fp);
}
