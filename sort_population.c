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
#include "sort_population.h"
#include "structs_ga.h"

/*void swap2(population *pob,int i, int j) {
    chromosome chromosomeT;
    chromosomeT = pob->chromosomes[i];
    pob->chromosomes[i] = pob->chromosomes[j];
    pob->chromosomes[j] = chromosomeT;
}

int partition(population *pob, int left, int right) {
    int i, j;

    i = left;
    for (j = left + 1; j <= right; ++j) {
        if (pob->chromosomes[j].fitness < pob->chromosomes[left].fitness) {
            ++i;
            swap2(pob,i,j);
        }
    }
    swap2(pob,left,i);

    return i;
}

void quickSort(population *pob, int left, int right) {
    int r;

    if (right > left) {
        r = partition(pob, left, right);
        quickSort(pob, left, r - 1);
        quickSort(pob, r + 1, right);
    }
}*/

void countingSort(population *pob, int k){
	int i,j;
	int *c;//c[k];
	chromosome *a;
    
    /* allocate memory for c[k] */
    c = malloc(k*sizeof(int));

	/* allocate memory for temporary population "a" */
	a = malloc(pob->population_size*sizeof(chromosome));
	if (a == NULL) printf("a NULL in countingSort() of ordenar_pob.c \n");
    
    for(i=0;i<pob->population_size;i++){
        a[i].genes = malloc(pob->chromosomes[0].length * sizeof(int));//allocate memory for chromosome "i"
        if (a[i].genes == NULL) 
            printf("a[i].genes NULL in countingSort() of ordenar_pob.c \n");
    }
    
    /* make a copy of population */
	for(i=0; i<pob->population_size; i++){
		a[i].fitness = pob->chromosomes[i].fitness;
        for(j=0; j<pob->chromosomes[0].length; j++)
            a[i].genes[j] = pob->chromosomes[i].genes[j]; 
	}

	/*counting sort*/
	for(i=0; i<k; i++){
		c[i] = 0;
	}

	for(i=0; i<pob->population_size; i++){
		c[a[i].fitness] = c[a[i].fitness] + 1;
	}

	for(i=1; i<k; i++){
		c[i] = c[i] + c[i-1];
	}

	for(i=pob->population_size-1; i>=0; i--){
		//copy into population
        pob->chromosomes[c[a[i].fitness]-1].fitness = a[i].fitness;
        for(j=0; j<pob->chromosomes[0].length; j++)
            pob->chromosomes[c[a[i].fitness]-1].genes[j] = a[i].genes[j];
        
        
		c[a[i].fitness] = c[a[i].fitness] - 1;
	}
    
    
    /* free memory */
    for(i=0;i<pob->population_size;i++){
        free(a[i].genes);
    }
	free(a);
    free(c);
}


