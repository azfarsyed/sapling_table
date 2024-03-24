#include <stdlib.h>
#include <string.h>
#include "node.h"

node *insert_node(node *front, char* id, double x, double y) {
	
	// links the new node into the chain 
	node *newNode = malloc(sizeof(node)); 	
	if(newNode == NULL) {
	       return NULL; 
	} else { 
 		newNode->id = malloc((strlen(id)+1) * sizeof(char)); 
		strcpy(newNode->id, id); 
		newNode->xcoord = x; 
		newNode->ycoord = y; 
		newNode->next = front; 
		return newNode;
	}		
	
}
