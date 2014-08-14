# You can put your build options here
-include config.mk

ROOT_DIRECTORY:=.
DEFAULT_LIB_INSTALL_PATH ?= ../../dist/

majorve :=1
minorve :=0
libname :=jsmn
version :=$(majorve).$(minorve).0
solib   :=lib$(libname).so.$(version)
soname  :=lib$(libname).so.$(majorve)
arlib   :=lib$(libname).a

SOFLAGS:= -Wl,-soname,$(soname) -Wl,-soname,lib$(libname).so -Wl,-rpath,$(DEFAULT_LIB_INSTALL_PATH)
CFLAGS += -g

all: install

install:$(solib) 
	#$(arlib)
	cp $(solib) $(DEFAULT_LIB_INSTALL_PATH)
	ldconfig -n -N $(DEFAULT_LIB_INSTALL_PATH)

$(arlib): jsmn.o
	$(AR) rc $@ $^

$(solib): jsmn.o
	$(CC) $(CFLAGS) $(CXXFLAGS) $(INCFLAGS) -std=c++0x -shared $< $(SOFLAGS) -o $@ -lACE

%.o: %.c jsmn.h
	$(CC) $(CFLAGS) -fPIC -c  $< -o $@

test: jsmn_test
	./jsmn_test

jsmn_test: jsmn_test.o $(arlib)
	$(CC) $(CFLAGS) -o $@ $< $(arlib)

#jsmn_test.o: jsmn_test.c libjsmn.a

clean:
	rm -f jsmn.o jsmn_test.o jsmn_test jsmn_test.exe $(arlib) $(solib)

.PHONY: all clean test install

