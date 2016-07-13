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
#include "structs_ga.h"
#include "improvement.h"

int dif_breakpoints(permutation *perm,int pos_i, int pos_j){
	int before = 0, after = 0;

	//pos_i < pos_j
	//number of breakpoints (before)
	if(pos_i == 0){
		if(perm->pi[0] != 1)
			before++;
	}
	else if (abs(perm->pi[pos_i - 1] - perm->pi[pos_i]) > 1)
			before++;

	if (pos_j == perm->length-1){
        if(perm->pi[pos_j] != perm->length)
			before++;
	}
	else if (abs(perm->pi[pos_j] - perm->pi[pos_j + 1]) > 1)
			before++;

	//number of breakpoints (after) - [imagine pos_j is in pos_i]
	if(pos_i == 0){
		if (perm->pi[pos_j] != 1)
			after++;
	}
	else if (abs(perm->pi[pos_i - 1] - perm->pi[pos_j]) > 1)
			after++;

	if (pos_j == perm->length-1){
        if (perm->pi[pos_i] != perm->length)
			after++;
	}
	else if (abs(perm->pi[pos_i] - perm->pi[pos_j + 1]) > 1)
			after++;
	//difference of breakpoints
	return after - before;
}

void apply_reversal(permutation *perm,int pos_i, int pos_j){
	int i;
    //pos_i < pos_j
	//revertir
	int aux;
	for(i=0; i<(pos_j - pos_i + 1)/2; i++){
		aux = perm->pi[pos_i + i];
		perm->pi[pos_i + i] = perm->pi[pos_j - i];
		perm->pi[pos_j - i] = aux;
	}
}
void show_permutation(permutation *perm){
	int i;
	for(i=0; i<perm->length; i++){
		printf("%d,",perm->pi[i]);
	}
	printf("\n");
}

int improve_permutation(permutation *perm){
	float prob;
	int i,j,found;
	int num_reversals = 0;
	
	while(1){
        /* search for a 2-reversal */
		found = 0;
		for(i=0; i<perm->length-1; i++){
			for(j=i+1; j<perm->length; j++){
				if(dif_breakpoints(perm,i,j) == -2){
					prob = ((rand() % 10) + 1) / 10.0;
					if (prob <= 0.5){
						found = 1;
						break;
					}
				}
			}
			if (found) break;
		}
		
		/* apply a 2-reversal if found, and continue searching */
        if (found){
			apply_reversal(perm,i,j);
			//mostrar_permutacion(perm);//debug
			num_reversals++;
		}
		else //if not found stop the search
			break;

	}
    
    rand(); 

	return num_reversals;
}
