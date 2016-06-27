#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <ctime>
#include <fstream>

using namespace std;

ifstream in ("Walls.dat");

const short X = 20, Y = 10;
const short FACE = 2, BEC = 176, WAL = 219;
const short FPS = 33, walls=5;

int wx = X-1, tim=100, sc=0, w=0;

float x = X/3, y = Y/2, y1 = y, x1 = x, vspeed=0.0;

char mep[Y][X];
char wall[walls][Y];

void rwl(short a, short b)
{
    COORD pos = {a, b};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void GetWalls()
{
    short z;

    for (int i=0;i<3;i++)
        for (int j=0;j<Y;j++)
        {
            in>>z;

            if (z)
                wall[i][j]=WAL;
            else
                wall[i][j]=BEC;
        }
}

void init()
{

    GetWalls();

    //Declare initial map
    for (int i=0;i<Y;i++)
        for (int j=0;j<X;j++)
            mep[i][j]=BEC;

    mep[(int)y][(int)x]=FACE;


    //Draw initial map
    for (int i=0;i<Y;i++)
    {
        for (int j=0;j<X;j++)

            printf ("%c", mep[i][j]);

        printf("\n");
    }

}

void AccelBird()
{
    if (GetAsyncKeyState(VK_UP)&0x8000)
    {
        if (vspeed>-1)

            vspeed -= 0.2;
    }

    else
    {
        if (vspeed<0.9)

            vspeed += 0.15;
    }

    if ((vspeed>0&&y<Y-1)||(vspeed<0&&y>0))

        y+=vspeed;

    else

        vspeed=0;
}

void UpdateBird()
{
    if ((int)y1!=(int)y)
    {
        mep[(int)y][(int)x]=FACE;
        mep[(int)y1][(int)x]=BEC;

        rwl(x,y);

            printf("%c", mep[(int)y][(int)x]);

        rwl(x1,y1);

            printf("%c", mep[(int)y1][(int)x1]);

        y1=y;
        x1=x;
    }
}

void UpdateWall()
{

    if (wx<0)
    {
        sc++;
        tim-=10;
        w = rand() % walls;

        for (int i=0;i<Y;i++)
        {
            rwl(wx+1,i);
            mep[i][(int)wx+1]=BEC;
            printf("%c", mep[i][(int)wx+1]);
        }
    }
    else
    {
        if (wx>=0&&wx<X-1)
        {

            for (int i=0;i<Y;i++)
            {
                mep[i][(int)wx+1]=BEC;

                    if (wx==x&&wall[w][i]==-80&&i==y
                        )
                        mep[i][(int)wx]=FACE;
                    else
                        mep[i][(int)wx]=wall[w][i];

                rwl(wx,i);
                printf("%c", mep[i][(int)wx]);

                rwl(wx+1,i);
                printf("%c", mep[i][(int)wx+1]);
            }
        }
    }

}

int main()
{
    init();

    clock_t t;
    t = clock();

    while (true)
    {

        if (mep[(int)y][(int)x] == -37)
            {
            system("cls");
            printf("GAME OVER. Final score: %d!", sc);
            Sleep(1000);
            break;
            }

        if (wx<0)
            wx = X-1;

        if (clock() - t >= tim)
            {
            t = clock();
            wx --;
            }

        AccelBird();
        UpdateBird();
        UpdateWall();
        Sleep(FPS);
    }

    return 0;
}
