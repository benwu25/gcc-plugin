my-pass.o: my-pass.h my-pass.cc
	/home/benwu25/gcc-install/bin/g++ -g -Wall -Wextra -fanalyzer -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter -fPIC -rdynamic -fno-rtti -I/home/benwu25/gcc-install/lib/gcc/x86_64-pc-linux-gnu/16.0.0/plugin/include -c -o my-pass.o my-pass.cc

all: my-pass.o
	/home/benwu25/gcc-install/bin/g++ -g -Wall -Wextra -fanalyzer -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter -fPIC -shared -rdynamic -fno-rtti -I/home/benwu25/gcc-install/lib/gcc/x86_64-pc-linux-gnu/16.0.0/plugin/include -L/home/benwu25/gcc-install/lib/gcc/x86_64-pc-linux-gnu/16.0.0/plugin -o libGCCPlugin.so gcc-plugin.cc -lcp1plugin my-pass.o

test: all
	/home/benwu25/gcc-install/bin/g++ -fplugin=./libGCCPlugin.so main.cpp

test-debug: all
	/home/benwu25/gcc-install/bin/g++ -fplugin=./libGCCPlugin.so main.cpp -wrapper gdb,--args

clean:
	rm libGCCPlugin.so

clean2: clean
	rm a.out my-pass.o
