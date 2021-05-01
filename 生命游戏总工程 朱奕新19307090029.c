#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define HELP "\\h"
#define LOAD "\\l"
#define SAVE "\\s"
#define DESIGN "\\d"
#define GENERATE "\\g"
#define RUN "\\r"
#define EXIT "\\e"
#define QUIT "\\q"
#define PRINT "\\p"
#define AUTO "\\a"
#define END "end"
#define BUFFLEN 1024

int currentRow=0;
int currentCol=0;
int currentMap[1001][1001]= {0};
int mapLoaded=0;       //用来指示现在是否有地图了
int mapDesigning=0;    //用来指示现在是否在地图设计模式中

void printWelcome()
{
    printf("*********************************\n");
    printf("*********************************\n");
    printf("       \n");
    printf("        生   命   游   戏\n");
    printf("    \n");
    printf("         欢迎来到生命游戏\n");
    printf(" 在这里您将体会到元胞自动机的乐趣\n");
    printf(" \n");
    printf("            准备好了吗\n");
    printf(" \n");
    printf("*********************************\n");
    printf("*********************************\n");
    printHelp();
}

void printHelp()
{
    printf("\t[\\h]\t打印命令提示\n");
    printf("\t[\\p]\t打印当前地图\n");
    printf("\t[\\l]\t导入地图\n");
    printf("\t[\\s]\t保存地图\n");
    printf("\t[\\d]\t进入地图设计模式\n");
    printf("\t[\\q]\t退出地图设计模式\n");
    printf("\t[\\a]\t随机生成地图\n");
    printf("\t[\\g]\t生成下一代生命\n");
    printf("\t[\\r]\t开始生命游戏\n");
    printf("\t[\\e]\t停止生命游戏\n");
    printf("\t[end]\t退出游戏\n");
}

void printCurrentMap(int row,int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf(currentMap[i][j]>0?"■":"□");
        }
        printf("\n");
    }
}

void clearMap(int row,int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            currentMap[i][j]=0;
        }
    }
}

void loadMap()
{
    mapDesigning=0;
    char mapName[101];
    printf("正在“导入地图”模式中\n");
    printf("请输入要打开的地图文件名\n");
    gets(mapName);
    FILE *fp;
    fp=fopen(mapName,"r");
    if (!fp)
    {
        printf("地图导入失败！\n");
        printf("\t[\\l]\t重新导入地图\n");
        printf("\t[\\d]\t进入地图设计模式\n");
    }
    else
    {
        mapLoaded=1;
        fscanf(fp,"%d",&currentRow);
        fscanf(fp,"%d",&currentCol);
        for(int i=0; i<currentRow; i++)
        {
            for(int j=0; j<currentCol; j++)
            {
                fscanf(fp,"%d",&currentMap[i][j]);
            }
        }
        printf("地图导入成功！地图导入自%s\n",mapName);
        printCurrentMap(currentRow,currentCol);
        printf("\t[\\g]\t生成下一代生命\n");
        printf("\t[\\r]\t开始生命游戏\n");
    }
}

void newMap()
{
    printf("欢迎前来创造地图！\n");
    printf("请输入想要设计的地图的行数和列数:\n若输入浮点数，将被强制转化为整数！\n");
    float temprow;
    float tempcol;
    while(1)
    {
        fflush(stdin);
        scanf("%f",&temprow);
        scanf("%f",&tempcol);
        if(temprow>0&&tempcol>0&&temprow<30000&&tempcol<30000)
        {
            currentRow=(int)temprow;
            currentCol=(int)tempcol;
            break;
        }
        else
        {
            printf("输入不合法！请重新输入\n");
        }
    }
    clearMap(currentRow,currentCol);
    printCurrentMap(currentRow,currentCol);
}

void designMap()
{
    char reada[1001]= {"0"};
    char readb[1001]= {"0"};
    char *a=reada;
    char *b=readb;
    while(1)
    {
        fflush(stdin);
        printf("请输入想要改变生死状态的细胞坐标:（左上角为0 0 ）\n若输入浮点数，将被强制转化为整数！\n若输入字母，将帮您改变（0，0）的生死状态！\n");
        scanf("%s",reada);
        scanf("%s",readb);
        mapDesigning=1;
        if(strcmp(reada,QUIT))
        {
            float vala=atof(a);
            float valb=atof(b);
            int row=(int)vala;
            int column=(int)valb;
            system("cls");
            if (row<0||row>=currentRow||column<0||column>=currentCol)
            {
                printf("这个位置不合法！请重新输入\n");
            }
            else
            {
                currentMap[row][column]=!currentMap[row][column];
                printf("更新后的细胞图为\n");
            }
            printCurrentMap(currentRow,currentCol);
            printf("如设计完成，要退出设计，请输入\\q以及任意字符\n");
        }
        else
        {
            fflush(stdin);
            break;
        }

    }
}

void randomMap()
{
    mapDesigning=1;
    time_t t;
    int n;
    srand((unsigned) time(&t));
    printf("请输入随机改变细胞生死状态操作数\n");
    scanf("%d",&n);
    for(int i=0; i<=n-1; i++)
    {
        int x=((rand())%currentRow);
        int y=((rand())%currentCol);
        currentMap[x][y]=!currentMap[x][y];
    }
    printCurrentMap(currentRow,currentCol);
    fflush(stdin);
    printf("\t[\\s]\t立即保存地图\n");
    printf("如不立即保存，导入地图或再次设计、生成地图后此地图将丢失\n");
}

void saveMap()
{
    char mapName[101];
    printf("正在保存地图\n");
    printCurrentMap(currentRow,currentCol);
    printf("请输入文件名\n");
    gets(mapName);
    FILE *fp;
    fp=fopen(mapName,"w+");
    if (!fp)
    {
        printf("无效的名称，保存失败\n输入\\s重新保存");
    }
    else
    {
        fprintf(fp,"%d ",currentRow);
        fprintf(fp,"%d\n",currentCol);
        for(int i = 0; i < currentRow; i++)
        {
            for(int j = 0; j < currentCol; j++)
            {
                fprintf(fp,"%d ",currentMap[i][j]);
            }
            fprintf(fp,"\n");
        }
        fclose(fp);
        printf("保存地图成功！地图名为%s\n",mapName);
        mapDesigning=0;
    }
}

int countAliveNeighbors(int x, int y)
{
    int count=0;
    if(x==0&&y==0)
    {
        count= currentMap[0][1]+currentMap[1][0]+currentMap[1][1];
        return count;
    }
    else if(x==0&&y==currentCol-1)
    {
        count= currentMap[0][currentCol-2]+currentMap[1][currentCol-1]+currentMap[1][currentCol-2];
        return count;
    }
    else if(x==currentRow-1&&y==0)
    {
        count= currentMap[currentRow-1][1]+currentMap[currentRow-2][0]+currentMap[currentRow-2][1];
        return count;
    }
    else if(x==currentCol-1&&y==currentCol-1)
    {
        count= currentMap[currentRow-2][currentCol-1]+currentMap[currentRow-1][currentCol-2]+currentMap[currentRow-2][currentCol-2];
        return count;
    }
    else if(x==0)
    {
        count= currentMap[x][y-1]+currentMap[x][y+1]+currentMap[x+1][y-1]+currentMap[x+1][y]+currentMap[x+1][y+1];
        return count;
    }
    else if(y==0)
    {
        count= currentMap[x-1][y]+currentMap[x+1][y]+currentMap[x-1][y+1]+currentMap[x][y+1]+currentMap[x+1][y+1];
        return count;
    }
    else if(x==currentRow-1)
    {
        count= currentMap[x][y-1]+currentMap[x][y+1]+currentMap[x-1][y-1]+currentMap[x-1][y]+currentMap[x-1][y+1];
        return count;
    }
    else if(y==currentCol-1)
    {
        count= currentMap[x-1][y]+currentMap[x+1][y]+currentMap[x-1][y-1]+currentMap[x][y-1]+currentMap[x+1][y-1];
        return count;
    }
    else
    {
        count=currentMap[x-1][y-1]+currentMap[x-1][y]+currentMap[x-1][y+1]+currentMap[x][y-1]+currentMap[x][y+1]+currentMap[x+1][y-1]+currentMap[x+1][y]+currentMap[x+1][y+1];
        return count;
    }
}

void updateMap(int row,int col)
{
    int aliveNeighbors[row][col];
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            aliveNeighbors[i][j] = countAliveNeighbors(i, j);
        }
    }
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(currentMap[i][j])
            {
                if(!(aliveNeighbors[i][j]==2||aliveNeighbors[i][j]==3))
                    currentMap[i][j]=0;
            }
            else
            {
                if(aliveNeighbors[i][j]==3)
                    currentMap[i][j]=1;
            }
        }
    }
}

void rungame()
{
    char temp='0';
    long t=time(NULL);
    while(1)
    {
        system("cls");
        printf("生命游戏正在进行，自动运行中\n按回车键暂停运行\n");
        updateMap(currentRow,currentCol);
        printCurrentMap(currentRow,currentCol);
        Sleep(1000);
        if(kbhit())
        {
            temp=getch();
            if (temp=='\r')
            {
                break;
            }
        }
    }
    temp='0';
}

void endgame()
{
    printf("生命游戏已经停止\n");
    printCurrentMap(currentRow,currentCol);
    printf("\t[\\l]\t导入地图\n");
    printf("\t[\\d]\t进入地图设计模式\n");
    printf("\t[\\r]\t重新开始生命游戏\n");
}

void exitgame()
{
    system("cls");
    printf("已经退出游戏。Goodbye！\n输入任意内容关闭");
    getchar();
}

int main()
{
    printWelcome();
    int count;
    int row,column=0;
    char runcycle[1001]= {'0'};
    int branch;
    char buff[10001];
    int gameRunning=0;       //用来指示现在是否正在运行生命游戏
    while(fgets(buff,BUFFLEN, stdin))
    {
        buff[strlen(buff) - 1] = '\0';
        branch=0;
        if( !strcmp(buff,HELP))
            branch=1;
        if( !strcmp(buff,LOAD))
            branch=2;
        if( !strcmp(buff,SAVE))
            branch=3;
        if( !strcmp(buff,DESIGN))
            branch=4;
        if( !strcmp(buff,GENERATE))
            branch=5;
        if( !strcmp(buff,RUN))
            branch=6;
        if( !strcmp(buff,EXIT))
            branch=7;
        if( !strcmp(buff,QUIT))
            branch=8;
        if( !strcmp(buff,PRINT))
            branch=9;
        if( !strcmp(buff,END))
            branch=10;
        if( !strcmp(buff,AUTO))
            branch=11;

        switch (branch)
        {
        case 1:
            system("cls");
            printHelp();
            break;
        case 2:
            system("cls");
            loadMap();
            break;
        case 3:
            system("cls");
            if(mapDesigning==0&&gameRunning==0)
            {
                printf("您没有设计过地图或在进行游戏，保存地图失败\n");
                printHelp();
            }
            else
            {
                saveMap();
                mapDesigning=0;
            }
            break;
        case 4:
            system("cls");
            gameRunning=0;
            newMap();
            designMap();
            goto quitDesign;
            break;
        case 5:
            system("cls");
            if (mapLoaded)
            {
                updateMap(currentRow,currentCol);
                printf("已经生成下一代细胞\n");
                printCurrentMap(currentRow,currentCol);
                printf("\t[\\g]\t生成下一代生命\n");
                printf("\t[\\r]\t开始生命游戏\n");
            }
            else
            {
                printf("您还没有地图呢！\n请重新操作\n");
                printHelp();
            }
            break;
        case 6:
            system("cls");
            if (mapLoaded)
            {
                gameRunning=1;
                printf("开始生命游戏\n自动运行开始\n");
                rungame();
                printf("\t输入\\r继续游戏自动运行\n");
                printf("\t[\\s]\t保存地图\n");
                printf("\t[\\g]\t生成下一代生命\n");
                printf("\t[\\e]\t停止生命游戏\n");

            }
            else
            {
                printf("您还没有地图呢！\n请重新操作\n");
                printHelp();
            }
            break;
        case 7:
            system("cls");
            if (gameRunning)
            {
                endgame();
                gameRunning=0;
            }
            else
            {
                printf("您不在进行生命游戏\n");
                printf("\t[\\h]\t打印命令提示\n");
                printHelp();
            }
            break;
quitDesign:
        case 8:
            if(mapDesigning)
            {

                system("cls");
                printf("已经退出地图设计模式\n");
                printf("\t[\\s]\t立即保存地图\n");
                printf("如不立即保存，导入地图或再次设计地图后此地图将丢失\n");
            }
            else
            {
                system("cls");
                printf("您还没有设计地图！\n");
                printHelp();
            }
            break;
        case 9:
            system("cls");
            if (mapLoaded)
            {
                printf("打印当前地图\n当前地图为\n");
                printCurrentMap(currentRow,currentCol);
            }
            else
            {
                printf("您还没有地图呢！\n请重新操作\n");
                printHelp();
            }
            break;
        case 10:
            exitgame();
            return 0;
            break;
        case 11:
            system("cls");
            newMap();
            randomMap();
            break;
        default :
            system("cls");
            printf("\t\t非法输入，请重新输入\n");
            printHelp();
        }
    }
    return 0;
}
