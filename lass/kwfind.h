
#ifndef __KWFIND_H__
#define __KWFIND_H__

#include "header.h"

#define FALSE	0
#define	TRUE	1

#define PATH_SIZE	1024	//패스사이즈,퍼미션 마스크
#define BUF_SIZE	256
#define PERM_MASK	0777

int	OPTION_NAME;	//옵션 플래그
int	OPTION_PERM;
int	OPTION_USER;
int	OPTION_GROUP;
int	OPTION_TYPE;
int	OPTION;

char	NAME_PATTERN[BUF_SIZE];	//옵션 사용자 입력 정보
int	FIND_PERM;
char	FIND_USER[20];
char	FIND_GROUP[20];
int	FIND_TYPE;

#endif
