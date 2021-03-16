

void displayIndex(Tree t)   /* Fist displaying photo infos in treenode and then if tree->next is not null, the function displays those photos too. */
{
	if(t==NULL)
    	return;
    displayIndex(t->left);    
    printf("%s,",t->Name);
    printf("%s,",t->Dimension);
    printf("%s,",t->Size);
    printf("%s,",t->City);
    printf("%s,",t->Country);
    printf("%d\n\n",t->Year);
    
    if(t->next != NULL){
    	struct node *iter;
    	for(iter = t->next;iter != NULL;iter=iter->next){
    		printf("%s,",iter->Name);
 	 	  	printf("%s,",iter->Dimension);
  			printf("%s,",iter->Size);
		    printf("%s,",iter->City);
		    printf("%s,",iter->Country);
		    printf("%d\n\n",iter->Year);
		}
	}
    displayIndex(t->right);  
}


int TreeHeight(Tree t){   /* Height function cant satisfy t = NULL condition. With TreeHeight function, I solved that problem. */

	if (t != NULL){
		return Height(t)+1;
	}
	else{
		return 0;
	}
}


int Height(Tree t){
	
	int lefth =0 ,righth =0;
	if (t!=NULL){
		righth = Height(t->right);
		lefth = Height(t->left);
		
		if(righth >= lefth){
			return righth+1;
		}
		else{
			return lefth+1;
		}
	}	
	else{
		return -1;
	}
}


int IsAvlTree(Tree t){    /* 1 AVL Tree, 0 Not AVL Tree (Checks all the nodes iteratively)  */
	
	Stack s = (Stack)malloc(sizeof(Stack));
	Tree temp = NULL;
	if(s == NULL){
		printf("Out of memory space!!\n");
	}

	s->bottom = NULL;
	s->top = NULL;

	while(t != NULL){
		push(t,s);
		t = t->left;
	}
	
	int count = 0;  /* For detecting not AVL tree */
	 
	while(1){
		temp = pop(s);
		if(abs(temp->balancefactor) > 1){
			count++;
		}
		t = temp->right;
		while(t != NULL){
			push(t,s);
			t = t->left;
		}
		if(t == NULL && s->top->next == NULL){
			break;
		}
	}
	if(count == 0){
		free(s);
		return 1;
	}	
	else{
		free(s);
		return 0;
	}
}


Tree FindUnbalancedTree(Tree t){   /* Finding unbalanced tree. Checks all the tree nodes with post order iteration. If the tree's Balancefactor bigger than 1, 
									  function returns this tree and then I will make it balanced with rotations.*/ 

	Stack s1 = (Stack)malloc(sizeof(Stack));
	if(s1 == NULL){
		printf("Out of memory space!!\n");
	}
	s1->top = NULL;
	s1->bottom = NULL;
	s1->size = 0;
	Stack s2 = (Stack)malloc(sizeof(Stack));
	if(s2 == NULL){
		printf("Out of memory space!!\n");
	}
	s2->top = NULL;
	s2->bottom = NULL;
	s2->size = 0;
	Tree temp = NULL;
	
	if(t == NULL){
		free(s1);
		free(s2);
		return;
	}
	
	push(t,s1);
	
	while(s1->top->next != NULL){
		temp = pop(s1);
		push(temp,s2);
		if(temp->left != NULL){
			push(temp->left,s1);
		}
		if(temp->right != NULL){
			push(temp->right,s1);
		}
	}
	
	while(s2->top->next != NULL){
		temp = pop(s2);
		if(abs(temp->balancefactor) > 1){
			free(s1);
			free(s2);
			return temp;
		}
	}
	free(s1);
	free(s2);	
}


void BalanceFactorCalculator(Tree t){   /* goes treenode to treenode, calculates balance factor and gives all the treenodes' balancefactor numbers.  */

   if(t==NULL)
    	return;
   BalanceFactorCalculator(t->left);    
   t->balancefactor = TreeHeight(t->left) - TreeHeight(t->right);
   BalanceFactorCalculator(t->right);

}


Tree pop(Stack temp){
	struct stacknode *iter;
	if(temp->top->next == NULL){
		printf("Stack is empty!\n");
	}
	else{
		
		iter = temp->top->next;
		Tree value = iter->data;
		temp->top->next = temp->top->next->next;
		temp->size--;
		free(iter);
		
		return value;
	}
}


void push(Tree t,Stack temp){
	
	if(temp->top == NULL){
		temp->top = (struct stacknode *)malloc(sizeof(struct stacknode));
		if(temp->top == NULL){
			printf("Out of memory space!\n");
		}
		
		temp->top->next = (struct stacknode *)malloc(sizeof(struct stacknode));
		if(temp->top->next == NULL){
			printf("Out of memory space!\n");
		}
		
		temp->top->next->data = t;
		temp->top->next->next = NULL;
		temp->size++;

	}
	else{
		struct stacknode *n = (struct stacknode *)malloc(sizeof(struct stacknode));
		if(n==NULL){
			printf("Out of memory space!\n");
		}
		
		n->data = t;
		n->next = temp->top->next;
		temp->top->next = n;
		temp->size++;
		
	}
}


Tree CopyTree(Tree t){   /* Fist copies the photo information in treenode and if tree->next is not null, copies the photos which have the same country name. */
	
	if(t != NULL){
		Tree node = (Tree)malloc(sizeof(struct TreeNode));
		strcpy(node->Name,t->Name);
		strcpy(node->Dimension,t->Dimension);
		strcpy(node->Size,t->Size);
		strcpy(node->City,t->City);
		strcpy(node->Country,t->Country);
	    node->Year = t->Year;
	    if(t->next != NULL){     /* for copying t->next side (The nodes that have the same country name) */
	    
	    	node->next = (struct node*)malloc(sizeof(struct node));
		  	strcpy(node->next->Name,t->next->Name);
		  	strcpy(node->next->Dimension,t->next->Dimension);
		  	strcpy(node->next->Size,t->next->Size);
			strcpy(node->next->City,t->next->City);
			strcpy(node->next->Country,t->next->Country);
		   	node->next->Year = t->next->Year;
			struct node *itert = t->next->next;
	    	struct node *iternode = node->next;
	    	iternode->next = NULL;
	    	while(itert != NULL){
				struct node *ins = (struct node*)malloc(sizeof(struct node));
				strcpy(ins->Name,itert->Name);
		    	strcpy(ins->Dimension,itert->Dimension);
		    	strcpy(ins->Size,itert->Size);
				strcpy(ins->City,itert->City);
				strcpy(ins->Country,itert->Country);
		   		ins->Year = itert->Year;
		   		iternode->next = ins;
		   		ins->next = NULL;
		   		itert = itert->next;
		   		iternode = iternode->next;		
			}
			
		}
			
		else{
			node->next = NULL;
		}
		node->right = CopyTree(t->right);
		node->left = CopyTree(t->left);	
		return node;
	}
	
	else{
		return NULL;
	}
}


Tree LeftRotate(Tree t){
	
	if(t->right->left != NULL){
		
		Tree r = CopyTree(t->right);
		t->right = NULL;
		Tree trightleft = CopyTree(r->left);
		r->left = NULL;
		r->left = t;
		t->right = trightleft;
		
		return r;
	}
	else{
		Tree r = CopyTree(t->right);
		t->right = NULL;
		r->left = t;
		
		return r;
	}
}

	
Tree RightRotate(Tree t){
	
	if(t->left->right != NULL){
		
		Tree l = CopyTree(t->left);
		t->left = NULL;
		Tree leftright = CopyTree(l->right);
		l->right = NULL;
		l->right = t;
		t->left = leftright;
		
		return l;
	}
	else{
		Tree l = CopyTree(t->left);
		t->left = NULL;
		l->right = t;
		
		return l;
	}
	
}

	
Tree LeftRight(Tree t){
	
	Tree left = CopyTree(t->left);
	left = LeftRotate(left);
	t->left = left;
	t = RightRotate(t);
	
	return t;
}


Tree RightLeft(Tree t){
	
	Tree right = CopyTree(t->right);
	right = RightRotate(right);
	t->right = right;
	t = LeftRotate(t);
	
	return t;	
}


Tree InsertTree(Tree insert, Tree t,char country[20]){    /* I am using it while inserting operation to avl tree. I find unbalanced tree with FindUnbalancedTree function. Then I am making it balanced with rotation operations.*/
	if(insert == NULL){                                      /*then I am inserting the balanced tree back to the main tree with this function (InsertTree). I am using country name for finding the insertion location. */
	}
	else if(t == NULL){
		t = insert;
	}
	else{
		Tree iter = t;
		Tree back = t;
		
		while(iter != NULL){
			if(strcasecmp(country,iter->Country) > 0){
				iter = iter->right;
				if(strcasecmp(country,iter->Country) != 0){
					back = back->right;
				}
			}
			else if(strcasecmp(country,iter->Country) < 0){
				iter = iter->left;
				if(strcasecmp(country,iter->Country) != 0){
					back = back->left;
				}
			}
			else if(strcasecmp(country,iter->Country) == 0){
				if(strcasecmp(country,back->Country) > 0){
					back->right = insert;
					return t;
				}
				else if(strcasecmp(country,back->Country) < 0){
					back->left = insert;
					return t;
				}
				else{               /* if Tree t has 3 node and back and iter is on the same node */
					t = insert;
					return t;
				}

			}
		}
	}
		
	return t;
}


Tree  insertPhoto(Tree t,struct node *n){   /* Inserts photos to AVL Tree */

	char tempcountry[20];
	
	t = IterativeInsertBinarySearchTree(t,n);    /* First adding BSt  */
	
	BalanceFactorCalculator(t);   /* Calculates all the nodes balance factor number */
	

	while(IsAvlTree(t) ==0){    /* Loop is continuing while all the treenodes are balanced */
		
		Tree temp = FindUnbalancedTree(t);               /* temp is the unbalanced node */
		
		strcpy(tempcountry,temp->Country);             /* I will use the tempcountry string to find the location in InsertTree */

		if(temp->balancefactor > 1){            /* The rotations make the tree balanced and I am Inserting the balanced tree to same location in the main tree. */
	
			if(strcasecmp(n->Country,temp->left->Country) < 0){   // LL
			
				temp = RightRotate(temp);
				t = InsertTree(temp,t,tempcountry);
				BalanceFactorCalculator(t);


			}
			else if(strcasecmp(n->Country,temp->left->Country) > 0){  //LR

				temp->left = LeftRotate(temp->left);
				t = InsertTree(temp,t,tempcountry);
				temp = RightRotate(temp);
				t = InsertTree(temp,t,tempcountry);
				BalanceFactorCalculator(t);
				


			}
		}
		else if(temp->balancefactor < -1){  
			if(strcasecmp(n->Country,temp->right->Country) > 0){   // RR

				temp = LeftRotate(temp);
				t = InsertTree(temp,t,tempcountry);
				BalanceFactorCalculator(t);


	
			}
			else if(strcasecmp(n->Country,temp->right->Country) < 0){   // RL

				temp->right = RightRotate(temp->right);
				t = InsertTree(temp,t,tempcountry);;
				temp = LeftRotate(temp);
				t = InsertTree(temp,t,tempcountry);
				BalanceFactorCalculator(t);
			}
		}
	}
	
	return t;
}


Tree IterativeInsertBinarySearchTree(Tree t,struct node *x){      /* Iteratively inserting operation to binary search tree */
	Tree iter,back;
	iter = back = t;
	
	if(t == NULL){
		t = (Tree)malloc(sizeof(struct TreeNode));
		if(t == NULL){
			printf("Out of memory space!!\n");
		}
		strcpy(t->Name,x->Name);
		strcpy(t->Dimension,x->Dimension);
		strcpy(t->Size,x->Size);
		strcpy(t->City,x->City);
		strcpy(t->Country,x->Country);
	    t->Year = x->Year;
		t->left = NULL;
	    t->right = NULL;
	    t->next = NULL;
	}
	else{
		while(iter != NULL){
			if(strcasecmp(x->Country,iter->Country) > 0){     /* Checking countries to find the proper inserting loaction */

				iter = iter->right;
				if(iter != NULL){
					back = back->right;
				}
			}
			else if(strcasecmp(x->Country,iter->Country) < 0){  

				iter = iter->left;
				if(iter != NULL){
					back = back->left;
				}
			}
			else if(strcasecmp(x->Country,iter->Country) == 0){
				
				if(iter->next == NULL){
					iter->next = x;	
					x->next = NULL;
					
				}
				
				else{
					
					struct node *findplace = iter->next;    /* if country of photo to be inserted already exists in the main tree, I am inserting the node to next of the treenode. */
					while(findplace->next != NULL){           /* I am making linked list in the treenode->next which includes the photos which have the same country */
					findplace = findplace->next;
					}
				    findplace->next = x;
				    x->next = NULL;
				    
				}
				
				return t;
			}	
		}
		

		Tree insert = (Tree)malloc(sizeof(struct TreeNode));    /* If country of photo to be inserted not exists in the tree, then the photo is storing in a new treenode.  */
		if(insert == NULL){
				printf("Out of memory space!!\n");
		}
		strcpy(insert->Name,x->Name);
		strcpy(insert->Dimension,x->Dimension);
		strcpy(insert->Size,x->Size);
		strcpy(insert->City,x->City);
		strcpy(insert->Country,x->Country);
	    insert->Year = x->Year;
		insert->left = NULL;
	    insert->right = NULL;
	    insert->next = NULL;
			
		if(strcasecmp(x->Country,back->Country) > 0){
			back->right = insert;
		}
		else if(strcasecmp(x->Country,back->Country) < 0){
			back->left = insert;
			
		}
	}
		
	
	return t;
} 


Tree readData(char filename[20]){     /* Reads the file and add the infos to AVL Tree  */
	
	Tree temp = NULL;
	struct node *insert;
		
	FILE *ffile;
	char str[100];
	char line[100];
	char *piece;
	ffile = fopen(filename,"r");
	int i = 0;
 
	while(1){
		
		if(fgets(str,sizeof(str),ffile) == NULL){
			break;
		}
		
		else{
			insert = (struct node*)malloc(sizeof(struct node));
			if(insert == NULL){
				printf("Out of memory space!!\n");
			}
			insert->next = NULL;
			
			strcpy(line,strtok(str,","));
			strcpy(insert->Name,line);
			        
			i=0;
			while(1){
				if(i==0){
				piece = strtok(NULL, ",");
				strcpy(insert->Dimension,piece);
					if(piece == NULL){
						break;
				}	}
				
				else if(i==1){
				piece = strtok(NULL, ",");
				strcpy(insert->Size,piece);
					if(piece == NULL){
						break;
				}}	
				
				else if(i==2){
				piece = strtok(NULL, ",");
				strcpy(insert->City,piece);
					if(piece == NULL){
						break;
				}}	
				
				else if(i==3){
				piece = strtok(NULL, ",");
				strcpy(insert->Country,piece);
					if(piece == NULL){
						break;
				}}	
				
				else if(i==4){
				piece = strtok(NULL, ",");
				insert->Year = atoi(piece);
					if(piece == NULL){
						break;
				}}
							
				else break;
				
			i++;
			}
				
			temp = insertPhoto(temp,insert);    /* I will hold all the infos of one photo in temp node and insert it to the AVL tree. The loop keeps doing it until file become empty.  */
			
		}	
	}
	
	fclose(ffile);

	return temp;
	
}


Tree FindMaXPopularCountry(Tree t,char maxcountryname[20]){    /* Takes the tree and the countryname which has the most number of photos among the countries, finds and returns the treenode which has this countryname.  */
  
    Stack s = (Stack)malloc(sizeof(Stack));
    if(s == NULL){
		printf("Out of memory space!!\n");
	}
	
	Tree temp = NULL;
	s->bottom = NULL;
	s->top = NULL;
	
	while(t != NULL){
		push(t,s);
		t = t->left;
	}

	while(1){
		temp = pop(s);
		if(strcasecmp(maxcountryname,temp->Country) == 0){   
			free(s);
			return temp;
		}
		t = temp->right;
		while(t != NULL){
			push(t,s);
			t = t->left;
		}
		if(t == NULL && s->top->next == NULL){
			free(s);
			break;
		}
	}
}


void popularCountry(Tree t){                               /*  First, I detect the country that have the most number of photos with traversing all the nodes and counting photos sequentially (O(n^2)).Then I search the treenode which 
                                                              has the most number of photos with sequential search O(n). Then I am printing the photo which is in treenode, after that, 
															  I am printing the photos in the linked list (treenode->next, (which have the same countryname) with traversing sequentially. O(n) 
															  So in total : O(n^2) 
															  On the other hand I can find the popular country with making new thing like treenode->countrynum in the struct treenode and add 1 to it 
															  after each insertion to the same node. So that I wouldn't have to traverse and count the number of photos of each node to detect the popular country.
															  With this way, I could decrease the complexity to O(n) */
	Stack s = (Stack)malloc(sizeof(Stack));                       
	Tree temp = NULL;
	int maxcountrynum = 0;
	char maxcountryname[25];
	
	Tree copyt = CopyTree(t);   /* t is not usable after the following stack operations. With copying t, I can use the tree t after the stack operation  */
	
	if(s == NULL){
		printf("Out of memory space!!\n");
	}
	s->bottom = NULL;
	s->top = NULL;
	
	while(t != NULL){
		push(t,s);
		t = t->left;
	}

	while(1){
		temp = pop(s);
		if(temp->next != NULL){

			int i = 0;
			struct node *iter0;
			for(iter0=temp->next;iter0!=NULL;iter0=iter0->next){
				i++;
			}
			if(i > maxcountrynum){                                       /* Finding the popular country */
				maxcountrynum = i;
				strcpy(maxcountryname,temp->Country);
			}
		}
		t = temp->right;
		while(t != NULL){
			push(t,s);
			t = t->left;
		}
		if(t == NULL && s->top->next == NULL){
			break;
		}
	}
	
	Tree maxtreenode = FindMaXPopularCountry(copyt,maxcountryname);     /* getting the treenode which has the popular country  */
	
	struct node *photo = maxtreenode->next;

	printf("%s,",maxtreenode->Name);                     /* printing the information of the photos in this node */
	printf("%s,",maxtreenode->Dimension);
	printf("%s,",maxtreenode->Size);
	printf("%s,",maxtreenode->City);
	printf("%s,",maxtreenode->Country);
	printf("%d\n\n",maxtreenode->Year);

	while(photo != NULL){
		
		printf("%s,",photo->Name);
	    printf("%s,",photo->Dimension);
	    printf("%s,",photo->Size);
	    printf("%s,",photo->City);
	    printf("%s,",photo->Country);
	    printf("%d\n\n",photo->Year);
		photo = photo->next;
	}
	
	free(s);
	free(copyt);
}


void popularYear(Tree t){             /*   First, I traverse all the treenodes and trenode->next linked lists if not NULL and add the yearnodes to the years linked list.
										   I treaverse all Treenodes, linked lists inside the treenode->next, and years linked list for inserting the years sequentially.
										   So the complexity is O(n^3). I can improve this by converting the years linked list to priority queue. So, I can find the insertion location
										   with Binary search instead of sequential search. It will decrease the complexity of time from O(n) to O(log(n)).
										   So, the new time complexity would be O(n^2.log(n))  */
	
	List years = (List)malloc(sizeof(List));     /* I am making linked list for the years, I will make nodes for each year and I will store the photo numbers inside of it. */
	if(years == NULL){
		printf("Out of memory space!!\n");
	}
	years->head = (struct yearnode *)malloc(sizeof(struct yearnode));
	if(years->head == NULL){
		printf("Out of memory space!!\n");
	}
	years->head->next = NULL;
	years->tail = years->head;
	years->size = 0;
	Tree tcopy = CopyTree(t);    /* t is not usable after the following stack operations. With copying t, I can use the tree t after the stack operation  */
	
	Stack s = (Stack)malloc(sizeof(Stack));   
	if(s == NULL){
		printf("Out of memory space!!\n");
	}
	
	Tree temp = NULL;
	s->bottom = NULL;
	s->top = NULL;
	
	while(t != NULL){
		push(t,s);
		t = t->left;

	}
	
	while(1){                                       /* first the fuction checks if the year of the photo exists in the linked list or not. If exists its just incrementing the year->numberofphoto.  */
		temp = pop(s);                                /* If the year of the photo not exits in the linked list, program creates a new node for this year and make year->numberofphoto = 1.  */
		if(years->head->next == NULL){
			years->head->next = (struct yearnode *)malloc(sizeof(struct yearnode));
			if(years->head->next == NULL){            
				printf("Out of memory space!!\n");
			}
			years->head->next->numberofphoto = 1;
			years->head->next->year = temp->Year;
			years->tail = years->head->next;
			years->tail->next = NULL;
			years->size++;	
		}
		int c;                           
	
		if(temp->next != NULL){              /* For the infos in the treenode->next linked list  */
			struct node *iter0;
			for(iter0=temp->next;iter0!=NULL;iter0=iter0->next){
				struct yearnode *iter1;
				c =0;
				for(iter1=years->head->next;iter1!=NULL;iter1=iter1->next){
					if(iter1->year == iter0->Year){
						iter1->numberofphoto++;
						break;
					}
					else{
						c++;
					}		
				}
				if(c == years->size){
						years->tail->next = (struct yearnode *)malloc(sizeof(struct yearnode));
						if(years->tail->next == NULL){
							printf("Out of memory space!!\n");
						}
						years->tail->next->year = iter0->Year;
						years->tail->next->numberofphoto = 1;
						years->size ++ ;
						years->tail = years->tail->next;
						years->tail->next = NULL;
					}
			}
		}
		
		if(years->head->next != NULL){            
			struct yearnode *iter;
			c =0;
			for(iter=years->head->next;iter!=NULL;iter=iter->next){
				if(iter->year == temp->Year){
					iter->numberofphoto++;
					break;
				}
				else{
					c++;
				}
			}
			if(c == years->size){
				years->tail->next = (struct yearnode *)malloc(sizeof(struct yearnode));
				if(years->tail->next == NULL){
					printf("Out of memory space!!\n");
				}		
				years->tail->next->year = temp->Year;
				years->tail->next->numberofphoto = 1;
				years->size ++ ;
				years->tail = years->tail->next;
				years->tail->next = NULL;
			}
		}
		
		t = temp->right;
		while(t != NULL){
			push(t,s);
			t = t->left;
		}
		if(t == NULL && s->top->next == NULL){
			break;
		}
	}
	
	struct yearnode *maxyearnode;
	int maxyear = 0;
	int photonum = 0;
	for(maxyearnode = years->head->next;maxyearnode!=NULL;maxyearnode=maxyearnode->next){    /* For detecting the year which has the maximum number of photos  */
		if(photonum < maxyearnode->numberofphoto){
			photonum = maxyearnode->numberofphoto;
			maxyear = maxyearnode->year;
		}
	}
	
	displayMaxYearPhotos(tcopy,maxyear);
	
	free(s);
	free(years);
	free(tcopy);
}


void displayMaxYearPhotos(Tree t,int year){
	if(t==NULL)
    	return;
    displayMaxYearPhotos(t->left,year); 
    if(t->Year == year){
    	
    	printf("%s,",t->Name);
 	 	printf("%s,",t->Dimension);
  		printf("%s,",t->Size);
		printf("%s,",t->City);
		printf("%s,",t->Country);
		printf("%d\n\n",t->Year);	
	}
	struct node *iter;
	for(iter = t->next;iter!=NULL;iter=iter->next){
		if(iter->Year == year){
			printf("%s,",iter->Name);
	 	 	printf("%s,",iter->Dimension);
	  		printf("%s,",iter->Size);
			printf("%s,",iter->City);
			printf("%s,",iter->Country);
			printf("%d\n\n",iter->Year);
		}
	}
    displayMaxYearPhotos(t->right,year);
	 
}


char *parseInput(int argc,char *argv[]){   /* For getting the input from command prompt  */
	
	if(argc == 2 ) {
    	return argv[1];
   }
   else if( argc > 2 ) {
    	printf("Too many arguments supplied.\n");
   }
   else {
    	printf("Please provide command line argumands\n ");
   }
}
