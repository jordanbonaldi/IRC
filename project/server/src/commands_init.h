/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef COMMANDS_REGISTER_HH
	# define COMMANDS_REGISTER_HH

# include "server.h"

CREATE_FUNCTION(void, registerCommands)
{
	__add_cmd("NICK", GET_FUNCTION(nick), false);
	__add_cmd("USERS", GET_FUNCTION(users), false);
	__add_cmd("USER", GET_FUNCTION(user), false);
	__add_cmd("JOIN", GET_FUNCTION(join), false);
	__add_cmd("PART", GET_FUNCTION(part), false);
	__add_cmd("LIST", GET_FUNCTION(list), false);
	__add_cmd("PRIVMSG", GET_FUNCTION(msg), false);
	__add_cmd("NAMES", GET_FUNCTION(names), false);
	__add_cmd("SEND", GET_FUNCTION(send), false);
	__add_cmd("ACCEPT", GET_FUNCTION(accept), false);
	__add_cmd("QUIT", GET_FUNCTION(quit), false);
}

# endif
