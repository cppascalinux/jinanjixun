#include<windows.h>
#include<cstdio>
int main()
{
	int n=0;
	while(1)
	{
		printf("%d\n",++n);
		system("data.exe");system("guess.exe");system("force.exe");
		if(system("fc guess.out force.out"))
		{
			printf("Oops");
			system("pause");
		}
	}
}
