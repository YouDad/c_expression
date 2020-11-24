test_objs := $(patsubst %.c, %.o, $(shell find * -name "*.c"))
test_objs += $(patsubst %.cpp, %.o, $(shell find * -name "*.cpp"))

tests := $(shell find * -name "*.cpp" | sed 's/\.cpp//;')
tests += $(shell find * -name "*.c" | sed 's/\.c//;')

.PHONY: default
default: compile

.PHONY: compile
compile: $(test_objs) $(objs)
	for test in $(tests); do \
		filename=`echo $${test} | sed 's/\//./g;'`; \
		$(CC) $(CPPFLAGS) -o $${filename}.test $${test}.o $(objs); \
	done;

.PHONY: install
install:
	mv *.test $(OUTDIR)/
