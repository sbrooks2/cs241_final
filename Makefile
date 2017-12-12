all: edge hello

to_greyscale: cimg-demo.cpp
	g++ -o $@ $^ -I/opt/X11/include -L/opt/X11/lib -lX11 -lpthread -std=gnu++0x

edge: edge_detect_final.cpp
	g++ -o $@ $^ -I/opt/X11/include -L/opt/X11/lib -lX11 -lpthread -std=gnu++0x

hello: hello.cpp
		g++ -o $@ $^


clean:
	rm p1