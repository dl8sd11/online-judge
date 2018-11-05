#include <bits/stdc++.h>
using namespace std;

class game{

private:
  int cell[4][4] = {};

public:
  void print_cell(){
    system("clear");
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        cout<<setw(6)<<cell[i][j];
      }
      cout<<endl;
    }
  }

  void generate_random_cell(){
    vector<pair<int,int> > available;
    for(int i=0;i<4;i++)
      for(int j=0;j<4;j++)
        if(cell[i][j]==0)available.push_back({i,j});

    int choice = rand() % int(available.size());
    cell[available[choice].first][available[choice].second] = (rand()%10?2:4);
    print_cell();
  }


};
int main(){
  game root;
  root.print_cell();
  for(int i=0;i<5;i++)root.generate_random_cell();
  return 0;
}
