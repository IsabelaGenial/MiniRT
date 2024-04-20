### CODAM BUILD
LIBMLX = libmlx42.a
MLXSRC = https://github.com/codam-coding-college/MLX42.git
BUILD_DIR_MLX = $(MLXDIR)/build
MLX_INCLUDE = ./MLX42/include/MLX42/
LIBMLX_TARGET = $(BUILD_DIR_MLX)/$(LIBMLX)
LIBX_FLAGS = -lmlx -lXext -lX11 -lm -lz
MLXDIR = ./MLX42
CODAM_LIB_FLAGS = -L./MLX42/build/ -lmlx42 -ldl -lglfw -pthread -lm


### LIBFT
LIBFT = ./libs/*.a
SRCSLIB = $(wildcard ./src/*/*.c)
LIB_OBJS = $(wildcard libs/objs/*.o)
LIB_BOBJS = $(wildcard libs/objs_bonus/*.o)
LIB := minirt.a

### MINIRT
NAME = minirt
SRC = minirt.c \
	  basic_tuple_operations.c compare_floats.c \
	  complex_tuple_operations.c create_tuples.c mult_matrices.c comparison.c \
	  transpose_matrix.c determinants.c minors.c submatrices.c chain_transformations.c \
      invert_matrix.c create_matrix.c translation.c rotation.c scaling.c intersect_shape.c \
      get_hit.c create_and_transform_rays.c intersection_coordinates.c colors.c \
	  set_transform.c surface_normals.c reflect.c create_material.c calculate_lighting.c \
	  create_world.c set_material.c intersect_world_with_ray.c prepare_computations.c shade_hit.c \
	  color_at.c view_transformation.c create_camera.c ray_for_pixel.c render.c intersect_sphere.c \
	  intersect_plane.c intersect_cylinder.c create_plane.c create_cylinder.c cylinder_setters.c \
	  shadows.c render_image.c endwith.c parse_ambient_and_light.c parse_camera.c parse_plane.c parse_utils.c \
	  parse_cylinder.c parse_sphere.c parse_functions_table.c parse_tokens_into_world.c caps.c \
	  check_type_identifiers.c file_validation.c open_file.c validate_line.c tokenizer.c create_sphere.c

VPATH = ./src ./src/math/canvas/ ./src/math/tuples/ ./src/math/ppm/ ./src/math/matrices \
		./src/math/matrix_transformations ./src/math/rays ./src/math/sphere \
		./src/math/rays/ ./src/math/light_and_shading/ ./src/math/making_scene/ \
		./src/math/camera/ ./src/math/cylinder/ ./src/math/plane/ ./src/math/create_intersection/ \
		./src/render ./src/input_validation ./src/parser ./src/tokenizer/ ./src/math/shape/

BUILD_SRC = ./build/
INCLUDE = -I ./include -I ./libs/
C_FLAGS = -Wall -Werror -Wextra -Ofast
OBJS = $(addprefix $(BUILD_DIR_RT),$(SRC:.c=.o))
BUILD_DIR_RT= ./build/
CMD = $(CC) $(LIBFT) $(OBJS) $(C_FLAGS) -I$(MLX_INCLUDE) -I $(INCLUDE) -c $< -o $@

### RECIPES

##### THIS IS FOR COMPILING ALL FUNCTIONS INTO A STATIC LIBRARY TO BE EASILY INCLUDED BY THE TESTERS #####

all: $(NAME)

$(NAME): $(LIBMLX_TARGET) $(OBJS)
	@printf "$(GREEN)[ Build ]$(DEF_COLOR) $(RED) $@ $(GREEN)complete $(DEF_COLOR)"
	@$(CC) $(C_FLAGS) $(OBJS) $(INCLUDE) -I$(MLX_INCLUDE) $(CODAM_LIB_FLAGS) -L ./libs/ -lft -o $@
	@compiledb make as_lib --no-print-directory

$(BUILD_DIR_RT)%.o: %.c $(LIBFT)
	@test -d $(BUILD_DIR_RT) || mkdir $(BUILD_DIR_RT)
	$(CC) $(C_FLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	make --no-print-directory -C ./libs && make bonus --no-print-directory -C ./libs

$(LIBMLX_TARGET): $(MLXDIR)
	cd $(MLXDIR) && cmake --build build -j4;

$(MLXDIR):
	git clone $(MLXSRC) $(MLXDIR);
	cd $(MLXDIR) && cmake -B build

mlxclean:
	@echo "Cleaning MLX42..."
	@rm -rf $(MLXDIR)

clean:
	@echo "Cleaning..."
	@make clean --no-print-directory -C libs/
	rm -rf $(BUILD_DIR_RT)

fclean: clean
	@echo "Fully Cleaning..."
	@make fclean --no-print-directory -C ./libs/
	@make clean --no-print-directory -C ./tests
	@rm -rf MLX42/
	@rm -f $(NAME) $(LIB)

makelib:
	@make --no-print-directory -C libs/

$(LIB): $(OBJS) $(LIB_OBJS) $(LIB_BOBJS)
	@printf "\n$(YELLOW)[ linking ] $(DEF_COLOR)objects into library $(YELLOW)$@ $(DEF_COLOR)\n"
	@mv $(LIBMLX_TARGET) $(LIB)
	@ar rcs $(LIB) $^

as_lib: all makelib $(LIB)
re: fclean all

# COLORS
GRAY = \033[0;37m
RED = \033[0;91m
BLUE = \033[0;94m
CYAN = \033[0;96m
GREEN = \033[0;92m
WHITE = \033[0;97m
YELLOW = \033[0;93m
MAGENTA = \033[0;95m
DEF_COLOR = \033[0;39m

.PHONY: all clean fclean re mlxclean
