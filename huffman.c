#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

struct MinHeapNode {
	char data;
	unsigned freq;
	struct MinHeapNode *left, *right;
};

struct MinHeap {
	unsigned size;
	unsigned capacity;
	struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq){
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;
	return temp;
}

struct MinHeap* createMinHeap(unsigned capacity){

	struct MinHeap* minHeap
		= (struct MinHeap*)malloc(sizeof(struct MinHeap));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array
		= (struct MinHeapNode**)malloc(minHeap->
capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b){
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx){
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{
	return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap){
	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode){
	++minHeap->size;
	int i = minHeap->size - 1;
	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}

// A standard funvtion to build min heap
void buildMinHeap(struct MinHeap* minHeap){
	int n = minHeap->size - 1;
	int i;
	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);

	printf("\n");
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root){
	return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size){
	struct MinHeap* minHeap = createMinHeap(size);
	int i;
	for (i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);
	return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size){
	struct MinHeapNode *left, *right, *top;

	// Step 1: Create a min heap of capacity
	// equal to size. Initially, there are
	// modes equal to size.
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

	// Iterate while size of heap doesn't become 1
	while (!isSizeOne(minHeap)) {
		// Step 2: Extract the two minimum
		// freq items from min heap
		left = extractMin(minHeap);
		right = extractMin(minHeap);
		// Step 3: Create a new internal
		// node with frequency equal to the
		// sum of the two nodes frequencies.
		// Make the two extracted node as
		// left and right children of this new node.
		// Add this node to the min heap
		// '$' is a special value for internal nodes, not used
		top = newNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertMinHeap(minHeap, top);
	}

	// Step 4: The remaining node is the
	// root node and the tree is complete.
	return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct MinHeapNode* root, int arr[], int top){
	// Assign 0 to left edge and recur
	if (root->left) {
		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}
	// Assign 1 to right edge and recur
	if (root->right) {
		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}
	// If this is a leaf node, then
	// it contains one of the input
	// characters, print the character
	// and its code from arr[]
	if (isLeaf(root)) {
		printf("%c: ", root->data);
		printArr(arr, top);
	}
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size){
	// Construct Huffman Tree
	struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
	// Print Huffman codes using
	// the Huffman tree built above
	int arr[MAX_TREE_HT], top = 0;
	printCodes(root, arr, top);
}

struct MinHeapNode* returnHuffmanCodes(char data[], int freq[], int size){
	// Construct Huffman Tree
	struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
	// Print Huffman codes using
	// the Huffman tree built above
	int arr[MAX_TREE_HT], top = 0;
	printCodes(root, arr, top);
	return root;
}



void convertContenttoArrays(int **frequ, char **vals, char *content, int *totalCh, int lengthOfText){
	int i, k, j, totalChars;
	int *frequencies;
	char *values;	
	totalChars = 0;
	for(i = 0; i < lengthOfText; i++){ //Trying to find element in our list and increment
		k = 0;
		for(j = 0; j < totalChars; j++){
			if(content[i] == values[j]){
				frequencies[j]++;
				k = 1;
			}
		}
		if(k == 0){ //was NOT found
			int *newFrequencies = malloc(sizeof(int) * (totalChars + 1));
			char *newValues = malloc(sizeof(char) * (totalChars + 1));
			for(j = 0; j < totalChars; j++){
				newFrequencies[j] = frequencies[j];
				newValues[j] = values[j];
			}
			free(values);
			free(frequencies);
			newFrequencies[totalChars] = 1;
			newValues[totalChars] = content[i];
			frequencies = newFrequencies; 
			values = newValues;
			totalChars++;
		}
	}
	*totalCh = totalChars;
	*frequ = frequencies;
	*vals = values; 
}

void makeBitStrings(struct MinHeapNode* root, int arr[], int top, int *current, int **bitArray, char *charValue){
	// Assign 0 to left edge and recur
	if (root->left) {
		arr[top] = 0;
		makeBitStrings(root->left, arr, top + 1, current, bitArray, charValue);
	}
	// Assign 1 to right edge and recur
	if (root->right) {
		arr[top] = 1;
		makeBitStrings(root->right, arr, top + 1, current, bitArray, charValue);
	}
	// If this is a leaf node, then
	// it contains one of the input
	// characters, print the character
	// and its code from arr[]
	
	if (isLeaf(root)) {
		charValue[*current] = root->data;
		int i;
		bitArray[*current] = malloc(sizeof(int) * (top + 1));
		bitArray[*current][0] = top; //element 0 is length of the bitstring
		for(i = 0; i < top; i++){
			bitArray[*current][i+1] = arr[i];
		}
		*current = *current + 1;		
	}
}

char convertIntArraytoChar(int* arr){
	int tot = 0, start = 128, i;
	for(i = 0; i < 8; i++){
		if(arr[i] == 1){
			tot = tot + start;
		}
		start = start / 2;
	}
	return tot;
}

int* convertChartoIntArray(unsigned char c){

	int* arr = malloc(sizeof(int) * 8);
	int bitval = 128, slot = 0, cval = c;
	for(slot = 0; slot < 8; slot++){
		if(bitval <= cval){
			cval = cval - bitval;
			arr[slot] = 1;
		}else{
			arr[slot] = 0;
		}
		bitval = bitval / 2;
	}
	return arr;
}

void writeCompressedFile(FILE *output, char *content, int **bitStrings, char *charvalues, int lengthOfText){
	int i, j, loc, bits, curbit = 0;
	int *arr = malloc(sizeof(int)*8);
	char c;
	for(i = 0; i < lengthOfText; i++){ //For Each character
		loc = 0; bits = 0;
		while(charvalues[loc] != content[i]){ //find char equal to charvalues
			loc++;
		}
		while(bits < bitStrings[loc][0]){ //While we haven't placed the final bit of the bitstring
			arr[curbit] = bitStrings[loc][bits + 1];
			curbit++;			
			if(curbit == 8){ //We have 8 bits in the byte array and need to print
				c = convertIntArraytoChar(arr);		
				fputc(c, output);
				curbit = 0;
			}
			bits++;
		}
	}
	//Add padding and submit final byte
	while(curbit < 8){
		arr[curbit] = 0;
		curbit++;
	}
	//print final bit to array
	c = convertIntArraytoChar(arr);
	fputc(c, output);
	free(arr);
}

void decryptCompressedFile(FILE *input, FILE *output, struct MinHeapNode* root){
	//Get input into memory
	fseek(input, 0, SEEK_END);
	int lengthOfText = ftell(input);
	char *content;
	fseek(input, 0, SEEK_SET);
	content = malloc(lengthOfText);
	fread(content, 1, lengthOfText, input);

	//Begin Decrypting
	int i, j, loc, bits, curbit;
	int *arr;
	struct MinHeapNode* base;
	base = root;	
	while(i < lengthOfText){
		arr = convertChartoIntArray(content[i]);
		i++;

		for(j = 0; j < 8; j++){
			if(arr[j] == 0){ //left
				base = base->left;
			}else{ //right
				base = base->right;
			}
			if(isLeaf(base)){ //We found the char
				fputc(base->data , output);
				base = root;
			}
		}
		free(arr);
	}
}

// Driver program to test above functions
int main(int argc, char *argv[]){

	FILE *textp, *output, *decomp;
	textp = fopen(argv[1], "rb");
	if(textp == NULL){
		printf("Input file not found\n");
		exit(1);
	}
	output = fopen(argv[2], "w+");
	if(output == NULL){
		printf("Output file not found\n");
		exit(1);
	}
	decomp = fopen(argv[3], "w+");
	if(decomp == NULL){
		printf("Decomp file not found\n");
		exit(1);
	}


	fseek(textp, 0, SEEK_END);
	int lengthOfText = ftell(textp);
	char *content;
	fseek(textp, 0, SEEK_SET);
	content = malloc(lengthOfText);
	fread(content, 1, lengthOfText, textp);
	int totalChars, i;
	totalChars = 0;
	int *frequencies;
	char *values;

	convertContenttoArrays(&frequencies, &values, content, &totalChars, lengthOfText);

	struct MinHeapNode* root;	
	root = returnHuffmanCodes(values, frequencies, totalChars);

	int **bitStrings = malloc(sizeof(int*) * totalChars);
	char *charvalues = malloc(sizeof(char) * totalChars);
	int current = 0;
	int arr[100];
	makeBitStrings(root, arr, 0, &current, bitStrings, charvalues);

	printf("***************************\nCOMPRESS\n***************************\n");

	writeCompressedFile(output, content, bitStrings, charvalues, lengthOfText);
	printf("***************************\nDECOMPRESS\n***************************\n");	
	fclose(output);
	output = fopen(argv[2], "rb");


	//NOTE If we had more time, we would specify the number of bytes to decrypt,
	//     but with our time frame, we are going to leave the project as is.
	decryptCompressedFile(output, decomp, root);

	return 0;
}
