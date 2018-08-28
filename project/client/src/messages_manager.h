/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef MESSAGE_HANDLER_HH
	# define MESSAGE_HANDLER_HH

# include "project.h"

CREATE_FUNCTION(void, messagesHandler)
{
	char tmp[MAX_SIZE];
	String response;

	RESET(tmp, MAX_SIZE);

	_NQ_(recv(
		this->socket->id,
		tmp,
		CALL_FUNCTION(getSizeLeft),
		0
	), 9, HIGH);

	CALL_FUNCTION_PARAMS(writeDataBuffer, tmp);
	if (
		CALL_FUNCTION_PARAMS(getData, -1) == '\n'
		&&
		CALL_FUNCTION_PARAMS(getData, -2) == '\r'
	)
	{
		response = CALL_FUNCTION(readDataBuffer);
		printf("%s", response);
		if (strncmp(response, "353", 3))
			this->channel.connected = true;
		free(response);
	}
}

# endif
