/*
** EPITECH PROJECT, 2018
** client
** File description:
** client
*/

# ifndef CLIENT_HH
	# define CLIENT_HH

# include "definition.h"

# define MAIN_PREFIX client

# define MAIN_STRUCT Client

# define NAME "root"

OBJECT_CREATOR
(
	Chan_,
	struct,

	String channel;
	int connected;
);

OBJECT_CREATOR
(
	Client,
	struct,

	Command *cmds;
	Input *input;
	Socket *socket;
	Buffer *buffer;
	Chan_ channel;
	int fd;

);

void __EXIT(MAIN_STRUCT *);

// LOADING HANDLERS

		# include "project.h"

// LOADING RESSOURCES (need to load them separately for conflicts)

	// IN COMMON RESSOURCES

		# include "buffer.h"

	// IN CLIENT

		# include "commands.h"
		# include "commands_manager.h"
		# include "commands_init.h"
		# include "messages_manager.h"
		# include "input.h"

CREATE_FUNCTION_NEUTRAL_LINKED(void, __EXIT)
{
	CALL_FUNCTION(destroyConnection);
	CALL_FUNCTION(destroyInput);
	CALL_FUNCTION(destroyCommands);
	CALL_FUNCTION_PARAMS(bufferMode, 1);
	if (this->channel.channel)
		free(this->channel.channel);
	exit(EXIT_SUCCESS);
}

CREATE_FUNCTION_NEUTRAL(int, main)
{
	MAIN_STRUCT this;
	this.cmds = NULL;
	this.fd = 1;
	this.channel.channel = NULL;
	this.channel.connected = false;

	signal(SIGINT, FUNC(void a(int sig) {
		__SETUNUSED__(sig);
		__SETUNUSED__(this);
		CALL_FUNCTION_LINKED_PASSED(__EXIT);
	}));
	CALL_FUNCTION_AS_PASS(initPreConnectionEvent);
	CALL_FUNCTION_AS_PASS(registerCommands);
	CALL_FUNCTION_AS_PASS(inputHandler);
	return 0;
}

#endif
