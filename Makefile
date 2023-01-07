NAME 	:= cub3D
LIB	:= ./lib/

LIBMLXDIR	:= $(LIB)/minilibx-linux
LIBMLXTAR	:= $(LIB)/minilibx-linux.tgz
LIBMLX		:= $(LIBMLXDIR)/libmlx.a

LIBFTDIR	:= $(LIB)/libft
LIBFTNAME	:= libft.a
LIBFT		:= $(LIBFTDIR)/$(LIBFTNAME)

SRCDIR	:= ./srcs/
SRC	:= init.c arg.c hook.c mouse.c key.c close.c window.c wall.c affine.c ray.c angle_utils.c map_utils.c calc_texture_mapping.c ray_utils.c 
ENTRY	:= main.c
ENTRYBONUS	:= main_bonus.c
ifdef WITH_BONUS
ENTRY	:= $(ENTRYBONUS)
endif
SRC	+= $(ENTRY)

SRCS	:= $(addprefix $(SRCDIR), $(SRC))
OBJS	:= $(SRCS:.c=.o)
OBJDIR	:= ./obj
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
LDFLAGS := $(IFLAGS) $(LFLAGS) -lft -lm -lmlx -lX11 -lXext -fsanitize=address  -fsanitize=undefined -fsanitize=leak -g3
#LDFLAGS := $(IFLAGS) $(LFLAGS) -lft -lm -lmlx -lX11 -lXext

endif

all:	$(LIBMLX)	
	@make -C $(LIBFTDIR)
	@make -C $(LIBMLXDIR)
	@make $(NAME)	

$(NAME)	:	$(OBJECTS) $(LIBS) 
		$(CC)  $(CFLAGS) $(OBJECTS)  $(LDFLAGS) -o $@


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) / $(*D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -MMD -MP -MF   $(OBJDIR)/$*.d  -o $@
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

$(LIBMLX) :
	tar zxvf $(LIBMLXTAR) -C $(LIB)

clean	:
			$(RM) $(OBJECTS)
			$(RM) $(DEPS)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.o)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.d)
			make clean -C $(LIBFTDIR)
			make clean -C $(LIBMLXDIR)

fclean	:	clean
			$(RM) $(NAME)
			$(RM) $(LIBS)

re	:		fclean all

bonus	:	
			@make WITH_BONUS=1

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

.PHONY: clean fclean bonus re
