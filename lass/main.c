
#include "kwfind.h"

int	OPTION_NAME = 0;	//옵션 플래그 초기화
int	OPTION_PERM = 0;
int	OPTION_USER = 0;
int	OPTION_GROUP = 0;
int	OPTION_TYPE = 0;
int	OPTION = 0;
int	FIND_PERM = 0;
int	FIND_TYPE = 0;

int main(int argc,char* argv[])
{
	int	i,j;

	//명령어만 입력하였을 경우 이하 모든 파일디렉토리 출력
	if(argc == 1)
	{
		kwfind(".");
		return 0;
	}

	//명령어와 경로만 입력하였을 경우 이하 모든 파일디렉토리 출력
	if(argc == 2)
	{
		printf("사용자 입력 경로 : %s\n",argv[1]);
		kwfind(argv[1]);
		return 0;
	}
 	
	//인자벡터 파싱
	for(i=1; i<argc; i++)

		if(*argv[i] == '-')
		{
			if( !strcasecmp(argv[i],"-name") )
			{
				printf("옵션 -name\n");
				OPTION_NAME = 1;
			}

			else if( !strcasecmp(argv[i],"-perm") )
			{
				printf("옵션 -perm\n");
				OPTION_PERM = 1;
			}
		
			else if( !strcasecmp(argv[i],"-user") )
			{
				printf("옵션 -user\n");
				OPTION_USER = 1;
			}
		
			else if( !strcasecmp(argv[i],"-group") )
			{
				printf("옵션 -group\n");
				OPTION_GROUP = 1;
			}
		
			else if( !strcasecmp(argv[i],"-type") )
			{
				printf("옵션 -type\n");
				OPTION_TYPE = 1;
			}

			else if( !strcasecmp(argv[i],"-print") )
				continue;

			else if( !strcasecmp(argv[i],"--help") )
			{
				usage();
				return 0;
			}

			else
			{
				fprintf(stderr,"지원하지 않는 옵션 : %s\n",argv[i]);
				fprintf(stderr,"도움말 옵션 : ./kwfind --help\n");
				usage();
				return -1;
			}
			
			OPTION = 1;
		}

	//인자가 3개 이상일때 루틴 처리
	//옵션이 없을 경우 -name 옵션생략으로 간주하여 수식처리
	if(!OPTION)
	{
		OPTION_NAME = 1;
		strcpy(NAME_PATTERN,argv[2]);
	}
	
	//옵션이 있을 경우 옵션에 따라 수식을 처리
	else
	{
		//-name 옵션에서 수식 없을 경우 모든 파일디렉토리로 간주하여 수식처리
		if((argc == 3) && OPTION_NAME)
			strcpy(NAME_PATTERN,"*");
		
		else
		{	//기타 옵션의 경우 수식을 반드시 입력받도록 처리
			if(argc < 4)
			{
				fprintf(stderr,"수식 입력이 필요합니다\n");
				usage();
				return -1;
			}
			
			//수식처리
			expression_check(argv[3]);
		}
	}

	//패스를 넘겨 파인드 시작
	kwfind(argv[1]);

	return 0;
}

////////////////////////////////////////////////////////////////
// pupose    : 옵션에 따라 수식을 처리한다
// parameter : 수식 문자열 포인터
////////////////////////////////////////////////////////////////
int expression_check(char* expression)
{
	//-name 옵션일 경우 패턴을 저장
	if(OPTION_NAME)
		strcpy(NAME_PATTERN,expression);

	//-perm 옵션일 경우 8진수 퍼미션 저장
	else if(OPTION_PERM)
		FIND_PERM = string_long(expression,8);
	
	//-user -grop 옵션일 경우 문자아이디 저장
	else if(OPTION_USER)
		strcpy(FIND_USER,expression);
	
	else if(OPTION_GROUP)
		strcpy(FIND_GROUP,expression);
	
	//-type 옵션일 경우 파일 타입 저장
	else if(OPTION_TYPE)
	{
		if( (*expression == 'f') || (*expression == 'F') )
			FIND_TYPE = S_IFREG;

		else if( (*expression == 'd') || (*expression == 'D') )
			FIND_TYPE = S_IFDIR;

		else if( (*expression == 'c') || (*expression == 'C') )
			FIND_TYPE = S_IFCHR;

		else if( (*expression == 'b') || (*expression == 'B') )
			FIND_TYPE = S_IFBLK;

		else if( (*expression == 'p') || (*expression == 'P') )
			FIND_TYPE = S_IFIFO;

		else if( (*expression == 'l') || (*expression == 'L') )
			FIND_TYPE = S_IFLNK;

		else if( (*expression == 's') || (*expression == 'S') )
			FIND_TYPE = S_IFSOCK;

		else
			return -1;
	}

	else
		return -1;

	return 0;
}

////////////////////////////////////////////////////////////////
// pupose    : 문자열을 정수형으로 변환
// parameter : 문자열 포인터, 진법
////////////////////////////////////////////////////////////////
int string_long(char* expression,int radix)
{
	char* token_p = expression;
	
	while(*token_p)
	{
		//숫자인지 체크
		if( !isdigit(*token_p) )
			return -1;

		*token_p++;
	}

	//변환한 정수형 리턴
	return strtol(expression,(char**)NULL,radix);
}

//도움말 콘솔 출력
int usage()
{
	fprintf(stderr,"사용법 : ./kwfind [패스] [-옵션] [수식]\n");
	fprintf(stderr," -name : 수식의 패턴에 맞는 이름으로 검색\n");
	fprintf(stderr," -perm : 수식의 퍼미션으로 검색\n");
	fprintf(stderr," -user : 수식의 소유자로 검색\n");
	fprintf(stderr,"-group : 수식의 그룹으로 검색\n");
	fprintf(stderr,"--help : 도움말 출력\n");
	fprintf(stderr,"사용예 : 모든 옵션은 하위디렉토리까지 수행\n");
	fprintf(stderr,"         패스는 반드시 입력\n");
	fprintf(stderr,"         패스만 입력시 모든 하위파일디렉토리 출력\n");
	fprintf(stderr,"         한번에 하나의 옵션만 가능\n");
	fprintf(stderr,"         패스 옵션 수식의 순서는 고정\n");
	fprintf(stderr,"         소유자 및 그룹은 문자아이디로 입력\n");
	fprintf(stderr,"         이진파일은 파일이름만 출력하고 건너뜀\n");
	fprintf(stderr,"         파일이름 패턴은 " "구분자로 입력\n");

	return 0;
}
