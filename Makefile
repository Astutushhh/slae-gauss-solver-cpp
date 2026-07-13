# ----------------------------------------------------------------------------------------------------------------------------------
# То что можно и нужно менять
# ----------------------------------------------------------------------------------------------------------------------------------

PROGRAM_NAME = gauss_solver
 
# Путь к компилятору (оставь пустым, если в PATH)
PATH_TO_COMPILER_DIR = 
 
# Префикс компилятора (оставь пустым для обычного gcc/g++)
COMPILER_APPENDIX = 
 
# Папка для скомпилированных файлов
PATH_TO_BUILD_DIR = build/

FIND := /usr/bin/find

SOURCES := $(shell $(FIND) . \( -path './build' -o -path './.git' -o -path './.vscode' \) -prune -o -name "*.cpp" -print)

INCLUDES := $(shell $(FIND) . \( -path './build' -o -path './.git' -o -path './.vscode' \) -prune -o -type d -print)
# ----------------------------------------------------------------------------------------------------------------------------------
# То что лучше не трогать
# ----------------------------------------------------------------------------------------------------------------------------------
 
PATH_TO_C_COMPILER = $(strip $(PATH_TO_COMPILER_DIR))$(strip $(COMPILER_APPENDIX))gcc
PATH_TO_CXX_COMPILER = $(strip $(PATH_TO_COMPILER_DIR))$(strip $(COMPILER_APPENDIX))g++
PATH_TO_ASM_COMPILER = $(strip $(PATH_TO_COMPILER_DIR))$(strip $(COMPILER_APPENDIX))as
PATH_TO_OBJDUMP = $(strip $(PATH_TO_COMPILER_DIR))$(strip $(COMPILER_APPENDIX))objdump
 
PATH_TO_TARGET_FILE = $(strip $(PATH_TO_BUILD_DIR))$(PROGRAM_NAME).exe
PATH_TO_LIST_FILE = $(strip $(PATH_TO_BUILD_DIR))$(PROGRAM_NAME).list
PATH_TO_MAP_FILE = $(strip $(PATH_TO_BUILD_DIR))$(PROGRAM_NAME).map
 
OBJECTS = $(addprefix $(PATH_TO_BUILD_DIR), $(addsuffix .o,$(basename $(SOURCES))))
 
# Флаги
CXX_COMPILE_FLAGS = -Og -ggdb -Wall -c $(addprefix -I,$(strip $(INCLUDES)))
CXX_LINKING_FLAGS = -Og $(strip $(LINKER_FLAGS))
LINKER_FLAGS = -Wl,-Map=$(PATH_TO_MAP_FILE)
OBJDUMP_FLAGS = -d
 
# ----------------------------------------------------------------------------------------------------------------------------------
# Правила сборки
# ----------------------------------------------------------------------------------------------------------------------------------
 
.PHONY: all build clean rebuild create_folders
 
all: build $(PATH_TO_LIST_FILE)
 
build: create_folders $(OBJECTS)
	$(PATH_TO_CXX_COMPILER) $(CXX_LINKING_FLAGS) $(OBJECTS) -o $(PATH_TO_TARGET_FILE)
 
rebuild: clean all
 
$(PATH_TO_BUILD_DIR)%.o: %.cpp
	$(PATH_TO_CXX_COMPILER) $(strip $(CXX_COMPILE_FLAGS)) $< -o $@
 
$(PATH_TO_BUILD_DIR)%.o: %.c
	$(PATH_TO_C_COMPILER) $(strip $(CXX_COMPILE_FLAGS)) $< -o $@
 
$(PATH_TO_LIST_FILE): $(PATH_TO_TARGET_FILE)
	$(PATH_TO_OBJDUMP) $(OBJDUMP_FLAGS) $(PATH_TO_TARGET_FILE) > $(PATH_TO_LIST_FILE)
 
clean:
	-rm -rf $(PATH_TO_BUILD_DIR)
 
create_folders:
	mkdir -p $(PATH_TO_BUILD_DIR)
	@mkdir -p $(addprefix $(PATH_TO_BUILD_DIR), $(sort $(dir $(SOURCES))))