#include <stdio.h>
#include <limits.h>
#include "node.h"

#define TABSZ_MSG "Table size: %lu\n"
#define TOTAL_ENTRIES_MSG "Total entries: %lu\n"
#define LONGEST_MSG "Longest chain: %lu\n"
#define SHORTEST_MSG "Shortest chain: %lu\n"
#define EMPTY_MSG "Empty buckets: %lu\n"
#define TREES_WITHIN_REGION_MSG "Total trees within given region: %lu\n"


void print_info(node **htable, unsigned long tabsz) {
	// TODO: walk down the indices of the htable
	// iterate through each chain and update statistics
	// print out statistics at end
	//
	// NOTE: all your statistics variables should be of type
	// unsigned long
	//
	// NOTE: you may use ULONG_MAX if you want
	// (maximum value for unsigned long int)
	unsigned long entries = 0; 
	unsigned long chain_cnt = 0; 
	unsigned long max = 0; 
	unsigned long min = 0; 
	unsigned long empty_cnt = 0; 	
	unsigned long minCheck = 0; // 1 if empty bucket
	 
	for(unsigned long i = 0; i < tabsz; i++) { 
		chain_cnt = 0; 
		node *node = htable[i]; 
		if(htable[i] == NULL) { 
			empty_cnt++; 
			min = 0; 
			minCheck = 1; 
		} else {  
			while(node != NULL) { 
				entries++; 
				chain_cnt++; 
				node = node->next; 
			}
		       
			if(min == 0 && minCheck != 1) { 
				min = chain_cnt; 
			}

			if(chain_cnt > max) { 
				max = chain_cnt; 
			} 
			if(chain_cnt < min) { 
				min = chain_cnt; 
			} 
		}
	}
	fprintf(stdout, TABSZ_MSG, tabsz); 
	fprintf(stdout, TOTAL_ENTRIES_MSG, entries);  
	fprintf(stdout, LONGEST_MSG, max); 
	fprintf(stdout, SHORTEST_MSG, min); 
	fprintf(stdout, EMPTY_MSG, empty_cnt); 
}
