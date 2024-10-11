# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 15:32:25 by dbonilla          #+#    #+#              #
#    Updated: 2023/10/16 16:58:48 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME		=	libft.a
INCLUDES	=	inc/
SRC_DIR		=	src/
CC			=	gcc
CCFLAGS		=	-Wall -Wextra -Werror
AR			=	ar rc
RM			=	rm -f



SRC_FILES	=	ft_is/ft_isalnum.c ft_is/ft_isalpha.c ft_is/ft_isascii.c \
				ft_is/ft_isdigit.c ft_is/ft_isprint.c ft_is/ft_isspace.c \
				ft_is/ft_ischarset.c ft_is/ft_isline.c ft_is/ft_isint.c \
				ft_is/ft_is_samesign.c \
				ft_lst/ft_lstnew.c ft_lst/ft_lstadd_front.c \
				ft_lst/ft_lstsize.c ft_lst/ft_lstlast.c \
				ft_lst/ft_lstadd_back.c ft_lst/ft_lstdelone.c \
				ft_lst/ft_lstclear.c ft_lst/ft_lstiter.c \
				ft_lst/ft_lstmap.c \
				ft_mem/ft_bzero.c ft_mem/ft_calloc.c ft_mem/ft_memccpy.c \
				ft_mem/ft_memchr.c ft_mem/ft_memcmp.c ft_mem/ft_memcpy.c \
				ft_mem/ft_memmove.c ft_mem/ft_memset.c \
				ft_put/ft_putchar_fd.c ft_put/ft_putnbr_unsigned_fd.c \
				ft_put/ft_putnbr_fd.c ft_put/ft_putstr_fd.c \
				ft_put/ft_puthex_fd.c \
				ft_str/ft_split.c ft_str/ft_strchr.c ft_str/ft_strdup.c \
				ft_str/ft_striteri.c ft_str/ft_strjoin.c ft_str/ft_strlcat.c \
				ft_str/ft_strlcpy.c ft_str/ft_strlen.c ft_str/ft_strmapi.c \
				ft_str/ft_strncmp.c ft_str/ft_strnstr.c ft_str/ft_strrchr.c \
				ft_str/ft_strtrim.c ft_str/ft_substr.c ft_str/ft_strcat.c \
				ft_str/ft_strcmp.c \
				ft_to/ft_abs.c ft_to/ft_atoi.c ft_to/ft_itoa.c ft_to/ft_max.c \
				ft_to/ft_toupper.c ft_to/ft_tolower.c ft_to/ft_digitcount.c\
				ft_printf/ft_printf.c \
				ft_gnl/ft_get_next_line.c \
				ft_intlst/ft_args_to_intlst.c ft_intlst/ft_intlst_addback.c \
				ft_intlst/ft_intlst_free.c ft_intlst/ft_intlst_last.c \
				ft_intlst/ft_intlst_new.c ft_intlst/ft_intlst_print.c \
				ft_intlst/ft_intlst_before_last.c \
				ft_intlst/ft_intlst_issorted.c ft_intlst/ft_intlst_minval.c\
				ft_intlst/ft_intlst_maxval.c ft_intlst/ft_intlst_size.c \
				ft_intlst/ft_intlst_isrevsorted.c

SRC	=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ	=	$(SRC:.c=.o)
# **************************************************************************************** #
all:			$(NAME)

$(NAME):		$(OBJ)
					@$(AR) $(NAME) $(OBJ)
					@echo "libft compiled!"

.c.o:			
				@echo "Compiling"
				@$(CC) $(CCFLAGS) -I$(INCLUDES) -c $< -o $(<:.c=.o)
clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re bonus