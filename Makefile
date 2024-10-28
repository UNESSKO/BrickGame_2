CC:=g++
TEST_FILES:= ./brick_game/snake/sourses/SnakeModel.cpp ./brick_game/snake/sourses/Snake.cpp
OFILES := SnakeModel.o Snake.o
LIBS = -lgtest -lgcov
LIBS_GCOV = $(LIBS) -fprofile-arcs -ftest-coverage --coverage
EXECUTE_FILE = CPP3_BrickGame_v2_0_1
TEST_EXECUTE_FILE = snake_test
GCOVDIR := gcov_report

all: install

install:
	make uninstall
	cd build && cmake . && make
	cd build && ./$(EXECUTE_FILE)

uninstall:
	cd build && rm -rf $(EXECUTE_FILE)

tests: clean
	mkdir -p "build"
	$(CC) $(TEST_FILES) $(LIBS_GCOV) -c
	$(CC) ./brick_game/snake/tests/*.cpp $(OFILES) $(LIBS) -o "build/test"
	./build/test

gcov_report: tests
	mkdir -p $(GCOVDIR)
	find . -name '*.gcda' -exec mv -t $(GCOVDIR) {} +
	find . -name '*.gcno' -exec mv -t $(GCOVDIR) {} +
	find . -name '*.gch' -exec mv -t $(GCOVDIR) {} +
	lcov --exclude '/usr/*' --capture --directory $(GCOVDIR) --output-file $(GCOVDIR)/coverage.info
	genhtml $(GCOVDIR)/coverage.info --output-directory $(GCOVDIR)/html

dvi:
	doxygen Doxyfile
	@sed -i 's/$$(LATEX_CMD) refman/$$(LATEX_CMD) refman || true/g' ./doxygen_output/latex/Makefile
	make -C ./doxygen_output/latex/ || true

dist:
	tar -cf brick_game_2_0.tar .

clean :
	find ./../ -type f -name '*.gch' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name '*.tar' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name '*.o' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name 'Snake.o' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name 'SnakeModel.o' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name 'snake_high_score.txt' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name '*.a' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name '*.gcda' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name '*.gcov' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name '*.gcno' ! -name 'CMakeLists.txt' -delete
	find ./../ -name '*.dSYM' -exec rm -rv {} +
	find ./../ -name 'doxygen_output' -exec rm -rv {} +
	find ./../ -name 'gcov_report' -exec rm -rv {} +
	find ./../ -type f -name '*.out' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name 'vgcore*' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name 'snake_high_score' ! -name 'CMakeLists.txt' -delete
	find ./../ -type f -name 'tetris_high_score' ! -name 'CMakeLists.txt' -delete

rebuild: clean install