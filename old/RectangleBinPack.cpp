/** @file RectangleBinPack.cpp
	@author Jukka Jylänki

	This work is released to Public Domain, do whatever you want with it.

	@brief RectangleBinPack is a data structure for performing online rectangle bin packing.
*/
#include "RectangleBinPack.h"

namespace rbp {

/** Restarts the packing process, clearing all previously packed rectangles and
	sets up a new bin of a given initial size. These bin dimensions stay fixed during
	the whole packing process, i.e. to change the bin size, the packing must be
	restarted again with a new call to Init(). */
void RectangleBinPack::Init(int width, int height)
{
	binWidth = width;
	binHeight = height;
	root.left = root.right = 0;
	root.x = root.y = 0;
	root.width = width;
	root.height = height;
}

/** @return A value [0, 1] denoting the ratio of total surface area that is in use.
	0.0f - the bin is totally empty, 1.0f - the bin is full. */
float RectangleBinPack::Occupancy() const
{
	unsigned long totalSurfaceArea = binWidth * binHeight;
	unsigned long usedSurfaceArea = UsedSurfaceArea(root);

	return (float)usedSurfaceArea/totalSurfaceArea;
}

/** Recursively calls itself. */
unsigned long RectangleBinPack::UsedSurfaceArea(const RectangleBinPack::Node &node) const
{
	if (node.left || node.right)
	{
		unsigned long usedSurfaceArea = node.width * node.height;
		if (node.left)
			usedSurfaceArea += UsedSurfaceArea(*node.left);
		if (node.right)
			usedSurfaceArea += UsedSurfaceArea(*node.right);

		return usedSurfaceArea;
	}

	// This is a leaf node, it doesn't constitute to the total surface area.
	return 0;
}

/** Running time is linear to the number of rectangles already packed. Recursively calls itself.
	@return 0 If the insertion didn't succeed. */
RectangleBinPack::Node *RectangleBinPack::Insert(RectangleBinPack::Node *node, int width, int height)
{
	// If this node is an internal node, try both leaves for possible space.
	// (The rectangle in an internal node stores used space, the leaves store free space)
	if (node->left || node->right)
	{
		if (node->left)
		{
			Node *newNode = Insert(node->left, width, height);
			if (newNode)
				return newNode;
		}
		if (node->right)
		{
			Node *newNode = Insert(node->right, width, height);
			if (newNode)
				return newNode;
		}
		return 0; // Didn't fit into either subtree!
	}

	// This node is a leaf, but can we fit the new rectangle here?
	if (width > node->width || height > node->height)
		return 0; // Too bad, no space.

	// The new cell will fit, split the remaining space along the shorter axis,
	// that is probably more optimal.
	int w = node->width - width;
	int h = node->height - height;
	node->left = new Node;
	node->right = new Node;
	if (w <= h) // Split the remaining space in horizontal direction.
	{
		node->left->x = node->x + width;
		node->left->y = node->y;
		node->left->width = w;
		node->left->height = height;

		node->right->x = node->x;
		node->right->y = node->y + height;
		node->right->width = node->width;
		node->right->height = h;
	}
	else // Split the remaining space in vertical direction.
	{
		node->left->x = node->x;
		node->left->y = node->y + height;
		node->left->width = width;
		node->left->height = h;

		node->right->x = node->x + width;
		node->right->y = node->y;
		node->right->width = w;
		node->right->height = node->height;
	}
	// Note that as a result of the above, it can happen that node->left or node->right
	// is now a degenerate (zero area) rectangle. No need to do anything about it,
	// like remove the nodes as "unnecessary" since they need to exist as children of
	// this node (this node can't be a leaf anymore).

	// This node is now a non-leaf, so shrink its area - it now denotes
	// *occupied* space instead of free space. Its children spawn the resulting
	// area of free space.
	node->width = width;
	node->height = height;
	return node;
}

}
