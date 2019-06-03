#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int main()
{
	for(int i=1;i<=10;i++)
	{
		char cmd[100];
		sprintf(cmd,"cp and%d.in and.in",i);
		system(cmd);
		system("time ./and");
		sprintf(cmd,"diff and.out and%d.out",i);
		if(!system(cmd))
			printf("%d AC\n",i);
		else
			return printf("%d WA\n",i),0;
	}
	return 0;
}