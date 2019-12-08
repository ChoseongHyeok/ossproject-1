
#include "kwfind.h"

////////////////////////////////////////////////////////////////
// pupose    : 옵션에 따라서 출력을 결정한다
// parameter : 패스
////////////////////////////////////////////////////////////////
int kwfind(char* path)
{
	DIR* dir_p;

	struct dirent* dirent_p;

	struct stat stat_st;

	struct passwd* passwd_p;

	struct group* group_p;

	//access 가능한 디렉토리인지 체크
	if( access(path,R_OK) )
	{
		perror("access");
		return -1;
	}	

	//디렉토리 개방
	if( !(dir_p = opendir(path)) )
	{
		perror("opendir");
		return -1;
	}

	//작업디렉토리 변경
	chdir(path);

	//디렉토리 패스 버퍼 메모리 할당
	char* path_buf = (char*)malloc(PATH_SIZE);

	//디렉토리 끝까지 루프
	while( (dirent_p = readdir(dir_p)) != NULL )
	{
		//i노드 0인 삭제파일 건너뛰기
		if( !(dirent_p->d_ino) )
			continue;
		
		//상위디렉토리 건너뛰기
		if( !strcmp(dirent_p->d_name,".") || !strcmp(dirent_p->d_name,"..") )
			continue;
		
		//file stat 호출
		if( lstat(dirent_p->d_name,&stat_st) < 0 )
		{
			perror("lstat");
			return -1;
		}

		
		//파일이름 패턴이 불일치할 경우 건너뛰기
		if(OPTION_NAME)
		{
			if( fnmatch(NAME_PATTERN,dirent_p->d_name,0) )
				continue;
		}

		//퍼미션이 불일치할 경우 건너뛰기
		else if(OPTION_PERM)
		{
			if( FIND_PERM != (stat_st.st_mode & PERM_MASK) )
				continue;
		}

		//유저 아이디가 불일치할 경우 건너뛰기
		else if(OPTION_USER)
		{
			passwd_p = getpwuid(stat_st.st_uid);

			if( strcasecmp(FIND_USER,passwd_p->pw_name) )
				continue;
		}
	
		//그룹 아이디가 불일치할 경우 건너뛰기
		else if(OPTION_GROUP)
		{
			group_p = getgrgid(stat_st.st_gid);

			if( strcasecmp(FIND_GROUP,group_p->gr_name) )
				continue;
		}
		
		//파일 타입이 불일치할 경우 건너뛰기
		else if(OPTION_TYPE)
		{
			if( FIND_TYPE != (stat_st.st_mode & S_IFMT) )
				continue;
		}	
	
		//파일 출력
		printf("%s/%s\n",getcwd(path_buf,PATH_SIZE),dirent_p->d_name);
	}


	//엔트리포인터 되돌림
	rewinddir(dir_p);

	
	//디렉토리 끝까지 루프
	while( (dirent_p = readdir(dir_p)) != NULL )
	{
		//i노드 0인 삭제파일 건너뛰기
		if( !(dirent_p->d_ino) )
			continue;

		//상위디렉토리 건너뛰기
		if( !strcmp(dirent_p->d_name,".") || !strcmp(dirent_p->d_name,"..") )
			continue;
		
		//file stat 호출
		if( lstat(dirent_p->d_name,&stat_st) < 0 )
		{
			perror("lstat");
			return -1;
		}

		//디렉토리일 경우 재귀호출
		if( (stat_st.st_mode & S_IFMT) == S_IFDIR )
		{
			kwfind(dirent_p->d_name);
		}
	}
	

	//디렉토리 닫기
	closedir(dir_p);


	//재귀호출시 작업디렉토리 상위로 변경
	chdir("..");


	//패스 버퍼 메모리 해제
	free(path_buf);


	return 0;
}


