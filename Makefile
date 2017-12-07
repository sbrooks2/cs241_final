all: cimg-demo

cimg-demo: cimg-demo.cpp
	g++ -o cimg-demo cimg-demo.cpp -I/opt/X11/include -L/opt/X11/lib -lX11 -lpthread -std=gnu++0x

clean:
	rm p1