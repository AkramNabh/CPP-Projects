#include "Image.h"
#include <math.h>
#include <vector>
struct point {
	float x, y;
};

int main() {

	int width,
		height,
		min = 255,
		max = 0,
		hist[256] = { 0 },
		cdf[256] = { 0 },
		mapping[256] = { 0 };
	float contrast,
		numOfPixels;
	std::vector<RGBA> colorPallet;
	ColorImage myimg_s;

	myimg_s.Load("input.png");

	width = myimg_s.GetWidth();
	height = myimg_s.GetHeight();
	numOfPixels = width * height;
	GrayscaleImage greyscaleImage_s(width, height);
	GrayscaleImage greyscaleImage_h(width, height);
	GrayscaleImage greyscaleImage_both(width, height);
	GrayscaleImage grayscaleCompare;
	grayscaleCompare.Load("input.png");
	ColorImage myimg_h(myimg_s);
	ColorImage myimg_both(myimg_s);


	//transforming from colored to greyscale

	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++) {
			greyscaleImage_s(w, h) = myimg_s(w, h).r / 3 + myimg_s(w, h).g / 3 + myimg_s(w, h).b / 3;
			greyscaleImage_h(w, h) = myimg_s(w, h).r / 3 + myimg_s(w, h).g / 3 + myimg_s(w, h).b / 3;
			greyscaleImage_both(w, h) = myimg_s(w, h).r / 3 + myimg_s(w, h).g / 3 + myimg_s(w, h).b / 3;

		}
	}


	//calculating the contrast value

	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++) {
			if (greyscaleImage_s(w, h) < min) {
				min = greyscaleImage_s(w, h);
			}
			if (greyscaleImage_s(w, h) > max) {
				max = greyscaleImage_s(w, h);
			}


			hist[greyscaleImage_h(w, h)]++;
		}
	}
	contrast = 255.0f / (max - min);


	cdf[0] = hist[0];
	for (int i = 1; i < 256; i++) {
		cdf[i] = cdf[i - 1] + hist[i];
	}

	for (int i = 0; i < 256; i++) {
		mapping[i] = (int)((cdf[i] / numOfPixels) * 255);
	}
	

	// applying contrast to greyscale
	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++) {
			greyscaleImage_s(w, h) = (greyscaleImage_s(w, h) - min) * contrast;
			greyscaleImage_both(w, h) = (greyscaleImage_both(w, h) - min) * contrast;
		}
	}
	
	// applying histogram equalization to greyscale
	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++) {
			greyscaleImage_h(w, h) = mapping[greyscaleImage_h(w, h)];
			greyscaleImage_both(w, h) = mapping[greyscaleImage_both(w, h)];
		}
	}


	//reverting image from greyscale to colored


	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++) {
		
			myimg_s(w, h).r = myimg_s(w, h).r + greyscaleImage_s(w, h);
			myimg_s(w, h).g = myimg_s(w, h).g + greyscaleImage_s(w, h);
			myimg_s(w, h).b = myimg_s(w, h).b + greyscaleImage_s(w, h);
			myimg_h(w, h).r = myimg_s(w, h).r + greyscaleImage_h(w, h);
			myimg_h(w, h).g = myimg_s(w, h).g + greyscaleImage_h(w, h);
			myimg_h(w, h).b = myimg_s(w, h).b + greyscaleImage_h(w, h);
			myimg_both(w, h).r = myimg_s(w, h).r + greyscaleImage_both(w, h);
			myimg_both(w, h).g = myimg_s(w, h).g + greyscaleImage_both(w, h);
			myimg_both(w, h).b = myimg_s(w, h).b + greyscaleImage_both(w, h);
		
		}
	}


	/*
	
	just to say, i gave it my shot to read a colored and do the effect on a colored image, the output i am 
	getting was the closest to the required, just i dont know what happens to the blue channel.

	i commented out the save for both the color images, but if you want to take a look, just 
	uncomment and compile.

	plus i commented a picture combining both of the formulas to give a very nice output
	
	*/
	greyscaleImage_s.Save("output-s.png");
	greyscaleImage_h.Save("output-h.png");
	grayscaleCompare.Save("greyscaled-for-comparing.png");
//	greyscaleImage_both.Save("output-both.png");
//	myimg_s.Save("contrastedcolored-s.png");
//	myimg_h.Save("contrastedcolored-h.png");
//	myimg_both.Save("contrastedcolored-both.png");
	return 0;
}
