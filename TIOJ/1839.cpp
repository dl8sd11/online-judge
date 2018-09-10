#include "lib1839.h"
using namespace std;

int n;
int key[5003];
bool used[5003];
bool test[5003];
void flip(int l,int r) {
	for (int i=l;i<r;i++) {
		if (!used[i]) test[i] = !test[i];
	}
}
bool idxIsOp(int idx) {
	int ret = tryCombination(test);
	return ret>idx||ret==-1;
}
int findDoor(int idx) {
	int l=0,r=n;
	bool state = idxIsOp(idx);
	while(l+1!=r) {
		int mid = (l+r)/2;
		flip(l,mid);
		if (idxIsOp(idx)==state) {
			l = mid;
		} else {
			state = !state;
			r = mid;
		}
	}
	if (!idxIsOp(l)) flip(l,l);
	used[l] = true;
	return l;
}
int main() {
  while(1) {
    n = init();
    for (int i=0;i<n;i++) used[i] = 0;
  	for (int i=0;i<n;i++) {
  		key[findDoor(i)]=i;

  	}
  	answer(test,key);
  }

	return 0;
}
