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
int mapLoaded=0;       //����ָʾ�����Ƿ��е�ͼ��
int mapDesigning=0;    //����ָʾ�����Ƿ��ڵ�ͼ���ģʽ��

void printWelcome()
{
    printf("*********************************\n");
    printf("*********************************\n");
    printf("       \n");
    printf("        ��   ��   ��   Ϸ\n");
    printf("    \n");
    printf("         ��ӭ����������Ϸ\n");
    printf(" ������������ᵽԪ���Զ�������Ȥ\n");
    printf(" \n");
    printf("            ׼��������\n");
    printf(" \n");
    printf("*********************************\n");
    printf("*********************************\n");
    printHelp();
}

void printHelp()
{
    printf("\t[\\h]\t��ӡ������ʾ\n");
    printf("\t[\\p]\t��ӡ��ǰ��ͼ\n");
    printf("\t[\\l]\t�����ͼ\n");
    printf("\t[\\s]\t�����ͼ\n");
    printf("\t[\\d]\t�����ͼ���ģʽ\n");
    printf("\t[\\q]\t�˳���ͼ���ģʽ\n");
    printf("\t[\\a]\t������ɵ�ͼ\n");
    printf("\t[\\g]\t������һ������\n");
    printf("\t[\\r]\t��ʼ������Ϸ\n");
    printf("\t[\\e]\tֹͣ������Ϸ\n");
    printf("\t[end]\t�˳���Ϸ\n");
}

void printCurrentMap(int row,int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf(currentMap[i][j]>0?"��":"��");
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
    printf("���ڡ������ͼ��ģʽ��\n");
    printf("������Ҫ�򿪵ĵ�ͼ�ļ���\n");
    gets(mapName);
    FILE *fp;
    fp=fopen(mapName,"r");
    if (!fp)
    {
        printf("��ͼ����ʧ�ܣ�\n");
        printf("\t[\\l]\t���µ����ͼ\n");
        printf("\t[\\d]\t�����ͼ���ģʽ\n");
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
        printf("��ͼ����ɹ�����ͼ������%s\n",mapName);
        printCurrentMap(currentRow,currentCol);
        printf("\t[\\g]\t������һ������\n");
        printf("\t[\\r]\t��ʼ������Ϸ\n");
    }
}

void newMap()
{
    printf("��ӭǰ�������ͼ��\n");
    printf("��������Ҫ��Ƶĵ�ͼ������������:\n�����븡����������ǿ��ת��Ϊ������\n");
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
            printf("���벻�Ϸ�������������\n");
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
        printf("��������Ҫ�ı�����״̬��ϸ������:�����Ͻ�Ϊ0 0 ��\n�����븡����������ǿ��ת��Ϊ������\n��������ĸ���������ı䣨0��0��������״̬��\n");
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
                printf("���λ�ò��Ϸ�������������\n");
            }
            else
            {
                currentMap[row][column]=!currentMap[row][column];
                printf("���º��ϸ��ͼΪ\n");
            }
            printCurrentMap(currentRow,currentCol);
            printf("�������ɣ�Ҫ�˳���ƣ�������\\q�Լ������ַ�\n");
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
    printf("����������ı�ϸ������״̬������\n");
    scanf("%d",&n);
    for(int i=0; i<=n-1; i++)
    {
        int x=((rand())%currentRow);
        int y=((rand())%currentCol);
        currentMap[x][y]=!currentMap[x][y];
    }
    printCurrentMap(currentRow,currentCol);
    fflush(stdin);
    printf("\t[\\s]\t���������ͼ\n");
    printf("�粻�������棬�����ͼ���ٴ���ơ����ɵ�ͼ��˵�ͼ����ʧ\n");
}

void saveMap()
{
    char mapName[101];
    printf("���ڱ����ͼ\n");
    printCurrentMap(currentRow,currentCol);
    printf("�������ļ���\n");
    gets(mapName);
    FILE *fp;
    fp=fopen(mapName,"w+");
    if (!fp)
    {
        printf("��Ч�����ƣ�����ʧ��\n����\\s���±���");
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
        printf("�����ͼ�ɹ�����ͼ��Ϊ%s\n",mapName);
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
        printf("������Ϸ���ڽ��У��Զ�������\n���س�����ͣ����\n");
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
    printf("������Ϸ�Ѿ�ֹͣ\n");
    printCurrentMap(currentRow,currentCol);
    printf("\t[\\l]\t�����ͼ\n");
    printf("\t[\\d]\t�����ͼ���ģʽ\n");
    printf("\t[\\r]\t���¿�ʼ������Ϸ\n");
}

void exitgame()
{
    system("cls");
    printf("�Ѿ��˳���Ϸ��Goodbye��\n�����������ݹر�");
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
    int gameRunning=0;       //����ָʾ�����Ƿ���������������Ϸ
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
                printf("��û����ƹ���ͼ���ڽ�����Ϸ�������ͼʧ��\n");
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
                printf("�Ѿ�������һ��ϸ��\n");
                printCurrentMap(currentRow,currentCol);
                printf("\t[\\g]\t������һ������\n");
                printf("\t[\\r]\t��ʼ������Ϸ\n");
            }
            else
            {
                printf("����û�е�ͼ�أ�\n�����²���\n");
                printHelp();
            }
            break;
        case 6:
            system("cls");
            if (mapLoaded)
            {
                gameRunning=1;
                printf("��ʼ������Ϸ\n�Զ����п�ʼ\n");
                rungame();
                printf("\t����\\r������Ϸ�Զ�����\n");
                printf("\t[\\s]\t�����ͼ\n");
                printf("\t[\\g]\t������һ������\n");
                printf("\t[\\e]\tֹͣ������Ϸ\n");

            }
            else
            {
                printf("����û�е�ͼ�أ�\n�����²���\n");
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
                printf("�����ڽ���������Ϸ\n");
                printf("\t[\\h]\t��ӡ������ʾ\n");
                printHelp();
            }
            break;
quitDesign:
        case 8:
            if(mapDesigning)
            {

                system("cls");
                printf("�Ѿ��˳���ͼ���ģʽ\n");
                printf("\t[\\s]\t���������ͼ\n");
                printf("�粻�������棬�����ͼ���ٴ���Ƶ�ͼ��˵�ͼ����ʧ\n");
            }
            else
            {
                system("cls");
                printf("����û����Ƶ�ͼ��\n");
                printHelp();
            }
            break;
        case 9:
            system("cls");
            if (mapLoaded)
            {
                printf("��ӡ��ǰ��ͼ\n��ǰ��ͼΪ\n");
                printCurrentMap(currentRow,currentCol);
            }
            else
            {
                printf("����û�е�ͼ�أ�\n�����²���\n");
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
            printf("\t\t�Ƿ����룬����������\n");
            printHelp();
        }
    }
    return 0;
}
