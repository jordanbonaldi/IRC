/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef FILES_HH
	# define FILES_HH

# include "project.h"

OBJECT_CREATOR
(
	SockFile,
	struct,

	String name;
	char content[2048];
)

CREATE_FUNCTION(SockFile *, initFile)
{
	SockFile *file;
	__
	(
		(file = malloc(sizeof(SockFile))),
		6,
		CRITICAL
	);
	return file;
}

CREATE_FUNCTION_PARAMS(bool, fileExists, String file)
{
	__UNUSED__;
	int a = open(file, O_RDONLY);
	close(a);
	return a != -1;
}

CREATE_FUNCTION_PARAMS(void, createFile, SockFile file)
{
	__UNUSED__;
	int fd = 0;
	_N_
	(
		(fd = open(file.name, O_CREAT | O_RDWR)),
		CRITICAL,
		11
	);
	//dprintf(fd, file.content);
	close(fd);
}

CREATE_FUNCTION_PARAMS(SockFile, readFile, String name)
{
	__UNUSED__;
	int fd = 0;
	SockFile file = (SockFile)
	{
		.name = name
	};

	RESET(file.content, 2048);
	_N_
	(
		(fd = open(file.name, O_CREAT | O_RDWR)),
		CRITICAL,
		11
	);
	read(fd, file.content, 2048);
	close(fd);
	return file;
}

# endif
