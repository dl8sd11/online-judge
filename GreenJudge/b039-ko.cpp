#include <iostream>
using namespace std;
bool col_used[100];
bool left_diag_used[100];
bool right_diag_used[100];

int ans[15],n;

void queen(int row)
{
    if(row==n+1){
        for(int i=1;i<=n;i++)cout<<ans[i]<<" \n"[i==n];
        return;
    }
    for(int col=1;col<=n;col++){
        //如果這個直線或斜線被占據了，就跳過
        if(col_used[col]) continue;
        if(left_diag_used[row+col]) continue;
        if(right_diag_used[n+row-col]) continue;
        
        //標示出這個直線和斜線都被占據了
        col_used[col]=1;
        left_diag_used[row+col]=1;
        right_diag_used[n+row-col]=1;
        
        ans[row]=col;
        queen(row+1);

        //取消，標示出這個直線和斜線都沒被佔據
        col_used[col]=0;
        left_diag_used[row+col]=0;
        right_diag_used[n+row-col]=0;
    }
}

int main()
{
    cin>>n;
    queen(1);
}
