#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avltree.h"
#include "avltree.c"


int main(int argc,char *argv[]){
	
	int command;
	Tree t = NULL;
	
	t = readData(parseInput(argc,argv));
	
	
	if(t!=NULL){
		printf(">>>Welcome to Photo Indexing<<<\n");
		do{
			printf("-----------------------------------------------------------------------------\n");
			printf("-Menu-\n");
			printf("1. Display the full index of photos\n");
			printf("2. Display the photos of popular country\n");
			printf("3. Display the photos of popular year\n");
			printf("4. Exit\n\n");
			printf("Option : ");
			scanf("%d",&command);
			
			if(command == 1){
				printf("Photo Index:\n");
				displayIndex(t);
			}
			else if(command == 2){
				printf("Photos of popular country:\n");
				popularCountry(t);
			}
			else if(command == 3){
				printf("Photos of popular year:\n");
				popularYear(t);
			}
			else if(command == 4){
				free(t);
				break;
			}
			else{
				printf("Enter true command!!\n\n");
			}
			
		}while(1);
	}
	
	
	return 0;
}
