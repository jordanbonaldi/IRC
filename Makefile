##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

PROJECT = project/

CLIENT = $(PROJECT)client/

SERVER = $(PROJECT)server/

all:
	make re -C $(CLIENT)
	make re -C $(SERVER)

client:
	make re -C $(CLIENT)

server:
	make re -C $(SERVER)

clean:
	make clean -C $(CLIENT)
	make clean -C $(SERVER)

fclean:
	make fclean -C $(CLIENT)
	make fclean -C $(SERVER)

re: all

.PHONY: all clean fclean re
