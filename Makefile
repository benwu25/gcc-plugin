all:
	g++ -g -Wall -Wextra -fanalyzer -Wno-unused-variable -Wno-unused-parameter -Werror -fPIC -shared -I/usr/lib/gcc/x86_64-linux-gnu/13/plugin/include -L/usr/lib/gcc/x86_64-linux-gnu/13/plugin -o libGCCPlugin.so gcc-plugin.cc

test: all
	g++ -fplugin=./libGCCPlugin.so main.cpp

test-debug: all
	/home/benwu25/Documents/mirror/gcc-install/gcc-install/bin/g++ -fplugin=./libGCCPlugin.so main.cpp -wrapper gdb,--args

clean:
	rm libGCCPlugin.so

clean2: clean
	rm a.out
