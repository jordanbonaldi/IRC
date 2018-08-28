/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef CONNECTOR_HH
	# define CONNECTOR_HH

# include "server.h"

# define setNULL(setter) this->setter = NULL

CREATE_FUNCTION(void, bindListen)
{
	printf("Binding port\n");
	CALL_FUNCTION(bindEvent);

	printf("Listening port\n");
	CALL_FUNCTION(listenEvent);
}

CREATE_FUNCTION(void, connAddr)
{
	CALL_FUNCTION_PARAMS(setAddr, INADDR_ANY);

	printf("Setting addr to localhost\n");

	CALL_FUNCTION(setSocketOption);
}

CREATE_FUNCTION(void, launchConnector)
{
	printf("Initialize connection\n");

	CALL_FUNCTION(initPreConnectionEvent);

	printf("Setting port on : %d\n", this->params.port);

	CALL_FUNCTION_PARAMS(setPort, this->params.port);
	CALL_FUNCTION(preConnectionEvent);

	printf("Creating socket\n");

	CALL_FUNCTION(connAddr);

	CALL_FUNCTION(bindListen);

	CALL_FUNCTION(buildBuffer);

	setNULL(users);
	setNULL(cmds);
	setNULL(channels);
}

# endif
