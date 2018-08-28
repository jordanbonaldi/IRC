/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef CHANNEL_HH
	# define CHANNEL_HH

# include "server.h"

OBJECT_CREATOR
(
	CallBack,
	struct,

	String str;
	void (*action)(void *);
);

OBJECT_CREATOR
(
	Channel,
	struct,

	String name;

	struct s_Channel *next;
);

# define setChannel(str) (Channel) {\
				.name = str\
			}

# define setCallBack(s, func) (CallBack) { \
			.str = s,\
			.action = func \
		}

# define __newChannel(str) CALL_FUNCTION_PARAMS(addChannel, setChannel(str))

# define sendMessageToChannel(chann, str, ...) \
	{\
		CALL_FUNCTION_PARAMS \
		(\
			onChannelAction,\
			setCallBack\
			(\
				chann,\
				FUNC\
				(\
					void a(void *user)\
					{\
						User *tmp = (User *)user;\
						dprintf(\
							tmp->index, \
							str, \
							__VA_ARGS__\
						);\
					}\
				)\
			)\
		);\
	}

# define sendMessageToChannelWithException(chann, exception, str, ...) \
	{\
		CALL_FUNCTION_PARAMS \
		(\
			onChannelAction,\
			setCallBack\
			(\
				chann,\
				FUNC\
				(\
					void a(void *user)\
					{\
						User *tmp = (User *)user;\
						if (tmp->index == exception)\
							return;\
						dprintf(\
							tmp->index, \
							str, \
							__VA_ARGS__\
						);\
					}\
				)\
			)\
		);\
	}

CREATE_FUNCTION_PARAMS(Channel *, addChannel, Channel channel)
{
	Channel *__chan;
	Channel *tmp;

	printf("Creating channel : %s\n", channel.name);
	__chan = malloc(sizeof(Channel));
	__chan->name = channel.name;
	__chan->next = NULL;
	if (this->channels) {
		tmp = this->channels;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __chan;
	} else {
		this->channels = __chan;
	}
	return __chan;
}

CREATE_FUNCTION_PARAMS(void, removeChannel, String args)
{
	Channel *tmp = this->channels;
	Channel *tmp2 = NULL;

	printf("Deleting channel : %s\n", args);
	if (!strcmp(tmp->name, args)) {
		this->channels = tmp->next;
		if (tmp->name)
			free(tmp->name);
		free(tmp);
		return;
	}
	while (tmp->next) {
		if (!strcmp(tmp->next->name, args))
			break;
		tmp = tmp->next;
	}
	tmp2 = tmp->next->next;
	if (tmp->next->name)
		free(tmp->next->name);
	free(tmp->next);
	tmp->next = tmp2;
}

CREATE_FUNCTION(void, destroyChannels)
{
	Channel *tmp = this->channels;
	Channel *tmp2;

	while (tmp) {
		tmp2 = tmp->next;
		if (tmp->name)
			free(tmp->name);
		free(tmp);
		tmp = tmp2;
	}
}

CREATE_FUNCTION_PARAMS(void, ActionOnChannels, CallBack callback)
{
	FOREACH_LIST
	(
		Channel *,
		this->channels,
		{
			if (!
				strncmp
				(
					IT->name,
					callback.str,
					strlen(callback.str)
				)
			)
				callback.action(IT);
		}
	);
}

CREATE_FUNCTION_PARAMS(Channel *, getChannel, String args)
{
	Channel *channel = NULL;

	FOREACH_LIST
	(
		Channel *,
		this->channels,
		{
			if (!strcmp(IT->name, args))
				channel = IT;
		}
	);
	return channel;
}

CREATE_FUNCTION_PARAMS(void, onChannelAction, CallBack callback)
{
	FOREACH_LIST
	(
		User *,
		this->users,
		{
			if (
				IT->channel &&
				!strcmp(IT->channel->name, callback.str)
			)
				callback.action(IT);
		}
	)
}

CREATE_FUNCTION_PARAMS(int, UserInChannel, String args)
{
	int $tmp = 0;

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
					__SETUNUSED__(user);
					++$tmp;
				}
			)
		)
	);
	return $tmp;
}

CREATE_FUNCTION_PARAMS(void, checkChannel, String args)
{
	if (!CALL_FUNCTION_PARAMS(UserInChannel, args))
		CALL_FUNCTION_PARAMS(removeChannel, args);
}

# endif
