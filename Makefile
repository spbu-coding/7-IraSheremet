include CONFIG.cfg

.PHONY: all check clean

CC = gcc

EXECUTABLE = $(BUILD_DIR)/$(NAME)
SOURCES = $(SOURCE_DIR)/sorter.c
OBJECTS = $(BUILD_DIR)/sorter.o

all: $(EXECUTABLE)

$(OBJECTS): $(SOURCES) | $(BUILD_DIR)
	$(CC) -c  $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $<

$(BUILD_DIR): $(SOURCES)
	@mkdir -p $@


clean:
	$(RM) -r $(BUILD_DIR)/