/*
** EPITECH PROJECT, 2018
** SERVER
** File description:
** SERVER
*/

# ifndef SERVER_HH
	# define SERVER_HH

# define SERVER

# include <sys/select.h>
# include <stdbool.h>

# include "definition.h"

# define MAIN_PREFIX server

# define MAIN_STRUCT Server

OBJECT_CREATOR
(
	User,
	struct,

	int index;
	String nick;
	bool connected;

	SockFile *file;

	Channel *channel;

	Buffer *buffer;

	void (*setBuffer)(MAIN_STRUCT *, struct s_User *);

	struct s_User *next;
);

OBJECT_CREATOR
(
	Output,
	struct,

	fd_set read_fd;
	fd_set set;

	int index;
	int last;

	User *selected;
);

OBJECT_CREATOR(Params, struct, int port);

OBJECT_CREATOR
(
	Server,
	struct,

	Command *cmds;
	Channel *channels;
	Output *output;
	Socket *socket;
	Buffer *buffer;
	User *users;
	Params params;

);

void __EXIT(MAIN_STRUCT *);

//

// LOADING HANDLERS

		# include "project.h"

// LOADING RESSOURCES (need to load them separately for conflicts)

	// IN COMMON RESSOURCES

		# include "buffer.h"

	// IN SERVER

		# include "channel.h"
		# include "user_manager.h"
		# include "commands.h"
		# include "commands_manager.h"
		# include "commands_init.h"
		# include "user.h"
		# include "user_message.h"
		# include "output.h"
		# include "connector.h"

CREATE_FUNCTION_NEUTRAL_LINKED(void, __EXIT)
{
	printf("\nClosing connection\n");
	CALL_FUNCTION(destroyConnection);
	CALL_FUNCTION(destroyOutput);
	CALL_FUNCTION(deleteBuffer);
	CALL_FUNCTION(destroyUsers);
	CALL_FUNCTION(destroyCommands);
	CALL_FUNCTION(destroyChannels);
	exit(EXIT_SUCCESS);
}

CREATE_MAIN(int, main)
{
	MAIN_STRUCT this;

	signal(SIGINT, FUNC(void a(int sig) {
		__SETUNUSED__(sig);
		printf("Stopping server\n");
		CALL_FUNCTION_LINKED_PASSED(__EXIT);
	}));

	if (argc == 1)
		return 1;
	this.params.port = argc != 2 ? 6667 : atoi(argv[1]);
	CALL_FUNCTION_AS_PASS(launchConnector);
	CALL_FUNCTION_AS_PASS(registerCommands);
	CALL_FUNCTION_AS_PASS(outputHandler);
	return 0;
}

#endif
