#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n = 1, size_, i, value;
    while(n != -1)   //因為已給n初始值(n=1),所以一開始就會進入此迴圈
    {
        cout << "       **Welcome to NCU-EE Mediation Committee**        " << endl;
        cout << "Please enter the number of treasures or -1 to end the program: ";
        cin >> n;
        int v[n];
        if(n == -1)   //若輸入-1則結束此程式
        {
            cout << "**Bye-Bye**" << endl;
            return 0;
        }
        cout << "Please enter the size of backpack: ";
        cin >> size_;   //輸入背包的大小

        for(int i = 0; i < n; i++)
        {
            cout << "Treasure " << i + 1 << " ($): ";
            cin >> value;   //輸入寶藏的價值
            v[i] = value;   //把每個寶藏的價值存放到一個array裡
        }
        cout << "......Distribution......Distribution......Distribution......" << endl;


        bool has_ans = false;
        for(int mask = 0; mask < pow(3,n); mask++)   //表示分配給三個人的可能方式
        {
            int total[3] = {};   //[0]:第一個人背包內的值,[1]:第二個人,[2]:第三個人 ({}為初始化 )
            int counter[3] = {};   //counter:用來計算第一、第二、第三人分別裝了幾個寶藏
            int a[n] = {};
            int b[n] = {};
            int c[n] = {};
            int acount = 0, bcount = 0, ccount = 0;
            int p = mask;   //p是第幾個可能的排列方式(以十進位表示)

            for(int j = 0; j < n; j++)   //十進位轉三進位
            {
                total[p % 3] += v[j];   //看該寶藏應該分給第幾個人
                if(p % 3 == 0)
                {
                    a[acount] = j + 1;
                    acount++;
                }
                if(p % 3 == 1)
                {
                    b[bcount] = j + 1;
                    bcount++;
                }
                if(p % 3 == 2)
                {
                    c[ccount] = j + 1;
                    ccount++;
                }

                counter[p % 3]++;   //計算此人的背包裝了幾次寶藏
                p /= 3;
            }

            int x = 0;
            for(int k = 0; k < 3; k++)
            {
                if((total[k] == total[0]) && (counter[k] <= size_))  //看是不是每個人背包裡的寶藏價值都一樣(每個都和第一個人比)
                    x++;
                else
                    break;
            }

            if(x == 3)   //看是不是三個人背包價值都一樣
            {
                cout << "YES" << endl;
                for(int i = 0; i < 3; i++)
                {
                    cout << "People " << i + 1 << " : ";
                    if(i == 0)
                    {
                        for(int l = 0; l < acount; l++)
                            cout << "Treasure " << a[l] << " ";
                    }
                    else if(i == 1)
                    {
                        for(int l = 0; l < bcount; l++)
                            cout << "Treasure " << b[l] << " ";
                    }
                    else if(i == 2)
                    {
                        for(int l = 0; l < ccount; l++)
                            cout << "Treasure " << c[l] << " ";
                    }
                    cout << endl;
                }
                has_ans = true;
                break;
            }
        }
        if(!has_ans)
            cout << "NO" << endl;

    }
    return 0;
}
