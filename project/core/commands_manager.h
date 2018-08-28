/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef COMMANDS_HANDLER_HH
	# define COMMANDS_HANDLER_HH

# include "project.h"

OBJECT_CREATOR
(
	Command,
	struct,

	String name;
	String line;

	void (*run)(CREATE_ARGS, String);

	bool need_connected;

	struct s_Command *next;
);

# define __create_cmd(cmdname, func, conn) ((Command) { \
					.name = cmdname, \
					.run = func, \
					.need_connected = conn, \
					.next = NULL\
				})

# define __add_cmd(cmdname, func, con) CALL_FUNCTION_PARAMS(addcmd, \
					__create_cmd(cmdname, func, con))

CREATE_FUNCTION_PARAMS(Command *, getNode, String name)
{
	Command *obj = NULL;

	FOREACH_LIST
	(
		Command *,
		this->cmds,
		{
			if (!strcmp(IT->name, name))
				obj = IT;
		}
	);
	return obj;
}

CREATE_FUNCTION(void, destroyCommands)
{
	Command *tmp = this->cmds;
	Command *tmp2;

	while (tmp) {
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

CREATE_FUNCTION_PARAMS(void, addcmd, Command cmd)
{
	Command *__cmd;
	Command *tmp;

	__cmd = malloc(sizeof(Command));
	__cmd->name = cmd.name;
	__cmd->run = cmd.run;
	__cmd->need_connected = cmd.need_connected;
	__cmd->next = NULL;
	if (!this->cmds)
		this->cmds = __cmd;
	else {
		tmp = this->cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __cmd;
	}
}

CREATE_FUNCTION_PARAMS(void, commandExecutor, Command *cmd)
{
	if (cmd->need_connected && !this->socket->connection) {
		printf("You need to be connected to a server\n");
		return;
	}
	if (cmd->line[strlen(cmd->line) - 1] == '\n')
		cmd->line[strlen(cmd->line) - 1] = 0;
	CALL_ANY(cmd->run, cmd->line);
}

CREATE_FUNCTION_PARAMS(void, getCommand, String cmd)
{
	__UNUSED__;
	bool called = false;
	Command *cmds = NULL;

	FOREACH_LIST
	(
		Command *,
		this->cmds,
		{
			if (!called &&
				!strncmp(IT->name, cmd, strlen(IT->name))) {

				IT->line = cmd;
				CALL_FUNCTION_PARAMS(commandExecutor, IT);
				called = true;
				return;

			}
		}
	);
	if (!called && *cmd != '/') {
		cmds = CALL_FUNCTION_PARAMS(getNode, "default");
		if (cmds) {
			cmds->line = cmd;
			CALL_FUNCTION_PARAMS(commandExecutor, cmds);
		}
	} else if (!called)
		printf("Unknown command\n");
}

CREATE_FUNCTION_PARAMS(void, commandsHandler, String cmd)
{
	__UNUSED__;
	CALL_FUNCTION_PARAMS(getCommand, cmd);
	free(cmd);
}

# endif
