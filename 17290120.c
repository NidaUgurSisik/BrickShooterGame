#include <stdio.h>
#include <stdlib.h>
int fcx, fcy, bx, by, check, SumScore = 0;
void funcdraw(int x, int y, char **brick);
void funcScore(int check);
int funcMap(int x, int y, char **brick);
void funcmotion(float speedx, float speedy, float cx, float cy, char **brick, char ch);
int funccheck(int fcx, int fcy, char colour, char **brick);
char ch, colour;
int main()
{

    int i, x, y, sx, sy, Score, colourCount = 0, r = 0, brickgame = 1;
    int pcheck;
    float cx, cy, speedx, speedy;
    char color[1000];
    scanf("%d%d", &x, &y);
    char **brick = (char **)malloc(y * sizeof(char *));
    for (int i = 0; i < y; i++)
        brick[i] = malloc(x * sizeof(char));
    while (1)
    {
        scanf("%c", &ch);
        if (ch == 'e')
            break;
        if (ch == '\n')
            continue;
        color[colourCount] = ch;
        colourCount++;
    }
    scanf("%c%c", &ch, &ch);
    scanf("%d%d", &sx, &sy);

    cx = sx;
    cy = sy;
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (i == 0 && j < x - 1 && j > 0)
                brick[i][j] = '~';
            else if (j == x - 1 || j == 0)
                brick[i][j] = '|';
            else if (r < colourCount)
            {
                brick[i][j] = color[r];
                r++;
            }
            else if (i == sy && j == sx)
                brick[i][j] = '_';
            else
                brick[i][j] = ' ';
        }
    }

    funcdraw(x, y, brick);
    scanf(" %c", &ch);
    while (ch != 'q')
    {
        colour = ch;
        scanf("%f %f", &speedx, &speedy);
        funcmotion(speedx, speedy, cx, cy, brick, ch);
        pcheck = funccheck(fcx, fcy, ch, brick);
        funcScore(pcheck);
        funcdraw(x, y, brick);
        scanf(" %c", &ch);
        if (ch == 'q' || funcMap(x, y, brick) == 1)
        {
            printf("Game is over. Your score is %d!\n", SumScore);
            break;
        }
    }
    return 0;
}
//draw function
void funcdraw(int x, int y, char **brick)
{

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            printf("%c", brick[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
//motion function
void funcmotion(float speedx, float speedy, float cx, float cy, char **brick, char ch)
{
    int motionflag = 1, bx, by, x, ax, ay;
    speedx /= 50;
    speedy /= 50;

    while (motionflag)
    {
        bx = cx;      //bx=before x
        by = cy;      //by=before y
        cx += speedx; //cx=color x
        cy += speedy; //cy=color y
        ax = cx;      //ax=after x
        ay = cy;      //ay=after y
        if (brick[ay][ax] != ' ' && brick[ay][ax] != '|')
        {
            motionflag = 0;
            brick[by][bx] = ch;
            fcy = by;
            fcx = bx;
        }
        if (brick[ay][ax] == '|')
        {
            cy -= speedy;
            speedx = -speedx;
            continue;
        }
        if (brick[ay][ax] == ' ')
        {
            continue;
        }
    }
}
//check function
int funccheck(int fcx, int fcy, char colour, char **brick)
{
    int i, j, check = 0;
    if (brick[fcy - 1][fcx - 1] == colour)
        check++;
    if (brick[fcy - 1][fcx] == colour)
        check++;
    if (brick[fcy - 1][fcx + 1] == colour)
        check++;
    if (brick[fcy][fcx - 1] == colour)
        check++;
    if (brick[fcy][fcx + 1] == colour)
        check++;
    if (brick[fcy + 1][fcx - 1] == colour)
        check++;
    if (brick[fcy + 1][fcx] == colour)
        check++;
    if (brick[fcy + 1][fcx + 1] == colour)
        check++;
    if (check >= 2)
    {

        for (i = fcx - 1; i <= fcx + 1; i++)
        {
            for (j = fcy - 1; j <= fcy + 1; j++)
                if (brick[j][i] == colour)
                    brick[j][i] = ' ';
        }
    }
    return check;
}
void funcScore(int pcheck)
{

    int Score = 0;
    if (pcheck == 2)
    {
        Score = 10 * (pcheck + 1);
        SumScore += Score;
        printf("You got %d points. Score: %d\n", Score, SumScore);
    }
    if (pcheck == 3)
    {
        Score = 10 * (pcheck + 1);
        SumScore += Score;
        printf("You got %d points. Score: %d\n", Score, SumScore);
    }
    if (pcheck > 3)
    {
        Score = 100;
        SumScore += Score;
        printf("You got %d points. Score: %d\n", Score, SumScore);
    }
}
int funcMap(int x, int y, char **brick)
{
    for (int i = 1; i < x - 1; i++)
    {

        for (int j = 1; j < y - 1; j++)
        {
            if (brick[j][i] != ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}