/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef COMMANDS_HH
	# define COMMANDS_HH

# include "server.h"

# define _sendToConnected(s) dprintf(this->output->selected->index, s)

# define __sendToUser(user, s, ...) dprintf(user->index, s, __VA_ARGS__)

# define __sendToConnected(s, ...) dprintf(this->output->selected->index, \
							s, __VA_ARGS__)

# define __CUT__ { \
			if (strchr(args, ' ')) {\
				strtok(args, " ");\
				args = strtok(NULL, "");\
				args[strlen(args) - 1] = 0;\
			}\
		}

# define __checkChannel__(chann) \
			Channel *channel = \
				CALL_FUNCTION_PARAMS(getChannel, args);\
			if (!channel) {\
				__sendToConnected(\
					ERR_NOSUCHCHANNEL,\
					chann\
				);\
				return;\
			}\

CREATE_FUNCTION_PARAMS(void, nick, String args)
{
	__CUT__;
	String old = NULL;

	if (!*args) {
		_sendToConnected(ERR_NONICKNAMEGIVEN);
		return;
	} else if (strlen(args) > 9) {
		__sendToConnected(ERR_ERRONEUSNICKNAME, args);
		return;
	} else if (CALL_FUNCTION_PARAMS(isNickAlreadyExists, args)) {
		__sendToConnected(ERR_NICKNAMEINUSE, args);
		return;
	}
	if (this->output->selected->nick) {
		old = strdup(this->output->selected->nick);
		free(this->output->selected->nick);
	}
	this->output->selected->nick = strdup(args);
	if (old)
		__sendToConnected
		(
			":%s NICK %s\r\n",
			this->output->selected->nick,
			old
		);
	else
		__sendToConnected
		(
			":%s NICK (null)\r\n",
			this->output->selected->nick
		);
	free(old);
	printf("Nickname changed for %d, now : [%s]\n",
		this->output->selected->index,
		this->output->selected->nick
	);
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

CREATE_FUNCTION_PARAMS(void, user, String args)
{
	__CUT__;

	if (CALL_FUNCTION_PARAMS(counter, args) != 3) {
		__sendToConnected(ERR_NEEDMOREPARAMS, "USER");
		return;
	}

	{
		/*
			calling new brackets for reseting pointer of strtok
		*/

		CALL_FUNCTION_PARAMS(nick, strtok(args, " "));

		/*
			pointer of strtok destruct here
		*/
	}
	__sendToConnected(
		"001 %s :Connected\r\n",
		this->output->selected->nick
	);
}

CREATE_FUNCTION_PARAMS(void, names, String args)
{
	__CUT__;

	__checkChannel__(args);
	__sendToConnected(RPL_NAMREPLY, args);
	CALL_FUNCTION_PARAMS
	(
		onChannelAction,
		setCallBack
		(
			args,
			FUNC
			(
				void a(void *user)
				{
					User *us = (User *)user;
					__sendToConnected("%s ", us->nick);
				}
			)
		)
	);
	_sendToConnected("\r\n");
	__sendToConnected(RPL_ENDOFNAMES, args);
}

CREATE_FUNCTION_PARAMS(void, part, String args)
{
	__SETUNUSED__(args);
	String name = NULL;

	if (!this->output->selected->channel) {
		_sendToConnected(ERR_NOTONCHANNEL);
		return;
	}
	name = strdup(this->output->selected->channel->name);
	__sendToConnected
	(
		":%s PART :%s\r\n",
		this->output->selected->nick,
		name
	);
	this->output->selected->channel = NULL;
	sendMessageToChannel
	(
		name,
		":%s PART %s\r\n",
		this->output->selected->nick,
		name
	);
	CALL_FUNCTION_PARAMS(checkChannel, name);
	free(name);
}

CREATE_FUNCTION_PARAMS(void, join, String args)
{
	__CUT__;
	Channel *channel = CALL_FUNCTION_PARAMS(getChannel, args);

	if (!channel)
		channel = __newChannel(strdup(args));
	if (this->output->selected->channel)
		CALL_FUNCTION_PARAMS(part, NULL);
	__sendToConnected
	(
		":%s JOIN :%s\r\n",
		this->output->selected->nick,
		args
	);
	sendMessageToChannel
	(
		channel->name,
		":%s JOIN %s\r\n",
		this->output->selected->nick,
		channel->name
	);
	printf("%s joined %s\n", this->output->selected->nick, channel->name);
	this->output->selected->channel = channel;
	__sendToConnected(RPL_TOPIC, channel->name);
	CALL_FUNCTION_PARAMS(names, channel->name);
}

CREATE_FUNCTION_PARAMS(void, users, String args)
{
	__CUT__;

	_sendToConnected(RPL_USERSTART);

	{

		FOREACH_LIST
		(
			User *,
			this->users,
			{
				__sendToConnected
				(
					RPL_USERS,
					IT->nick,
					IT->channel ?
					IT->channel->name :
					"None"
				);
			}
		)

	}

	_sendToConnected(RPL_ENDOFUSERS);
}

CREATE_FUNCTION(void, listAll)
{
	{

		FOREACH_LIST
		(
			Channel *,
			this->channels,
			{
				__sendToConnected(RPL_LIST, IT->name);
			}
		)

	}
}

CREATE_FUNCTION_PARAMS(void, list, String args)
{
	_sendToConnected(RPL_LISTSTART);

	if (strchr(args, ' ')) {
		__CUT__;
		CALL_FUNCTION_PARAMS
		(
			ActionOnChannels,
			setCallBack
			(
				args,
				FUNC
				(
					void a(void *channel)
					{
						Channel *chan =
							(Channel *)channel;
						__sendToConnected
						(
							RPL_LIST,
							chan->name
						);
					}
				)
			)
		);
	} else
		CALL_FUNCTION(listAll);

	_sendToConnected(RPL_LISTEND);
}

CREATE_FUNCTION_PARAMS(void, msg, String args)
{
	__CUT__;
	String user_or_channel  = strtok(args, " ");
	String _message_ = strtok(NULL, "") + 1;
	User *user = CALL_FUNCTION_PARAMS(getUserByName, user_or_channel);
	Channel *channel = CALL_FUNCTION_PARAMS(getChannel, user_or_channel);

	__SETUNUSED__(channel);
	if (user) {
		__sendToUser(
			user,
			":%s PRIVMSG %s :%s\r\n",
			user->nick,
			this->output->selected->nick,
			_message_
		);
		__sendToConnected
		(
			":%s PRIVMSG %s :%s\r\n",
			user->nick,
			this->output->selected->nick,
			_message_
		);
	} else
		sendMessageToChannel
		(
			channel->name,
			":%s PRIVMSG %s :%s\r\n",
			this->output->selected->nick,
			channel->name,
			_message_
		);
}

CREATE_FUNCTION_PARAMS(void, quit, String args)
{
	__SETUNUSED__(args);
	CALL_FUNCTION_PARAMS(removeUser, this->output->selected);
}

CREATE_FUNCTION_PARAMS(void, send, String args)
{
	__CUT__;

	String name = strtok(args, " ");
	String file = strtok(args, "");
	User *user = CALL_FUNCTION_PARAMS(getUserByName, name);
	int port = 0;

	if (!user) {
		__sendToConnected(ERR_NOSUCHNICK, name);
		return;
	}
	if (!CALL_FUNCTION_PARAMS(fileExists, file))
		port = CALL_FUNCTION(passiveMode);
	else {
		__sendToConnected(ERR_FILERROR, file);
		return;
	}

	this->output->selected->file = CALL_FUNCTION(initFile);

	// READ AND STOCK;

	__sendToConnected
	(
		"SENDFILE :%s :Command (127,0,0,1,%d,%d)\r\n",
		file,
		port / 256,
		port % 256
	);
	__sendToUser(user, ":%s SENDING :%s\r\n",
		this->output->selected->nick, file);
}

CREATE_FUNCTION_PARAMS(void, accept, String args)
{
	__CUT__;
	User *user = CALL_FUNCTION_PARAMS(getUserByName, strtok(args, " "));
	int port = 0;

	if (!user) {
		__sendToConnected(ERR_NEEDMOREPARAMS, args);
		return;
	} else if (!user->file) {
		__sendToConnected(ERR_USERSDONTMATCH, user->nick);
		return;
	}
	port = CALL_FUNCTION(passiveMode);

	// WRITING FILE AND STOCK;

	__sendToConnected
	(
		"ACCEPT :%s :Rcv (127,0,0,1%d,%d)\r\n",
		user->file->name,
		port / 256,
		port % 256
	);
}

# endif
