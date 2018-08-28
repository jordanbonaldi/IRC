/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef OUTPUT_HH
	# define OUTPUT_HH

# include "server.h"

CREATE_FUNCTION(void, createOutputAttributes)
{
	this->output = malloc(sizeof(Output));
	__(this->output, 1, CRITICAL);
	this->output->index = -1;
	this->output->last = -1;
	this->output->selected = NULL;
}

CREATE_FUNCTION_PARAMS(void, callOne, bool first)
{
	if (first)
		CALL_FUNCTION(loadUser);
	else
		CALL_FUNCTION(readUser);
}

CREATE_FUNCTION(void, launchAction)
{
	FOREACH_IT(this->output->last + 1, {
		if (FD_ISSET(index, &this->output->read_fd)) {
			this->output->index = index;
			CALL_FUNCTION_PARAMS(callOne,
				index == this->socket->id);
		}
	});
}

CREATE_FUNCTION(void, destroyOutput)
{
	if (this->output)
		free(this->output);
}

CREATE_FUNCTION(void, initFD)
{
	FD_ZERO(&this->output->set);
	FD_SET(this->socket->id, &this->output->set);
	FD_ZERO(&this->output->read_fd);
}

CREATE_FUNCTION(void, outputHandler)
{
	CALL_FUNCTION(createOutputAttributes);
	CALL_FUNCTION(initFD);
	this->output->last = this->socket->id;
	while (true) {
		this->output->read_fd = this->output->set;
		_N_(select(
			this->output->last + 1,
			&this->output->read_fd,
			NULL,
			NULL,
			NULL
		), 2, CRITICAL);
		CALL_FUNCTION(launchAction);
	}
}

# endif
