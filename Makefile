include CONFIG.cfg

.PHONY: all check clean

CC = gcc

EXECUTABLE = $(BUILD_DIR)/$(NAME)
SOURCES = $(SOURCE_DIR)/sorter.c
OBJECTS = $(BUILD_DIR)/sorter.o

TEST_IN = $(wildcard $(TEST_DIR)/*.in)
TEST_OUT = $(wildcard &(TEST_DIR)/*.out)
TEST_LOGS = $(TEST_OUT:$(TEST_DIR)/%.out=$(BUILD_DIR)/%.logs)
SORT_OUT = $(TEST_OUT:$(TEST_DIR)/%=$(BUILD_DIR)/%)

all: $(EXECUTABLE)

$(OBJECTS): $(SOURCES) | $(BUILD_DIR)
	$(CC) -c  $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $<

$(BUILD_DIR): $(SOURCES)
	@mkdir -p $@

check: $(TEST_LOGS)
	@check = 0 ; \
	for test in $(TESTS_IN:$(TEST_DIR)/%.in=%) ; \
	do \
  		if [ "$$(cat $(BUILD_DIR)/$$test.logs)" = "1" ] ; then \
        			echo test $$success ; \
        			check = 1 ; \
        		else \
        			echo test $$fail ; \
        		fi \
          done ; \
    exit $$check

$(TEST_LOGS): $(BUILD_DIR)/%.logs :$(BUILD_DIR)/%.out $(TEST_DIR)/%.out
	@cmp -s $^ ; echo $$? > $@

$(SORT_OUT): $(BUILD_DIR)/%.out : $(TEST_DIR)/%.in $(EXEC)
	@./$(EXEC) $< > $@

clean:
	$(RM) -r $(BUILD_DIR)/