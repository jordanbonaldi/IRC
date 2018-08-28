/*
** EPITECH PROJECT, 2018
** connection
** File description:
** connection
*/

# ifndef USER_CHECKER_HH
	# define USER_CHECKER_HH

# include "server.h"

CREATE_FUNCTION_PARAMS(bool, isNickAlreadyExists, String nick)
{
	bool obj = false;

	FOREACH_LIST
	(
		User *,
		this->users,
		{
			if (
				IT->nick &&
				*IT->nick &&
				!strcmp(IT->nick, nick)
			)
				obj = true;
		}
	);
	return obj;
}

CREATE_FUNCTION_PARAMS(User *, getUserByIndex, int index)
{
	User *obj = NULL;

	FOREACH_LIST
	(
		User *,
		this->users,
		{
			if (IT->index == index)
				obj = IT;
		}
	);
	return obj;
}

CREATE_FUNCTION_PARAMS(User *, getUserByName, String args)
{
	User *obj = NULL;

	FOREACH_LIST
	(
		User *,
		this->users,
		{
			if (!strcmp(IT->nick, args))
				obj = IT;
		}
	);
	return obj;
}

CREATE_FUNCTION_PARAMS(void, unLinkIndex, int index)
{
	FD_CLR(index, &this->output->set);
	close(index);
}

CREATE_FUNCTION_PARAMS(void, removeUser, User *user)
{
	User *tmp = this->users;
	User *tmp2 = NULL;

	printf("Deleting user : [%d] : %s\n", user->index, user->nick);
	if (tmp->index == user->index) {
		this->users = tmp->next;
		CALL_FUNCTION_PARAMS(unLinkIndex, tmp->index);
		if (tmp->nick)
			free(tmp->nick);
		free(tmp);
		return;
	}
	while (tmp->next) {
		if (tmp->next->index == user->index)
			break;
		tmp = tmp->next;
	}
	tmp2 = tmp->next->next;
	CALL_FUNCTION_PARAMS(unLinkIndex, tmp->next->index);
	if (tmp->next->nick)
		free(tmp->next->nick);
	free(tmp->next);
	tmp->next = tmp2;
}

# endif
