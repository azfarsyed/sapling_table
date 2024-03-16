#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "node.h"

#define MIN_TAB_SZ 3
#define DEFAULT_TAB_SZ 1873
#define QUERY_SUCCESS_FORMAT "found tree id=%s, x=%.5f, y=%.5f\n" 
#define QUERY_FAILURE_FORMAT "could not find tree with id=%s\n"

int main(int argc, char **argv) {
	int s_flag = 0;
	unsigned long tabsz = DEFAULT_TAB_SZ;
	// TODO: parse opts with getopt and initialize these variables 
	// (see strtoul for parsing unsigned long)
	int c; 

//	char *filename = argv[1];
	 
	while((c = getopt(argc, argv, "st:")) != -1) { 
		switch (c) { 
		
		case 's' : 
			s_flag = 1; 
			break; 
		case 't': 
			tabsz = atof(optarg); 
			if(tabsz < MIN_TAB_SZ) {
				tabsz = DEFAULT_TAB_SZ; 
			}
			break; 
		default: 
			abort(); 
		}
	}
//	printf("%d", s_flag); 

	char *filename = argv[optind]; 
	// TODO: initialze htable
	// using calloc so all buckets are initialized to NULL
	node **htable = calloc(tabsz, sizeof(node));
	if (htable == NULL) {
		return EXIT_FAILURE;
	}
	
	// TODO: get filename and call load_table; 

	if (load_table(htable, tabsz, filename) == -1) {
		fprintf(stderr, "error in load_table\n");
		free(htable);
		return EXIT_FAILURE;
	}
	
	size_t bufsz = 0;
	char *buf = NULL; 
	
	// read one line at a time from stdin, do a lookup for that id
	// 
	int queries = 0; 
	ssize_t bytes;
	while ((bytes = getline(&buf, &bufsz, stdin)) > 0) {
		// replace the \n, if it exists (for hashing)
		if (buf[bytes - 1] == '\n') buf[bytes - 1] = '\0';
		
		
		unsigned long index = hash(buf) % tabsz;

		node *front = htable[index]; 
		node *curr = node_lookup(front, buf); 

		if(curr != NULL) { 
			fprintf(stdout, QUERY_SUCCESS_FORMAT, buf, curr->xcoord, curr->ycoord);	
			queries++; 
		} else { 
			fprintf(stdout, "could not find tree with id=%s\n", buf); 
		}
		
	}
	printf("%d successful queries\n", queries);
	// if -s called then print stats
	
	if (s_flag == 1) {
		print_info(htable, tabsz); 
	}

	// TODO: free all allocated memory associated with the table 
	// using delete_table()
	//
	delete_table(htable, tabsz); 
	free(buf);  // free the buffer allocated by getline()

	return EXIT_SUCCESS;
}



