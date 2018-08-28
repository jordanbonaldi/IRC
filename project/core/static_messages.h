/*
** EPITECH PROJECT, 2018
** lol
** File description:
** lol
*/

# ifndef STATICMSG_HH
	# define STATICMSG_HH

# include "project.h"

# define RPL_LISTSTART "321 :Channel\r\n"

# define RPL_LIST "322 :%s\r\n"

# define RPL_LISTEND "323 :End of /LIST\r\n"

# define RPL_TOPIC "332 :You've joined %s\r\n"

# define RPL_NAMREPLY "353 %s :"

# define RPL_ENDOFNAMES "366 %s :End of /NAMES list\r\n"

# define RPL_USERSTART "392 :Pseudo - Channel\r\n"

# define RPL_USERS "393 :%s - %s\r\n"

# define RPL_ENDOFUSERS "394 :End of /USERS\r\n"

# endif
