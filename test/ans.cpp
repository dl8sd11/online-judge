#include <cstdio>
using namespace std;

int N, M;
int Set[2 * 100005];

void Initial(int N);
int Find_Root(int x);
void SetEnemy(int x, int y);
void Union(int x, int y);
void Compare(int x, int y);

int main()
{
    int Case, x, y;
    char Mode;
    scanf("%d", &Case);
    while (Case--) {
        scanf("%d %d", &N, &M);
        Initial(N);
        while (M--) {
            scanf(" %c %d %d", &Mode, &x, &y);
            if (Mode == 'A')
                Compare(x, y);
            else if (Mode == 'D')
                SetEnemy(x, y);
        }
    }
}
void Initial(int N)
{
    for (int i = 1; i <= N; ++i)
        Set[i] = i, Set[i+N] = 0;
}
int Find_Root(int x)
{
    if (x == Set[x])
        return x;
    return Set[x] = Find_Root(Set[x]);
}
void SetEnemy(int x, int y)
{
    int x_enemy = Set[x+N];
    int y_enemy = Set[y+N];

    if (x_enemy == 0) Set[x+N] = Find_Root(y);
    else Union(x_enemy, y);

    if (y_enemy == 0) Set[y+N] = Find_Root(x);
    else Union(y_enemy, x);

}
void Union(int x, int y)
{
    x = Find_Root(x);
    y = Find_Root(y);
    if (x != y)
        Set[y] = x;
}
void Compare(int x, int y)
{
    int x_root = Find_Root(x);
    int x_enemy = Find_Root(x+N);

    int y_root = Find_Root(y);
    int y_enemy = Find_Root(y+N);

    if (x_root == y_root)
        puts("In the same gang.");
    else if (x_enemy == y_root || y_enemy == x_root)
        puts("In different gangs.");
    else
        puts("Not sure yet.");
}