/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef USER_HH
	# define USER_HH

# include "server.h"

# define setUser(a) (User) {\
				.index = a\
			}

CREATE_FUNCTION_PARAMS(void, setBuffer, User *user)
{
	this->buffer = user->buffer;
}

CREATE_FUNCTION(void, destroyUsers)
{
	User *tmp = this->users;
	User *tmp2;

	while (tmp) {
		tmp2 = tmp->next;
		if (tmp->nick)
			free(tmp->nick);
		free(tmp);
		tmp = tmp2;
	}
}

CREATE_FUNCTION_PARAMS(void, newUser, User userinit)
{
	User *__user;
	User *tmp;

	__SETUNUSED__(tmp);
	__user = malloc(sizeof(User));
	__user->index = userinit.index;
	__user->nick = NULL;
	__user->channel = NULL;
	__user->next = NULL;
	__user->connected = true;
	__user->setBuffer = GET_FUNCTION(setBuffer);
	if (this->users == NULL)
		this->users = __user;
	else {
		tmp = this->users;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = __user;
	}
}

CREATE_FUNCTION(void, loadUser)
{
	printf("New user try to connect\n");
	CALL_FUNCTION(acceptEvent);
	printf("User connected succesfully\n");
	CALL_FUNCTION_PARAMS(
		newUser,
		setUser
		(
			this->socket->connected_fd
		)
	);
	FD_SET
	(
		this->socket->connected_fd,
		&this->output->set
	);
	if (this->socket->connected_fd > this->output->last)
		this->output->last = this->socket->connected_fd;
}

# endif
