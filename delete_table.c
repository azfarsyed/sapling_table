#include <stdlib.h>
#include "node.h"

void delete_table(node **htable, unsigned long tabsz) {
	// TODO: walk through the chains in table
	//
	// TODO: free all the memory associated to each node in each chain
	//
	// TODO: free the entire table

	for(unsigned long i = 0; i < tabsz; i++) { 
		node *curr = htable[i]; 
		while(curr != NULL) { 
			node *prev = curr; 
			curr = curr->next; 
			free(prev->id);
			free(prev); 
		}
	}
	
	free(htable); 
}
