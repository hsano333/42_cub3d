NAME 	:= cub3D
LIB	:= ./lib/
OBJDIR	:= ./obj

LIBMLXDIR	:= $(LIB)/minilibx-linux
LIBMLXTAR	:= $(LIB)/minilibx-linux.tgz
LIBMLX		:= $(LIBMLXDIR)/libmlx.a

LIBFTDIR	:= $(LIB)/libft
LIBFTNAME	:= libft.a
LIBFT		:= $(LIBFTDIR)/$(LIBFTNAME)

SRCDIR	:= ./srcs/
SRC	:= main.c init.c arg.c hook.c mouse.c key.c close.c wall.c ray.c angle_utils.c map_utils.c calc_texture_mapping.c ray_utils.c door.c parser_add_color.c parser_add_map.c parser_add_map_helper.c parser_add_to_env.c parser_check_file.c  parser_exit.c parser_fill_check_buf.c parser_free.c parser_line.c parser_main.c parser_print_err.c parser_util.c parser_add_player.c parser_add_info.c player.c slot.c slot_utils.c draw_map.c
ENTRY	:= window.c parser_check_type.c parser_copy_map.c
ENTRYBONUS	:= window_bonus.c parser_check_type_bonus.c parser_copy_map_bonus.c

ifdef WITH_BONUS
SRC	+= $(ENTRYBONUS)
DELENTRY	:= $(addprefix $(OBJDIR)/, $(ENTRY))
else
DELENTRY	:= $(addprefix $(OBJDIR)/, $(ENTRYBONUS))
SRC	+= $(ENTRY)
endif

SRCS	:= $(addprefix $(SRCDIR), $(SRC))
OBJS	:= $(SRCS:.c=.o)
OBJECTS	:= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEPS	:= $(OBJECTS:.o=.d)
ifeq ($(shell uname),Darwin)
INCS	:= ./include $(LIBFTDIR)/include $(LIBMLXDIR) /opt/X11/include
else
INCS	:= ./include $(LIBFTDIR)/include $(LIBMLXDIR)
endif

LIBDIRS	:= $(LIBFTDIR) $(LIBMLXDIR) 
IFLAGS	:= $(addprefix -I,$(INCS))
LFLAGS	:= $(addprefix -L,$(LIBDIRS))
LIBS	:= $(LIBFT) $(LIBMLX)

CC	:= cc
CFLAGS	:= -Wall -Wextra -Werror
ifeq ($(shell uname),Darwin)
LDFLAGS := $(IFLAGS) -L$(LIBFTDIR) -lft -lm -L/usr/X11R6/lib -lmlx -lXext -framework OpenGL -framework AppKit
else
#LDFLAGS := $(IFLAGS) $(LFLAGS) -lft -lm -lmlx -lX11 -lXext
LDFLAGS := $(IFLAGS) $(LFLAGS) -lft -lm -lmlx -lX11 -lXext -fsanitize=address  -fsanitize=undefined -fsanitize=leak -g3

endif

ifdef WITH_BONUS
DFLAGS  := -D BONUS=1
endif

all:	$(LIBMLX)	
	echo $(DELENTRY)
	@make -C $(LIBFTDIR)
	@make -C $(LIBMLXDIR)
	@make $(NAME)	

$(NAME)	:	$(OBJECTS) $(LIBS) 
		$(CC)  $(CFLAGS) $(OBJECTS) $(LDFLAGS) $(DFLAGS) -o $@
		$(RM) $(DELENTRY:.c=.o)
		$(RM) $(DELENTRY:.c=.d)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) / $(*D)
	$(CC) $(CFLAGS) $(IFLAGS) $(BONUS_FLAG) $(DFLAGS) -c $< -MMD -MP -MF   $(OBJDIR)/$*.d  -o $@

$(LIBMLX) :
	tar zxvf $(LIBMLXTAR) -C $(LIB)

clean	:
			$(RM) $(OBJECTS)
			$(RM) $(DEPS)
			$(RM) $(OBJDIR)/$(ENTRY:.c=.o)
			$(RM) $(OBJDIR)/$(ENTRY:.c=.d)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.o)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.d)
			$(RM) $(DELENTRY:.c=.o)
			$(RM) $(DELENTRY:.c=.d)
			echo	$(ENTRYBONUS)
			echo	$(ENTRY)
			@make clean -C $(LIBFTDIR)
			@make clean -C $(LIBMLXDIR)

fclean	:	clean
			$(RM) $(NAME)
			$(RM) $(LIBS)

re	:		fclean all

bonus	:	
			@make WITH_BONUS=1

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

.PHONY: all clean fclean bonus re
