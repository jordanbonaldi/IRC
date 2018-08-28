/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef USERMESSAGING_HH
	# define USERMESSAGING_HH

# include "server.h"

CREATE_FUNCTION_PARAMS(void, handleMessage, String response)
{
	__UNUSED__;
	String cut;

	printf("%s\n", response);
	while ((cut = strtok_r(response, "\n", &response))) {
		printf("Launching action for : %s\n", cut);
		CALL_FUNCTION_PARAMS(commandsHandler, strdup(cut));
	}
}

CREATE_FUNCTION(void, errOnReceive)
{
	printf("User [%d] disconnected\n", this->output->index);
	CALL_FUNCTION_PARAMS(removeUser, this->output->selected);
}

CREATE_FUNCTION(void, messagesHandler)
{
	char tmp[MAX_SIZE];
	String response;

	RESET(tmp, MAX_SIZE);

	if (recv(
		this->output->selected->index,
		tmp,
		CALL_FUNCTION(getSizeLeft),
		0
	) > 0)
	{
		CALL_FUNCTION_PARAMS(writeDataBuffer, tmp);

		if (
			CALL_FUNCTION_PARAMS(getData, -1) == '\n'
			&&
			CALL_FUNCTION_PARAMS(getData, -2) == '\r'
		)
		{
			response = CALL_FUNCTION(readDataBuffer);
			CALL_FUNCTION_PARAMS(
				handleMessage,
				response
			);
			free(response);
		}
	} else
		CALL_FUNCTION(errOnReceive);
}

CREATE_FUNCTION(void, readUser)
{
	this->output->selected = CALL_FUNCTION_PARAMS(
					getUserByIndex,
					this->output->index
				);
	if (this->output->selected && this->output->selected->connected)
		CALL_FUNCTION(messagesHandler);
}

# endif
