#include "../MaxRectsBinPack.h"
#include "../Rect.h"

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>

using namespace std;

bool compareRectIds (Rect i, Rect j) { return (i.id < j.id); }

int main(int argc, char **argv)
{
	if (argc < 5 || argc % 2 != 1)
	{
		printf("Usage: MaxRectsBinPackTest binWidth binHeight w_0 h_0 w_1 h_1 w_2 h_2 ... w_n h_n\n");
		printf("       where binWidth and binHeight define the size of the bin.\n");
		printf("       w_i is the width of the i'th rectangle to pack, and h_i the height.\n");
		printf("Example: MaxRectsBinPackTest 256 256 30 20 50 20 10 80 90 20\n\n");
		printf("On error 1 will be returned. On success the return value is 0 and the x/y coordinates \n");
		printf("of each input rect will be printed to screen. The order of the output is the same as in the input.\n");
		return 0;
	}

	// Create a bin to pack to, use the bin size from command line.
	MaxRectsBinPack bin;
	int binWidth = atoi(argv[1]);
	int binHeight = atoi(argv[2]);
	bin.Init(binWidth, binHeight);

	vector<RectSize> rects;
	vector<Rect> sortedrects;

	// Pack each rectangle (w_i, h_i) the user inputted on the command line.
	for(int i = 3; i < argc; i += 2)
	{
		// Read next rectangle to pack.
		RectSize r;
		r.width = atoi(argv[i]);
		r.height = atoi(argv[i+1]);
		r.id = (i-3)/2;
		rects.push_back(r);
	}
	MaxRectsBinPack::FreeRectChoiceHeuristic heuristic = MaxRectsBinPack::RectBestShortSideFit;
	bin.Insert(rects, sortedrects, heuristic);

	// Test success or failure.
	if (rects.size() > 0) {
		printf("failed to place %d rects.\n", (int)rects.size());
		return 1;
	} else {
		sort(sortedrects.begin(), sortedrects.end(), compareRectIds);
		for (vector<Rect>::iterator it = sortedrects.begin(); it != sortedrects.end(); it++) {
			printf ("%d %d\n", it->x, it->y);
		}
		return 0;
	}
}
