TARGETS = edge segment

all: $(TARGETS)

# to_greyscale: cimg-demo.cpp
# 	g++ -g -o $@ $^ -I/opt/X11/include -L/opt/X11/lib -lX11 -lpthread -std=gnu++0x

edge: edge_detect.cpp
	g++ -o $@ $^ -I/opt/X11/include -L/opt/X11/lib -lX11 -lpthread -std=gnu++0x

segment: breadthfirst.cpp
	g++ -fstack-check -o $@ $^ -I/opt/X11/include -L/opt/X11/lib -lX11 -lpthread -std=gnu++0x

# hello: hello.cpp
# 		g++ -o $@ $^


clean:
	rm -f *.o $(TARGETS) *~