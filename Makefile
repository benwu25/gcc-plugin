all:
	/home/benwu25/Documents/mirror/install/bin/g++ -g -Wall -Wextra -fanalyzer -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter -fPIC -shared -rdynamic -fno-rtti -I/home/benwu25/Documents/mirror/install/lib/gcc/x86_64-pc-linux-gnu/16.0.0/plugin/include -L/home/benwu25/Documents/mirror/install/lib/gcc/x86_64-pc-linux-gnu/16.0.0/plugin -o libGCCPlugin.so gcc-plugin.cc -lcp1plugin

test: all
	/home/benwu25/Documents/mirror/install/bin/g++ -fplugin=./libGCCPlugin.so main.cpp

test-debug: all
	/home/benwu25/Documents/mirror/install/bin/g++ -fplugin=./libGCCPlugin.so main.cpp -wrapper gdb,--args

clean:
	rm libGCCPlugin.so

clean2: clean
	rm a.out
