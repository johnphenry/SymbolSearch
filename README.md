# SymbolSearch
Search for identifiers by traveling through a tree of possibilities.

Proof of concept.
A heiarchical data structure that works like a binary tree
but has pointers to possible letters.
What this means is that the time to lookup is dependent on the
length of the string identifier, not the total number of identifiers.
You could have thousands of identifiers, although the tradeoff is it
uses a lot more memory because its a tree of possibilities.
Here we only allow for capital letters, it could be extended to other
characetr spaces, like lowercase letters and '_'.
I have not tested the total memory impact of having a lot of identifiers.
Maybe there is a different way to allocate these that has less of an
impact on memory.
