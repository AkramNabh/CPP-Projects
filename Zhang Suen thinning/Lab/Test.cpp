#include "Image.h"
#include <math.h>
#include <vector>
#include <string>

int main() {

	GrayscaleImage TestRuns;

	TestRuns.Load("input.png");
	int width = TestRuns.GetWidth(), height = TestRuns.GetHeight(), sum = 0, adder = 0;
	GrayscaleImage output(width, height);
	//2D vector to save coordinates easily
	std::vector<std::vector<int>> values(width, std::vector<int>(height));

	//global thresholding
	for (int i = 0; i < width; i++) {
		for (int y = 0; y < height; y++) {
			sum += (TestRuns(i, y));
			++adder;
		}
	}
	sum = sum / adder;

	//binary transformation
	for (int x = 0; x < TestRuns.GetWidth(); x++) {
		for (int y = 0; y < TestRuns.GetHeight(); y++) {

			if (TestRuns(x, y) <= sum) {
				TestRuns(x, y) = 255;
			}
			else {
				TestRuns(x, y) = 0;
			}
		}
	}

	//transforming 255,0 to binary 1,0
	for (int x = 0; x < TestRuns.GetWidth(); x++) {
		for (int y = 0; y < TestRuns.GetHeight(); y++) {
			if (TestRuns(x, y) == 255) {
				values[x][y] = 1;
			}
			else {
				values[x][y] = 0;
			}
		}
	}

	int Xaxis = values.size();
	int Yaxis = values[0].size();
	bool loopBreaker = false;

	//zhang suen algorithm
	while (!loopBreaker) {
		loopBreaker = true;
		std::vector<std::pair<int, int>> deletedPixels;

		for (int i = 1; i < Xaxis - 1; ++i) {
			for (int z = 1; z < Yaxis - 1; ++z) {
				int center = values[i][z];

				if (center == 0) {
					continue;
				}
				//kernal calculation
				int top_left = values[i - 1][z - 1];
				int top = values[i][z - 1];
				int top_right = values[i + 1][z - 1];
				int left = values[i - 1][z];
				int right = values[i + 1][z];
				int bottom_left = values[i - 1][z + 1];
				int bottom = values[i][z + 1];
				int bottom_right = values[i + 1][z + 1];

				int nCounts = left + bottom_left + bottom + bottom_right + right + top_right + top + top_left;

				if (2 <= nCounts && nCounts <= 6) {
					int tran = 0;
					if (left == 0 && bottom_left == 1) ++tran;
					if (bottom_left == 0 && bottom == 1) ++tran;
					if (bottom == 0 && bottom_right == 1) ++tran;
					if (bottom_right == 0 && right == 1) ++tran;
					if (right == 0 && top_right == 1) ++tran;
					if (top_right == 0 && top == 1) ++tran;
					if (top == 0 && top_left == 1) ++tran;
					if (top_left == 0 && left == 1) ++tran;

					//condition of deleting
					if (tran == 1 && (left * bottom * right == 0) &&
						(bottom * right * top == 0)) {
						deletedPixels.push_back(std::make_pair(i, z));
					}

				}
			}
		}

		for (const auto& pixel : deletedPixels) {
			values[pixel.first][pixel.second] = 0;
		}

		if (!deletedPixels.empty()) {
			loopBreaker = false;
			deletedPixels.clear();
		};

		for (int i = 1; i < Xaxis - 1; ++i) {
			for (int z = 1; z < Yaxis - 1; ++z) {

				int center = values[i][z];
				if (center == 0) {
					continue;
				}

				int top_left = values[i - 1][z - 1];
				int top = values[i][z - 1];
				int top_right = values[i + 1][z - 1];
				int left = values[i - 1][z];
				int right = values[i + 1][z];
				int bottom_left = values[i - 1][z + 1];
				int bottom = values[i][z + 1];
				int bottom_right = values[i + 1][z + 1];

				int nCount = left + bottom_left + bottom + bottom_right + right + top_right + top + top_left;

				if (2 <= nCount && nCount <= 6) {
					int trans = 0;

					if (left == 0 && bottom_left == 1) ++trans;
					if (bottom_left == 0 && bottom == 1) ++trans;
					if (bottom == 0 && bottom_right == 1) ++trans;
					if (bottom_right == 0 && right == 1) ++trans;
					if (right == 0 && top_right == 1) ++trans;
					if (top_right == 0 && top_left == 1) ++trans;
					if (top == 0 && top_left == 1) ++trans;
					if (top_left == 0 && left == 1) ++trans;

					if (trans == 1 && (left * bottom * top == 0) &&
						(left * right * top == 0)) {
						deletedPixels.push_back(std::make_pair(i, z));
					}
				}
			}
		}

		for (const auto& pixel : deletedPixels) {
			values[pixel.first][pixel.second] = 0;
		}

		if (!deletedPixels.empty()) {
			loopBreaker = false;
		}


	}


	// returning values to the output image
	for (int x = 0; x < TestRuns.GetWidth(); x++) {
		for (int y = 0; y < TestRuns.GetHeight(); y++) {

			if (values[x][y] == 1) {
				output(x, y) = 255;
			}
			else {
				output(x, y) = 0;
			}



		}
	}

	TestRuns.Save("output_binary.png");
	output.Save("output_skeletonized.png");

	//	myimg_both.Save("contrastedzored-both.png");
	return 0;
}