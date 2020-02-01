#include "Land.h"

typedef long long ll;
const int MAXC = 1000000000;
#include <map>

std::map<int,ll> ansX, ansY;
rectangle find_rectangle(int subtask){
	rectangle answer;
	long long query = area(0, 0, 1, 1);

	int xL = 0, xR = MAXC;
	while (xL < xR - 1) {
        int xM = (xL + xR) >> 1;
        ll ret = area(0,0,xM, MAXC);
        ansX[xM] = ret;
        if (ret > 0) {
            xR = xM;
        } else {
            xL = xM;
        }
	}

	int yL = 0, yR = MAXC;
	while (yL < yR - 1) {
        int yM = (yL + yR) >> 1;
        ll ret = area(0,0, MAXC, yM);
        ansY[yM] = ret;
        if (ret > 0) {
            yR = yM;
        } else {
            yL = yM;
        }
	}

	int xD, yD;
	if (ansY.count(yR)) {
        xD = ansY[yR];
	} else {
	    xD = area(0, 0, MAXC, yR);
	}

	if (ansX.count(xR)) {
        yD = ansX[xR];
	} else {
	    yD = area(0, 0, xR, MAXC);
	}


	answer.a=xL, answer.b=yL, answer.c=xL+xD, answer.d=yL+yD;
	return answer;
}


