/** @file RectangleBinPack.h
	@author Jukka Jylänki

	This work is released to Public Domain, do whatever you want with it.

	@brief RectangleBinPack is a data structure for performing online rectangle bin packing.
*/
#ifndef RectangleBinPack_h
#define RectangleBinPack_h

#include "clb/Core/Ptr.h"

namespace rbp {

/** Performs 'discrete online rectangle packing into a rectangular bin' by maintaining 
	a binary tree of used and free rectangles of the bin. There are several variants
	of bin packing problems, and this packer is characterized by:
	- We're solving the 'online' version of the problem, which means that when we're adding
	  a rectangle, we have no information of the sizes of the rectangles that are going to
	  be packed after this one.
	- We are packing rectangles that are not rotated. I.e. the algorithm will not flip
	  a rectangle of (w,h) to be stored if it were a rectangle of size (h, w). There is no
	  restriction conserning UV mapping why this couldn't be done to achieve better
	  occupancy, but it's more work. Feel free to try it out.
	- The packing is done in discrete integer coordinates and not in rational/real numbers (floats).

	Internal memory usage is linear to the number of rectangles we've already packed.

	For more information, see
	- Rectangle packing: http://www.gamedev.net/community/forums/topic.asp?topic_id=392413
	- Packing lightmaps: http://www.blackpawn.com/texts/lightmaps/default.html
	
	Idea: Instead of just picking the first free rectangle to insert the new rect into,
	      check all free ones (or maintain a sorted order) and pick the one that minimizes 
			the resulting leftover area. There is no real reason to maintain a tree - in fact 
			it's just redundant structuring. We could as well have two lists - one for free 
			rectangles and one for used rectangles. This method would be faster and might
			even achieve a considerably better occupancy rate. */
class RectangleBinPack
{
public:
	/** A node of a binary tree. Each node represents a rectangular area of the texture
	    we surface. Internal nodes store rectangles of used data, whereas leaf nodes track 
	    rectangles of free space. All the rectangles stored in the tree are disjoint. */
	struct Node : public clb::RefCountable
	{
		// Left and right child. We don't really distinguish which is which, so these could
		// as well be child1 and child2.
		Ptr(Node) left;
		Ptr(Node) right;

		// The top-left coordinate of the rectangle.
		int x;
		int y;

		// The dimension of the rectangle.
		int width;
		int height;
	};

	/// Starts a new packing process to a bin of the given dimension.
	void Init(int width, int height);

	/// Inserts a new rectangle of the given size into the bin.
	/** Running time is linear to the number of rectangles that have been already packed.
		@return A pointer to the node that stores the newly added rectangle, or 0 
			if it didn't fit. */
	Node *Insert(int width, int height)
	{
		return Insert(&root, width, height);
	}

	/// Computes the ratio of used surface area.
	float Occupancy() const;

private:
	Node root;

	// The total size of the bin we started with.
	int binWidth;
	int binHeight;

	/// @return The surface area used by the subtree rooted at node.
	unsigned long UsedSurfaceArea(const Node &node) const;

	/// Inserts a new rectangle in the subtree rooted at the given node.
	Node *Insert(Node *node, int width, int height);
};

}

#endif
