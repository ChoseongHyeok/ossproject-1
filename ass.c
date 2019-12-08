#include <stdio.h>
#include <stdio.h>
#include "stdlib.h"
int main()
{	
	FILE *p1;
	FILE *p2;
	char output1[100];
	char output2[100];
	int state;
	int i=1;
	char val[256];
	char buf[256];	
	char al[256];
	char al2[256];

		printf("Please enter the file you want to find(exit==no) : ");
		scanf("%s",val);
		sprintf(buf,"find %s",val);
		p1 = popen(buf,"r"); // Practice 'find val.*'	
		if(p1 == NULL) // if it doesn't exist, take it to the next level
		{
			system("mkdir ZIP"); // make a derectory, name=ZIP
		       	for(int i=0;i<10;i++){
			sprintf(al,"unzip *.zip -d /home/ssgwon1/ZIP");
			}
			system(al); // unzipe *.zip
			system("cd ZIP"); // Access in derectory ZIP
		
			p2 = popen(buf,"r"); // Practice 'find val.*'

			if(p2 == NULL)
			{
				printf("File not exist");
			}
		
			else
			{
				while(fgets(output2, sizeof(output2), p2) !=NULL);
				printf("%s",output2);
			}
			sprintf(al2,"mv /home/ZIP/%s.* /home/%s.*",val,val);
			system(al2); // move present derectory
		
		
		}
		else
		{
		while(fgets(output1,sizeof(output1),p1)!=NULL);
			printf("%s",output1);
		}

	return 0;
}
