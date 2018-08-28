/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef COMMANDS_HH
	# define COMMANDS_HH

# include "client.h"

OBJECT_CREATOR
(
	Generic,
	struct,

	String data;
	String name;
);

# define setGeneric(a, b) (Generic) { \
				.data = b,\
				.name = a\
			}\

# define _sendToConnected(s) dprintf(this->socket->id, s)

# define __sendToConnected(s, ...) dprintf(this->socket->id, \
							s, __VA_ARGS__)

CREATE_FUNCTION_PARAMS(void, genericCall, Generic args)
{
	if (strchr(args.data, ' ')) {
		strtok(args.data, " ");
		__sendToConnected("%s %s\r\n", args.name,
							strtok(NULL, ""));
	} else
		__sendToConnected("%s\r\n", args.name);
}

CREATE_FUNCTION_PARAMS(void, quit, String args)
{
	CALL_FUNCTION_PARAMS(genericCall, setGeneric("QUIT", args));
	free(args);
	CALL_FUNCTION_LINKED(__EXIT);
}

CREATE_FUNCTION_PARAMS(void, nick, String args)
{
	bool space = false;

	if ((space = strchr(args, ' ')))
		strtok(args, " ");
	__sendToConnected("NICK %s\r\n", space ? strtok(NULL, "") : "");
}

CREATE_FUNCTION_PARAMS(void, server, String args)
{
	String ip;
	String tmp;
	int port;

	if (!strchr(args, ' ')) {
		printf("Bad usage /server ip[:port]\n");
		return;
	}
	tmp = strdup(args);
	strtok(args, " ");
	ip = strchr(tmp, ':') ? strtok(NULL, ":") : strtok(NULL, "");
	port = strchr(tmp, ':') ? atoi(strtok(NULL, "")) : 6667;
	if (ip[strlen(ip) - 1] == '\n')
		ip[strlen(ip) - 1] = 0;
	free(tmp);
	{
		CALL_FUNCTION_PARAMS(setIp, ip);
		CALL_FUNCTION_PARAMS(setPort, port);
		CALL_FUNCTION_PARAMS(setAddr, inet_addr(this->socket->ip));
		CALL_FUNCTION(preConnectionEvent);
		CALL_FUNCTION(connectionEvent);
		this->fd = this->socket->id + 1;
	}
	__sendToConnected("USER %s %s %s :%s\r\n",
		NAME, NAME, "127.0.0.1", NAME);
}

CREATE_FUNCTION_PARAMS(void, part, String args)
{
	CALL_FUNCTION_PARAMS(genericCall, setGeneric("PART", args));
	if (this->channel.channel)
		free(this->channel.channel);
	this->channel.channel = NULL;
}

CREATE_FUNCTION_PARAMS(void, join, String args)
{
	String tmp = strdup(args);
	CALL_FUNCTION_PARAMS(genericCall, setGeneric("JOIN", args));
	strtok(tmp, " ");
	if (this->channel.channel)
		free(this->channel.channel);
	this->channel.channel = strdup(strtok(NULL, ""));
	free(tmp);
}

CREATE_FUNCTION_PARAMS(void, users, String args)
{
	CALL_FUNCTION_PARAMS(genericCall, setGeneric("USERS", args));
}

CREATE_FUNCTION_PARAMS(void, names, String args)
{
	CALL_FUNCTION_PARAMS(genericCall, setGeneric("NAMES", args));
}

CREATE_FUNCTION_PARAMS(void, list, String args)
{
	CALL_FUNCTION_PARAMS(genericCall, setGeneric("LIST", args));
}

CREATE_FUNCTION_PARAMS(int, counter, String args)
{
	__UNUSED__;
	int count = 0;

	FOREACH_LENGTH(char, args, strlen(args),
	{
		__SETUNUSED__(index);
		if (IT == ' ')
			count++;
	}
	);
	return count;
}

CREATE_FUNCTION_PARAMS(void, msg, String args)
{
	int count = CALL_FUNCTION_PARAMS(counter, args);

	if (count == 3) {
		args += 5;
		String chan = strtok(args, " ");
		String name = strtok(NULL, " ");
		String file = strtok(NULL, " ");
		__sendToConnected("SENDFILE %s %s %s\r\n",
			chan,
			name,
			file
		);
	}
	else if (count >= 2) {
		args += 5;
		String name = strtok(args, " ");
		String msg = strtok(NULL, "");
		__sendToConnected("PRIVMSG %s :%s\r\n",
			name,
			msg
		);
	}

}

CREATE_FUNCTION_PARAMS(void, accept_file, String args)
{
	CALL_FUNCTION_PARAMS(genericCall, setGeneric("ACCEPTFILE", args));
}

CREATE_FUNCTION_PARAMS(void, default, String args)
{
	if (!this->channel.channel)
		return;
	__sendToConnected("PRIVMSG %s :%s\r\n",
		this->channel.channel, args);
}

# endif
