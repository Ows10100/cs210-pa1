Reflection - CS 210 Programming Assignment 1

1. Why does concat only need to work between two lists of the same representation? What would you have to do differently, or what would go wrong, if you tried to make it work between a LinkedList and an ArrayList?

`concat` is designed to concatenate only the list types having the same representation, because both are handling their own memory in a different way—one by using the contiguous heap array and its tracking of capacity, and the second by using scattered node objects connected by pointers. If these two structures were concatenated, it would be necessary to convert one of them into the other structure, which requires the checking of the type and allocating the memory again. In any case, there is a threat of memory leaks, segmentation faults, or violation of encapsulation principles.

2. Walk through reverse() on your linked list: name the three pointers you need alive at once, and explain why losing track of any one of them mid-loop corrupts the list.

The three pointers that must be kept alive at any one time during an in-place reversal of a linked list are `prev`, which indicates the part of the list that has already been reversed; `current`, which is the node that is presently being operated on; and `next`, which contains the rest of the list after it has been broken away from the current node. If `current` were lost, the remainder of the traversal would have no reference point, thus ending the loop.

3. Both addAnyWhere and deleteAnyWhere require a bounds check. What’s the valid range for position in each, and what does your implementation do if a caller passes a position outside it?

In case of `addAnywhere`, the range will be `[0, size]` because any object can be added at first position, middle, or at last position. But the range of `deleteAnywhere` will be `[0, size - 1]` since there is no possibility of deleting anything from the non-existent position. If there occurs any attempt by anyone to access any invalid position, my solution will take care of it through proper boundary checking.

4. In LinkedList::concat, why did you need to walk to the end of the list first, when addFront and deleteFront never needed to? What would change about concat’s performance if LinkedList still tracked a tail pointer, and what would you have to keep updated elsewhere if you added one back?

`concat()` will have to traverse to the end of the first list in order to link the head of the second list to the last element's `next` pointer, while `addFront()` and `deleteFront()` will always deal just with the head. With the existence of a tail pointer, the `concat()` function would be able to link the second list in $O(1)$ time rather than $O(n)$ time. On the other hand, having the tail pointer again will imply that all insertions, deletions, and reversals (`addFront()`, `deleteAnywhere()`, `reverse()`, and others) will have to take special care for updating the tail pointer correctly.

5. Pick either addAnywhere or deleteAnywhere in ArrayList and explain, in your own words, what has to shift and in which direction, and why shifting in the wrong direction would overwrite data you still need.

In case of `addAnywhere` using an `ArrayList`, shifting to accommodate the newly added element takes place from the target insertion point to the end of the `ArrayList`. The operation should take place starting at the last location of the array towards the target insertion index. If the shifting were done in reverse order; that is, from the insertion index to the end of the array, then the immediate element after the insertion point would be overwritten before being copied.

6. Indicate the specific line of code within your main.cpp file in which a Reverse card affects the direction of play, and describe what problem there would be in the game if this line was absent.

Statement "turnOrder->reverse();" from main.cpp file depicts how the Reverse Card is implemented. In the above statement, reverse function is used directly to reverse the list of players. The absence of this statement means that the turn order will follow exactly the same forward sequence despite the use of Reverse card. On the output side, the output of the game will show the players' sequence as it is.