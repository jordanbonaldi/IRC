/*
** EPITECH PROJECT, 2018
** lol
** File description:
** lol
*/

# ifndef STATICERR_HH
	# define STATICERR_HH

# include "project.h"

# define ERR_NOSUCHNICK "401 %s :No such nick/channel\r\n"

# define ERR_NOSUCHSERVER "402 %s :No such server\r\n"

# define ERR_NOSUCHCHANNEL "403 %s :No such channel\r\n"

# define ERR_CANNOTSENDTOCHAN "404 %s :Cannot send to channel\r\n"

# define ERR_TOOMANYCHANNELS "405 %s :You have joined too many channels\r\n"

# define ERR_WASNOSUCHNICK "406 %s :There was no such nickname\r\n"

# define ERR_TOOMANYTARGETS "407 %s :Duplicate recipients. No message \
delivered\r\n"

# define ERR_NOORIGIN "409 :No origin specified\r\n"

# define ERR_NORECIPIENT "411 :No recipient given\r\n"

# define ERR_NOTEXTTOSEND "412 :No text to send\r\n"

# define ERR_UNKNOWNCOMMAND "421 %s :Unknown command\r\n"

# define ERR_FILERROR "424 %s :File unknown\r\n"

# define ERR_NONICKNAMEGIVEN "431 :No nickname given\r\n"

# define ERR_ERRONEUSNICKNAME "432 %s :Erroneus nickname\r\n"

# define ERR_NICKNAMEINUSE "433 %s :Nickname is already in use\r\n"

# define ERR_USERNOTINCHANNEL "441 %s %s :They aren't on that channel\r\n"

# define ERR_NOTONCHANNEL "442 :You're not on a channel\r\n"

# define ERR_NEEDMOREPARAMS "461 %s :Not enough parameters\r\n"

# define ERR_USERSDONTMATCH "502 %s :No file\r\n"

# endif
