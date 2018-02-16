/*
Proof of concept.
A heiarchical data structure that works like a binary tree
but has pointers to possible letters.
What this means is that the time to lookup is dependent on the
length of the identifier, not the total number of identifiers.
You could have thousands of identifiers, although the tradeoff is it
uses a lot more memory because its a tree of possibilities.
Here we only allow for capital letters, it could be extended to other
characetr spaces, like lowercase letters and '_'.
I have not tested the total memory impact of having a lot of identifiers.
Maybe there is a different way to allocate these that has less of an
impact on memory.
*/
#include <stdlib.h>
struct lnode{
	struct lnode *symb['Z'-'A'];
	int data;//Could be anything, data to be associated with the symbol
	//Ideally this data is just a pointer to bigger data somewhere else.
	//Storing large structures for most nodes would waste space.
	//Because most nodes don't even have associated data.
};

#define POOL_SIZE 20000
struct lnode pool[POOL_SIZE];
struct lnode *nodeAlloc = (struct lnode*)&pool;
struct lnode head;

//Allocs a new branch if needed, otherwise travels to a lower branch.
struct lnode* traverse(char insert_point, struct lnode *this){
	if(this->symb[insert_point - 'A'] == NULL){	
		struct lnode *subNode = nodeAlloc++;
		*subNode = (struct lnode){0};//Most ptrs will be NULL.
		this->symb[insert_point - 'A'] = subNode;
		return subNode;
	}
	return this->symb[insert_point - 'A']; 
}

void addIdentifier(char*key, int data){
	struct lnode *curr = &head;
	for(char *c = key;*c!='\0';c++){
		curr = traverse(*c, curr);
	}
	curr->data = data;
}

//Get the data associated with an identifier.
//Speed of execution is based on the length of the input string,
//Returns NULL pointer if it does not exist.
int* search(char*key){
	struct lnode *curr = &head;
	char *c;
	for(c = key; *c!='\0';c++){
		curr = curr->symb[*c - 'A'];
		if(curr == NULL){
			return NULL;
		}
	}
	return &curr->data;
}

//Testing
#include <stdio.h>
void testFind(char*key){
	int*data = search(key);
	if(data){
		printf("'%s' has value %d\n", key, *data);
		return;
	}
	printf("Symbol '%s' does not exist.\n", key);
}

int main(){
	addIdentifier("TEST", 5);
	addIdentifier("WORD", 42);
	addIdentifier("THING", 57);
	addIdentifier("LONGERIDENTIFIER", 21);
	addIdentifier("HAHA", 0);
	addIdentifier("GLCLEAR", 0);
	addIdentifier("GLGENBUFFERS", 0);
	addIdentifier("WHATTHE", 0);
	addIdentifier("MORENAMES", 0);

	testFind("TEST");
	testFind("WAH");
	testFind("WORD");
	testFind("THING");
	testFind("LONGERIDENTIFIER");
	testFind("TESTS");	

	long numAllocs = nodeAlloc - pool;
	printf("Current number of allocated nodes: %ld\n", numAllocs);
	printf("Size of each node: %ld\n", sizeof(struct lnode));
	printf("Bytes used: %ld\n", sizeof(struct lnode) * numAllocs);
}
