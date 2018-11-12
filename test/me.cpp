#include<stdio.h>
#define s "#include<stdio.h>%c#define s %c%s%c%cint main(){%c%cprintf(s,10,34,s,34,10,10,9,10,9,10);%c%creturn 0;%c}"
int main(){
	printf(s,10,34,s,34,10,10,9,10,9,10);
	return 0;
}