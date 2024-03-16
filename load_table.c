#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

#define MAX_LINELEN 100 
#define FILE_OPEN_ERR_MSG "error in load_table while opening file %s\n"
#define DUPLICATE_ID_MSG "load_table duplicate entry: %s\n"
#define INSERTION_ERROR_MSG "load_table could not create node for %s\n"

int load_table(node **htable, unsigned long int tabsz, char *filename) {
	FILE *fp = NULL;
	// TODO: open the file and check that it was successful
	if((fp = fopen(filename, "r")) == NULL) { 
		fprintf(stderr, FILE_OPEN_ERR_MSG, filename); 
		return -1; 
	}
	// TODO: loop through the file and read one line at a time using fgets
	// see manual page for fgets for information on parameters
	char buf[MAX_LINELEN + 1]; // input buffer for fgets
	while (fgets(buf, MAX_LINELEN + 1, fp) == buf) {
		// TODO: for each line, use strtok to break it into columns
		// (convert the second and third columns to doubles)
		char *id = strtok(buf, ","); 
		char *x = strtok(NULL, ","); 
		char *y = strtok(NULL, ","); 

		double xstr = atof(x); 
		double ystr = atof(y); 
		unsigned int index = hash(id) % tabsz; 
		
		// if duplicate
		if(node_lookup(htable[index], id) != NULL) { 
		       	fprintf(stderr, DUPLICATE_ID_MSG, id); 
			continue; 	
		} else { 
			//if insert node doesnt works
			node *f = insert_node(htable[index], id, xstr, ystr); 
			if(f == NULL) { 
				fprintf(stderr, INSERTION_ERROR_MSG, id); 
				fclose(fp); 
				return -1; 
			} else { 
				htable[index] = f; 
			}
		}
	}
	fclose(fp); 
	return 0; 	
}
