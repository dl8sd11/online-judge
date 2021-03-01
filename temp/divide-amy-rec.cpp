#include <iostream>

using namespace std;

int n = 1, size_;
int v[100];
int p1[100];
int p2[100];
int p3[100];
void distribution ( int, int, int, int, int);
bool has_ans = false;

int main()
{
    while(n != -1)   //因為已給n初始值(n=1),所以一開始就會進入此迴圈
    {
        cout << "       *Welcome to NCU-EE Mediation Committee*        " << endl;
        cout << "Please enter the number of treasures or -1 to end the program: ";
        cin >> n;
        if(n == -1)   //若輸入-1則結束此程式
        {
            cout << "*Bye-Bye*" << endl;
            return 0;
        }
        cout << "Please enter the size of backpack: ";
        cin >> size_;   //輸入背包的大小

        for(int i = 0; i < n; i++)
        {
            cout << "Treasure " << i + 1 << " ($): ";
            cin >> v[i];   //輸入寶藏的價值 //把每個寶藏的價值存放到一個array裡
        }

        cout << "......Distribution......Distribution......Distribution......" << endl;

        distribution ( 1, 0, 0, 0, 0 );
        distribution ( 2, 0, 0, 0, 0 );
        distribution ( 3, 0, 0, 0, 0 );

        if(has_ans != true)
            cout << "NO" << endl;

        cout << "\n***Thanks and Come Again***\n" << endl;

        has_ans = false;
    }
    return 0;
}

void distribution ( int person, int amount, int a, int b, int c)
{
    if(has_ans == true)
        return;

    if(person == 1)
    {
        p1[a] = amount;
        a++;
    }
    if(person == 2)
    {
        p2[b] = amount;
        b++;
    }
    if(person == 3)
    {
        p3[c] = amount;
        c++;
    }

    if(a > size_)
        return;
    if(b > size_)
        return;
    if(c > size_)
        return;

    int av = 0, bv = 0, cv = 0;

    for(int i = 0; i < a; i++)
        av += v[p1[i]];

    for(int i = 0; i < b; i++)
        bv += v[p2[i]];

    for(int i = 0; i < c; i++)
        cv += v[p3[i]];

    if(amount == n - 1)
    {
        if((av == bv) && (av == cv))  //看是不是每個人背包裡的寶藏價值都一樣
        {
            cout << "YES" << endl;
            for(int i = 0; i < 3; i++)
            {
                cout << "People " << i + 1 << " : ";
                if(i == 0)
                {
                    for(int l = 0; l < a; l++)
                        cout << "Treasure " << p1[l] + 1 << "  ";
                }
                if(i == 1)
                {
                    for(int l = 0; l < b; l++)
                        cout << "Treasure " << p2[l] + 1 << "  ";
                }
                if(i == 2)
                {
                    for(int l = 0; l < c; l++)
                        cout << "Treasure " << p3[l] + 1 << "  ";
                }
                cout << endl;
            }
            has_ans = true;
        }
        return;
    }

    distribution ( 1, amount + 1, a, b, c );
    distribution ( 2, amount + 1, a, b, c );
    distribution ( 3, amount + 1, a, b, c );
}
