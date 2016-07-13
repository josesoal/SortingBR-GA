/*
 ============================================================================
 Author :
 Jose Luis Soncco-Alvarez and Mauricio Ayala-Rincon
 Group of Theory of Computation
 Universidade de Brasilia (UnB) - Brazil
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "calc_fitness.h"
#include "structs_ga.h"

#include "invdist.h"
#include "structs.h"

int calculate_fitness(chromosome crom, int *num_eval_fit_function){
	int i,buffer;
	struct genome_struct *genome_list;//list of genomes
	int NumGenomes = 2;//number of genomes
	int NumGenes;//number of genes

	/* read number of genes */
	NumGenes = crom.length;
	NumGenes++;//incremet number of genes, to put gene "1" at the beginning

	/* allocate list of genomes */
	genome_list = ( struct genome_struct * ) malloc ( NumGenomes * sizeof ( struct genome_struct ) );

	/* read first genomes */
	genome_list[0].genome_num = 1; //genome id
	genome_list[0].genes = ( int * ) malloc ( NumGenes * sizeof ( int ) );

	genome_list[0].genes[0] = 1;//the first gen is 1
	for(i=1; i<NumGenes; i++){
		buffer = crom.genes[i-1];
		if (buffer >= 1)//if positive increment by one
			genome_list[0].genes[i] = buffer + 1;
		else//if negative decrement by one
			genome_list[0].genes[i] = buffer - 1;
	}

    /* generate second genome (identity) */
	genome_list[1].genome_num = 2; //genome id
	genome_list[1].genes = ( int * ) malloc ( NumGenes * sizeof ( int ) );

	for(i=0; i<NumGenes; i++){
		genome_list[1].genes[i] = i+1;
	}

    /* calculate reversal distance */
	int score = invdist_circular_nomem ( genome_list, genome_list + 1, NumGenes);

    /* increment the number of evaluations of fitness function */
    *num_eval_fit_function = *num_eval_fit_function + 1;
    
    //free memory
	free(genome_list[0].genes);
	free(genome_list[1].genes);
	free(genome_list);

	return score;
}


