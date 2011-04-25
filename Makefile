GCC=gcc

PLUGIN_SOURCE_FILES= \
  gcc-python.c \
  gcc-python-closure.c \
  optpass.c \
  gcc-python-tree.c \
  autogenerated-tree.c \
  autogenerated-gimple.c

PLUGIN_OBJECT_FILES= $(patsubst %.c,%.o,$(PLUGIN_SOURCE_FILES))
GCCPLUGINS_DIR:= $(shell $(GCC) --print-file-name=plugin)

PYTHON_CONFIG=python-debug-config
PYTHON_CFLAGS=$(shell $(PYTHON_CONFIG) --cflags)
PYTHON_LDFLAGS=$(shell $(PYTHON_CONFIG) --ldflags)

CFLAGS+= -I$(GCCPLUGINS_DIR)/include -fPIC -O2 -Wall -Werror -g $(PYTHON_CFLAGS) $(PYTHON_LDFLAGS)

plugin: python.so

python.so: $(PLUGIN_OBJECT_FILES)
	$(GCC) $(CFLAGS) -shared $^ -o $@

clean:
	rm -f *.so *.o
	rm -f optpass.c
	rm -f autogenerated*

optpass.c: optpass.pyx
	cython $^ -o $@

autogenerated-gimple-types.txt: gimple-types.txt.in
	cpp $(CFLAGS) $^ -o $@

autogenerated-tree-types.txt: tree-types.txt.in
	cpp $(CFLAGS) $^ -o $@

autogenerated-tree.c: cpybuilder.py generate-tree-c.py autogenerated-tree-types.txt
	python generate-tree-c.py > $@

autogenerated-gimple.c: cpybuilder.py generate-gimple-c.py autogenerated-gimple-types.txt
	python generate-gimple-c.py > $@

# Hint for debugging: add -v to the gcc options 
# to get a command line for invoking individual subprocesses
# Doing so seems to require that paths be absolute, rather than relative
# to this directory
TEST_CFLAGS= \
  -fplugin=$(shell pwd)/python.so \
  -fplugin-arg-python-script=test.py

test: plugin
	gcc -v $(TEST_CFLAGS) $(shell pwd)/test.c 

