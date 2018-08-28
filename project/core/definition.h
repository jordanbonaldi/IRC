/*
** EPITECH PROJECT, 2018
** client
** File description:
** client
*/

# ifndef DEFINITION_HH
	# define DEFINITION_HH

# define OBJECT_CREATOR(x, spec, ...) typedef spec s_##x { \
				__VA_ARGS__; \
			} x;

# define STRUCT_DEFINE(x) typedef struct s_##x x;

/*
	Defining struct to allocating pre processing memory
*/

	STRUCT_DEFINE(SockFile);
	STRUCT_DEFINE(Server);
	STRUCT_DEFINE(Buffer);
	STRUCT_DEFINE(Socket);
	STRUCT_DEFINE(CallBack);
	STRUCT_DEFINE(Channel);
	STRUCT_DEFINE(Input);
	STRUCT_DEFINE(Command);
	STRUCT_DEFINE(Client);
	STRUCT_DEFINE(Chan);

/*
	End pre processing definition
*/

# define Status enum s_status

# define String char *

#endif
