#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
void CharCount(char path[]);  //字符统计
void WordCount(char path[]);  //单词统计
void LineCount(char path[]);  //行数统计
void AllCount(char path[]);  //综合统计(代码行，空行，注释行)
int main()
{
    char input[100],path[50];
    printf("-c 文件地址 返回字符数\n");
    printf("-w 文件地址 返回单词数\n");
    printf("-l 文件地址 返回行数\n");
    printf("-a 文件地址 返回代码行、空行、注释行数\n");
    printf("请输入命令:");
    gets(input);
    int count=strlen(input);
    strncpy(path, input + 10,  count - 10);//将命令行输入的地址赋值给path
    path[count - 9] = '\0';//路径结尾添加结束符，避免统计类型时出错
    int check = 1; 
    //检查类型
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

void CharCount(char path[]) //字符统计函数
{
    FILE *fp=NULL;
    int a = 0;
    char ch;
    char *path_1 = path;
    int k = strlen(path);
    *(path_1 + k-1) = '\0';
    if ((fp = fopen(path_1 , "r")) == NULL)
    {
        printf("文件读取失败");
        exit(0);
    }
    ch = fgetc(fp);
    while (ch != EOF)
    {
        a++;
        ch = fgetc(fp);
    }
    printf("字符数 ：%d\n", a);
    fclose(fp);
}

void WordCount(char path[]) //单词统计函数
{
    FILE *fp;
    int b = 0;
    char ch;
    char *path_1 = path;
    int k = strlen(path);
    *(path_1 + k - 1) = '\0';
    if ((fp = fopen(path_1, "r")) == NULL)
    {
        printf("文件读取失败");
        exit(0);
    }
    //fgetc()会返回读取到的字符，若返回EOF则表示到了文件尾，或出现了错误。
    ch = fgetc(fp);
    while (ch != EOF)
    {
        if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9'))//非空
        {
            while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9') || ch == '_')
            {
                ch = fgetc(fp);//直到遇见非字母/数字/下划线
            }
            b++;
            ch = fgetc(fp);
        }
        else
        {
            ch = fgetc(fp);
        }
    }
    printf("单词数：%d.\n", b);
    fclose(fp);

}

void LineCount(char path[]) //行数统计函数
{
    FILE *fp;
    int c = 1;
    char ch;
    char *path_1 = path;
    int k = strlen(path);
    *(path_1 + k - 1) = '\0';
    if ((fp = fopen(path_1, "r")) == NULL)
    {
        printf("文件读取失败");
        exit(0);
    }
    //fgetc()会返回读取到的字符，若返回EOF则表示到了文件尾，或出现了错误。
    ch = fgetc(fp);
    //如果是换行符则l（line）++，否则继续读取下一个字符
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
    printf("行数：%d.\n", c);
    fclose(fp);
}

void AllCount(char path[])  //综合统计函数，包括代码行，空行，注释行
{
    FILE *fp;
    char ch;
    char *path_1 = path;
    int k = strlen(path);
    *(path_1 + k - 1) = '\0';
    int d = 0, e = 0, f = 0;
    if ((fp = fopen(path_1, "r")) == NULL)
    {
        printf("文件读取失败");
        exit(0);
    }
    //fgetc()会返回读取到的字符，若返回EOF则表示到了文件尾，或出现了错误。
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
    printf("代码行数 ：%d.\n", d);
    printf("空行数 ：%d.\n", e);
    printf("注释行数 ：%d.\n", f);
    fclose(fp);
}
