Adam Jusila, Rebecca Posner, Patrick Smith, and Sawyer Brooks
cs241 f17

Final Project: opening images

Just kidding. It's segmenting images.

Usage: make will generate two files: edge and segment. The commands run on OSX 10.12.6, and both have only been tested with JPGs.
	
	edge: converts an image to greyscale, applies a Gaussian blur, and creates a Sobel edge-map of an image. Takes a LONG time to run; using images with dimensions greater than 500x500 is not recommended.
		Usage: ./edge <inputfile.jpg> <outputfile.jpg>

		Modifiable parameters by line number:
			93:   src.blur(0.5);
				Applies a Gaussian blur to the image before running the edge detection. Disabling is recommended for computer-generated or non-photographic images.

			114: gx = xGradsobel(&src, x, y);
		    115: gy = yGradsobel(&src, x, y);
		    	Applies one of the Sobel (xGradsobel), Roberts Cross (xGradrob), or Prewitt (xGradprew) to the image. Sobel was the most successful; roberts was the most efficient (but, VERY bad on photographs).

		    129: if (output(y,x) > (int) (0.25*(float)(255)) ) {
		    	The 0.25 in this line will determine the threshold at which pixels will be considered edges. The standard algorithm will output pixels with brightness according to their rate of change relative to their neighbor. This is a sort of sensitivity setting for what to consider an edge.

	segment: takes an image output from edge (though it will run with any image and often yield interesting results) and runs a greedy breadth-first algorithm to get as many pixels as possible within the bounds of an edge and group them.
		Usage: ./segment <inputfile.jpg> <outputfile.jpg>

		Modifiable parameters by line number:
			195-231: color algorithms.

			277:  graph[x][y] = * new Graph(x, y, (src(x,y) >= 130));
				130 is the optional threshold for edge detection. Useful if you're using a standard Sobel output that hasn't been standardized per pixel to be 255 or 0 (edge/not edge).

Files:
	
	Makefile: see above; supports make and clean.

	CImg.h: the CImg library; required for compilation.

	bredthfirst.cpp: implementation of the above described breadth-first algorithm for segmenting images. Compiles into segment.

	edge_detect.cpp: compiles into edge. Implementation of three algorithms to run edge detection on an image.


~~~~~

We have adhered to the honor code in completing this assignment.

Sawyer Brooks, Adam Jussila, Rebecca Posner, and Patrick Smith.