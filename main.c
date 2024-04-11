// This code fully mine (unfinished) 

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <conio.h>

#define LENGTH  100
#define WIDTH   60
#define HEIGHT  26

void drawMap();
void getRandomApple();

int userX = WIDTH / 2;
int userY = HEIGHT / 2;

int tailX[100], tailY[100];
int nTail = 0;

int apples = 0;
int count = 0;

int appleX = 5;
int appleY = 5;

bool up;
bool down;
bool left;
bool right;

bool gameOver = false;

bool appleEaten = false;

int main(void)
{
    setlocale(LC_ALL, "rus");
    while(!gameOver)
    {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = userX;
        tailY[0] = userY;

        for (int i = 1; i < nTail; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        

        if(appleEaten == true)
            getRandomApple();

        drawMap();
        
        if(_kbhit()) {
            switch (_getch())
            {
            case 'w': case 'W':
                up = true;
                down = false;
                left = false;
                right = false;
                break;
            case 's': case 'S':
                up = false;
                down = true;
                left = false;
                right = false;
                break;
            case 'a': case 'A':
                up = false;
                down = false;
                left = true;
                right = false;
                break;
            case 'd': case 'D':
                up = false;
                down = false;
                left = false;
                right = true;
                break;
            }
        }

        if(up) userY--;
        else if(down) userY++;
        else if(right) userX++;
        else if(left) userX--;

        if(userX == WIDTH) userX = 1;
        else if(userX == 0) userX = WIDTH-1;
        else if(userY == HEIGHT) userY = 1;
        else if(userY == 0) userY = HEIGHT-1; 

        if(userX == appleX && userY == appleY) {
            appleEaten = true;
            apples++;
            nTail++;
        }
        else appleEaten = false;

        if(userX >= WIDTH || userX < 0 || userY > HEIGHT || userY < 0) 
            gameOver = true;
        
        for (int i = 0; i < nTail; i++)
            if(tailX[i] == userX && tailY[i] == userY)
                gameOver = true;
               
        system("cls");
    }
    printf("\n\nGame Over!\n\n");
    char penis;
    scanf("%c", &penis);
    return 0;
}

void drawMap()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if(y == 0 || y == HEIGHT-1) printf("#");
            else if(x == 0 || x == WIDTH - 1) printf("#");  
            else if(x == userX && y == userY) printf("0");  // отрисовка головы змейки
            else if(x == appleX && y == appleY) printf("@");  // отрисовка яблока
            else 
            { 
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if(tailX[k] == x && tailY[k] == y) 
                    { 
                        print = true;
                        printf("o");
                    }
                }
                if(!print) printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", apples);
}

void getRandomApple()
{
    srand(time(NULL));

    appleX = rand() % WIDTH;
    appleY = rand() % HEIGHT;
}