#include <iostream>
using namespace std;
int main(){
	int N;
	cin>>N;
	char **p;
	p=new char*[N];
	//s
	int *num;
	num=new int[N];
	for(int i=0;i<N;i++){
		num[i]=0;
	}
	//e
	for(int i=0;i<N;i++){
		p[i]=new char[101];
		cin>>p[i];
		//s
		for(int j=0;j<101;j++){
			if(p[i][j]=='\0'){
				break;
			}
			num[i]++;
		}
		//e
	}
	int a,b;
	while(cin>>a>>b){
		/*int count1=0,count2=0;
		int i1=0,i2=0;
		while(p[a][i1]!='\0'||){
			count1++;
			i1++;
		}
		while(p[b][i2]!='\0'){
			count2++;
			i2++;
		}*/  //origin
		char *q;
		//q=new char[count1+count2];
		int s=num[a]+num[b];
		q=new char[s+1];
		for(int i=0;i<num[a];i++){
			q[i]=p[a][i];
		}
	    q[num[a]+num[b]] = NULL;
		delete [] p[a];
		p[a]=q;
		for(int i=num[a];i<num[a]+num[b];i++){
			p[a][i]=p[b][i-num[a]];
		}
		//upper p is fine
		delete [] p[b];
		for(int i=b;i<N-1;i++){
			p[i]=p[i+1];
		}
        p[N-1] = NULL;
		N--;
		num[a]+=num[b];
		for(int i=b;i<N;i++){
			num[i]=num[i+1];
		}
		/*for(int i=0;i<N;i++){
		cout<<"test 1: "<<p[i]<<endl;
		}*/
	}
	for(int i=0;i<N;i++){
		cout<<p[i]<<endl;
	}
	for(int i=0;i<N;i++){
		delete [] p[i];
	}
    delete [] p;
	delete [] num; 
	return 0;
}
