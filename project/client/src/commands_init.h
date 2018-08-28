/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef COMMANDS_REGISTER_HH
	# define COMMANDS_REGISTER_HH

# include "client.h"

CREATE_FUNCTION(void, registerCommands)
{
	__add_cmd("/quit", GET_FUNCTION(quit), true);
	__add_cmd("/server", GET_FUNCTION(server), false);
	__add_cmd("/nick", GET_FUNCTION(nick), true);
	__add_cmd("/part", GET_FUNCTION(part), true);
	__add_cmd("/join", GET_FUNCTION(join), true);
	__add_cmd("/users", GET_FUNCTION(users), true);
	__add_cmd("/list", GET_FUNCTION(list), true);
	__add_cmd("/names", GET_FUNCTION(names), true);
	__add_cmd("/msg", GET_FUNCTION(msg), true);
	__add_cmd("/accept_file", GET_FUNCTION(accept_file), true);
	__add_cmd("default", GET_FUNCTION(default), true);
}

# endif
