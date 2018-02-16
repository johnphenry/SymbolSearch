/*
Instead of using one big hash table,
you can use multiple smaller hash tables.
Each table now has less items to search through in turn.
*/
#include <map>
#include <string>
#include <stdio.h>
using namespace std;

#define RANGE ('z' - 'A')

map<string, int> maps[RANGE];

void add(string s, int val){
	const char *c = s.c_str();
	maps[*c - 'A'].insert( pair<string, int>(s,val) );
}
void search(string s){
	const char *c = s.c_str();
	printf("%d\n", maps[*c - 'A'][s]);
}
int main(){
	add("printf", 5);
	add("search", 27);
	search("printf");
	search("search");
}
