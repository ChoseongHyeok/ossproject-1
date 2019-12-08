#include <stdio.h>
#include <stdio.h>
#include "stdlib.h"
int main()
{
	FILE *fp;
	FILE *fp1;
	int state;
	int i=1;
	char val[256];
	char buf[256];	
	char al[256];
	char al2[256];

		printf("Please enter the file you want to find(exit==no) : ");
		scanf("%s",val);
		sprintf(buf,"find %s.*",val);
		fp = popen(buf,"r"); // Practice 'find val.*'
		if(fp == NULL) // if it doesn't exist, take it to the next level
		{
			system("mkdir ZIP"); // make a derectory, name=ZIP
		       	sprintf(al,"unzip *.zip -d/home/ZIP");
			system(al); // unzipe *.zip
			system("cd ZIP"); // Access in derectory ZIP

			fp1 = popen(buf,"r"); // Practice 'find val.*'
			if(fp1 == NULL)
			{
				printf("File not exist");
			}
			printf("%s",fp1);
			sprintf(al2,"mv /home/ZIP/%s.* /home/%s.*",val,val);
			system(al2); // move present derectory
			pclose(fp1);
		}
		printf("%s",fp);
	
	state = pclose(fp);
	return 0;
}
