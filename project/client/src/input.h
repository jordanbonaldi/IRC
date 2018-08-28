/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef INPUT_HH
	# define INPUT_HH

# include "client.h"

OBJECT_CREATOR
(
	Input,
	struct,

	fd_set *read_fd;
	int mode;
);

CREATE_FUNCTION(void, createInputAttributes)
{
	this->input = malloc(sizeof(Input));
	__(this->input, 1, CRITICAL);
	CALL_FUNCTION(buildBuffer);
}

CREATE_FUNCTION(char, readChar)
{
	__UNUSED__;
	char c;

	_N_(read(1, &c, 1), 4, CRITICAL);
	return c;
}

CREATE_FUNCTION_PARAMS(void, printChar, char c)
{
	__UNUSED__;

	_N_(write(1, &c, 1), 4, CRITICAL);
}

CREATE_FUNCTION_PARAMS(bool, removeLastChar, char c)
{
	if (c != 127)
		return false;
	write(1, "\b \b", 3);
	CALL_FUNCTION(removeWrite);
	return true;
}

CREATE_FUNCTION(void, handleInput)
{
	register char c;

	c = CALL_FUNCTION(readChar);
	if (CALL_FUNCTION_PARAMS(removeLastChar, c))
		return;
	CALL_FUNCTION_PARAMS(printChar, c);
	CALL_FUNCTION_PARAMS(addChar, c);
	if (CALL_FUNCTION(getSizeLeft) && c != '\n')
		return;
	CALL_FUNCTION_PARAMS(commandsHandler,
			CALL_FUNCTION(readDataBuffer));
}

CREATE_FUNCTION_PARAMS(void, callOne, bool first)
{
	if (first)
		CALL_FUNCTION(handleInput);
	else
		CALL_FUNCTION(messagesHandler);
}

CREATE_FUNCTION(void, launchAction)
{
	FOREACH_IT(this->fd + 1, {
		if (FD_ISSET(index, this->input->read_fd))
			CALL_FUNCTION_PARAMS(callOne, !index);
	});
}

CREATE_FUNCTION(fd_set, initFD)
{
	__UNUSED__;
	fd_set set;

	FD_ZERO(&set);
	FD_SET(0, &set);
	return set;
}

CREATE_FUNCTION(void, destroyInput)
{
	CALL_FUNCTION(deleteBuffer);
	if (this->input)
		free(this->input);
}

CREATE_FUNCTION(void, inputHandler)
{
	fd_set set = CALL_FUNCTION(initFD);
	CALL_FUNCTION_PARAMS(bufferMode, 0);
	CALL_FUNCTION(createInputAttributes);
	this->input->read_fd = &set;
	while (true) {
		FD_ZERO(this->input->read_fd);
		if (this->socket->id > 0)
			FD_SET(this->socket->id, this->input->read_fd);
		FD_SET(0, this->input->read_fd);
		_N_(select(
			this->fd,
			this->input->read_fd,
			NULL,
			NULL,
			NULL
		), 2, CRITICAL);
			CALL_FUNCTION(launchAction);
	}
	CALL_FUNCTION_PARAMS(bufferMode, 1);
}

# endif
