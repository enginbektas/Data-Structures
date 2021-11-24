/*Data Structures Term Project #1*/
/*Author: Engin Bektas*/
/*This program basically constructs a Binary Search Tree from the input
in alphabetic manner and a Binary Tree such that in the form of having 
the most efficient way to give result of the minimum possible total access time.*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


Node  * getNewNode(char * w[], long freq) { // allocates memory and creates a new Node  node and returns it
	Node  * newNode = (Node  * )malloc(sizeof(Node ));
	strcpy(newNode->word, w);
	newNode->frequency = freq;
	newNode->left = newNode->right = NULL;
	return newNode;
}
Node  * insert (Node  * root, char w[], long freq) {//inserts node to Node  tree
	if(root == NULL)  //if empty
		root = getNewNode(w, freq);
	else if (strcmp(root->word, w) > 0) //compare keys and decide to go whether left or right
		root->left = insert(root->left, w, freq);
	else
		root->right = insert(root->right, w, freq);
	return root;
}
bool search(Node  * root, char x[]) { // returns true if the given word exists in the tree
	if (root == NULL) return false;
	else if (strcmp(root->word, x) == 0) return true;
	else if(strcmp(x, root->word)) return search(root->left, x);
	else return search(root->right, x);
}
int getTotalAccessTime(Node  * node, int i, bool isFirst, int * tat) { // takes root node and initially i=0. i holds the current depth. returns true if the given word exists in the tree
	if(node == NULL)	//tat = totalAccessTime
        return tat;
    if(isFirst){ //reset tat if it is the very beginning of the function
        *tat = 0;
        isFirst = false;
    }
    i++; // i holds the depth of the spesific node
    *tat += i * node->frequency;
    getTotalAccessTime(node->left, i, isFirst, tat);
    getTotalAccessTime(node->right, i, isFirst, tat);
    return;
}
int treeToArray(Node  * node, Node  * nodes[], int index) {//Adds given node to given array starting from the i'th element.
    if (node == NULL)
        return index;
        nodes[index] = node;
        index++;
        index = treeToArray(node->left, nodes, index);
        index = treeToArray(node->right, nodes, index);
        return index;
}
void printTree(Node  * node, bool flag) {//Adds given node to given array starting from the i'th element.
    if(node == NULL)
        return;
    while (flag) {
        printf("%s\n","Printing in in-order fashion:");
        flag = false;
    }

        
    printTree(node->left, flag);
    printf("%-10s %d\n", node->word, node->frequency);
    printTree(node->right, flag);
}
int sizeOfTree(Node  * node) {  //returns the number of the nodes in the given tree
    int c = 1;
    if (node == NULL)
        return 0;
    else {
        c += sizeOfTree(node->left);
        c += sizeOfTree(node->right);
        return c;
     }
}
void bubbleSort(Node  * arr[], int size) { //sorts given struct pointer array
    int i, j;
    for (i = 0; i < size-1; i++) {
        //printf("%s %d\n", arr[i].word, arr[i].frequency);
        for( j=0; j < size-i-1; j++) {
            if (arr[j]->frequency < arr[j+1]->frequency) {
                nodeSwap(arr[j], arr[j+1]);
            }
        }
    }
}
void nodeSwap(Node  * a, Node  * b){ //swaps nodes
    Node  temp = *a;
    *a = *b;
    *b = temp;
}
Node  * createLevelOrderTree(Node  * arr[], Node  * root, int i, int n) { //creates a tree in depth traversal fashion
    if ( i == n )                                 //with array implemengetTotalAccessTimeion of trees
    return root;
    if (i < n) {
        Node  * temp = getNewNode(arr[i]->word, arr[i]->frequency);
            root = temp;
        root->left = createLevelOrderTree(arr, root->left, 2 * i + 1, n);
        root->right = createLevelOrderTree(arr, root->right, 2 * i + 2, n);
    }
    return root;
}
Node  * createTree(char file[]){ //reads the input, parses it, creates nodes and assign values to it
    Node  * node = NULL;                                  //finally returns the root of the tree
    Node  * node2 = NULL; //creating empty tree
    FILE * input;
    int frequency = 0; //holds the frequency to be assigned to each node
    int number = 0; //keeps track of number'th element of the input
    char word[30]; //holds the word to be assigned to each node
    char line[30]; //one line from the input
    char delim[] = ","; //input tokenizer
    int i; //loop counter
	int j;
    if((input = fopen(file, "r")) == NULL) {//opening and checking file
        puts("File could not be opened");
    }
        else
        { //Reading of the input and ceating of the Node  tree in alphabetic order
            //
            // CREATING OF Node
            //
            while(!feof(input))	{//reads from the file, obtains number, word, and frequency, assigns them to the tree.
                char * charPtr;
                fgets(line, 30, input);
                
                for(i=0; i<3; i++) {
                    if (i==0) { // for the first tokenizing, process the number
                        charPtr = strtok(line, delim);
                        number = atoi(charPtr); //parse string to int
                    } if (i==1) {
                        strcpy(word, strtok(NULL,delim)); // for the second tokenizing, process the word
                        for(j = 0; j<30; j++){ // convert word to lower case
                            word[j] = tolower(word[j]);
                        }
                    } if (i==2) {
                        charPtr = strtok(NULL, delim); // for the third tokenizing, process the frequency
                        frequency = atoi(charPtr); //parse string to int
                    }
                }
            node = insert(node, word, frequency);
            }
        }
    return node;
}
main() {
    Node  * node = NULL; //node holds the root of Binary Search Tree
    Node  * node2 = NULL; //node2 holds the root of Binary Tree that is arranged for the most efficient

	int totalAccessTime = 0;
    char input[30] = "input.txt";                   
    node = createTree(input); //this function reads input and returns a tree root node
    int size = sizeOfTree(node); //holds the node number
    printTree(node, true); //prints
    getTotalAccessTime(node, 0, true, &totalAccessTime); //updates totalAccessTime
    printf("Total access time of the first binary search tree: %d\n", totalAccessTime);
    puts("");

    Node  * arr[size]; //initialize array
    treeToArray(node, arr, 0); //to store the nodes temporarily
    bubbleSort(arr, size); //sorts the array by frequencies
    
    node2 = createLevelOrderTree(arr, node2, 0, size); //create level order tree using the array
    printTree(node2, true);
    getTotalAccessTime(node2, 0, true, &totalAccessTime); //updates totalAccessTime
    printf("Total access time of the second binary tree: %d", totalAccessTime);
    puts("");
}



