#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

//node of our tree
struct node {
	char letter;
	struct node* left;
	struct node* right;
};


//allocates a new node with given letter
//right and left pointers are NULL
struct node* createNode(char character) {
    // Allocates memory for the node
    struct node* newNode = malloc(sizeof(struct node));

    // Stores the character
    newNode->letter = character;

    // Set left and right to NULL
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


//build the tree needed to do morse to english conversion
//see project description
void buildMorseTree(struct node* root) {
    struct node* eNode = createNode('e');
    root->left = eNode;

    struct node* tNode = createNode('t');
    root->right = tNode;

    struct node* iNode = createNode('i');
    eNode->left = iNode;

    struct node* aNode = createNode('a');
    eNode->right = aNode;

    struct node* nNode = createNode('n');
    tNode->left = nNode;

    struct node* mNode = createNode('m');
    tNode->right = mNode;

    struct node* sNode = createNode('s');
    iNode->left = sNode;

    struct node* uNode = createNode('u');
    iNode->right = uNode;

    struct node* rNode = createNode('r');
    aNode->left = rNode;

    struct node* wNode = createNode('w');
    aNode->right = wNode;

    struct node* dNode = createNode('d');
    nNode->left = dNode;

    struct node* kNode = createNode('k');
    nNode->right = kNode;

    struct node* gNode = createNode('g');
    mNode->left = gNode;

    struct node* oNode = createNode('o');
    mNode->right = oNode;

    struct node* hNode = createNode('h');
    sNode->left = hNode;

    struct node* vNode = createNode('v');
    sNode->right = vNode;

    struct node* fNode = createNode('f');
    uNode->left = fNode;

    struct node* lNode = createNode('l');
    rNode->left = lNode;

    struct node* pNode = createNode('p');
    wNode->left = pNode;

    struct node* jNode = createNode('j');
    wNode->right = jNode;

    struct node* bNode = createNode('b');
    dNode->left = bNode;

    struct node* xNode = createNode('x');
    dNode->right = xNode;

    struct node* cNode = createNode('c');
    kNode->left = cNode;

    struct node* yNode = createNode('y');
    kNode->right = yNode;

    struct node* zNode = createNode('z');
    gNode->left = zNode;

    struct node* qNode = createNode('q');
    gNode->right = qNode;
}


//prints the Morse Tree in preorder
void printMorseTree(struct node* node) {

    // Reached a dead end
    if(node == NULL){
        return;
    }

    // Print the letter
    printf("%c", node->letter);
    printf(" ");

    // Go right
    printMorseTree(node->left);

    // Go left
    printMorseTree(node->right);

}


//converts all the characters(dot, dash, space, slash) pointed to 
//by characters and converts to english characters and places the 
//english conversions in output.
//This function will create the root by calling createNode.
//The data of the root node can be a character 0
//and will build the tree by calling buildTree(root)
//After building the tree, call printMorseTree to show it was built correctly
void convertMorseToEnglish(char* characters, char* output) {
	struct node* root = createNode('0');
	buildMorseTree(root);
	printMorseTree(root);

    printf("\n");

    // Array of 100 character pointers
    char **tokens = malloc(100 * sizeof(char*));

    // For keeping track of current index in array
    int counter = 0;

    // For keeping track of the size of the current token
    int tokenLength = 0;

    // For keeping track of the current index for the output as we will be adding to it after translating from morse code
    int outputCurrIndex = 0;

    // For storing the character retrieved from morse code
    char theCharcter = 'z';

    // Splits the characters by each space
    char *token = strtok(characters, " ");

    // While there is still a space
    while(token != NULL){
        // Allocates memory for the current token to store in the array
        tokens[counter] = malloc((strlen(token) + 1) * sizeof(char));

        // Make a copy of the token. Stores it in array
        strcpy(tokens[counter], token);

        // Increment index
        counter = counter + 1;

        // Go to next token
        token = strtok(NULL, " ");
    }

    // Loops through, printing all tokens
    for(int i = 0; i < counter; i++){
        //printf("%s\n", tokens[i]);
        // Stores length of the token
        tokenLength = strlen(tokens[i]);


        //printf("%d\n", tokenLength);

        for(int j = 0; j < tokenLength; j++){
            // If current character is a period
            if(tokens[i][j] == '.'){
                // Go left
                root = root->left;
            // If current character is a dash
            }else if(tokens[i][j] == '-'){
                // Go right
                root = root->right;
            // If current character is a slash
            }else if(tokens[i][j] == '/'){
                // Adds a space to the output
                output[outputCurrIndex] = ' ';

                // Increments current index of output
                outputCurrIndex = outputCurrIndex + 1;
            }
        }
        // Stores the letter retrieved after loop is ran
        theCharcter = root->letter;


        // Adds character to the output
        output[outputCurrIndex] = theCharcter;

        // Increments index of output
        outputCurrIndex = outputCurrIndex + 1;

        // Moves the root back to the beginning for another loop
        root = createNode('0');
        buildMorseTree(root);


    }

   // Making a final output since the current one has a 0 at the front of every word
    char finalOutput[strlen(output)];
    // For storing current index of final output
    int currIndexFinalOutput = 0;


    


    // Goes through output
    for (int m = 0; m < strlen(output); m++) {
        // Skips the 0s
        if (output[m] != '0') {
            // Adds to final output
            finalOutput[currIndexFinalOutput] = output[m];
            // Increments final output index
            currIndexFinalOutput = currIndexFinalOutput + 1;
        }
    }


    // Make the last character null so there is no junk data at the end of the string
    finalOutput[currIndexFinalOutput] = '\0';

    

    
    printf(finalOutput);
    printf("\n");

}






int main() {
	//printf("hello world");
    //printf("\n");

    // Array where every character is 0
    char message[200] = { '0' };

    // Array where every character is NULL
    char output[100] = { '\0' };

    // Tries opening the file
	FILE* datafile = fopen("numberThree.txt", "r");/* open file for reading*/
    // If file cannot be opened
	if (datafile == NULL) { 
        printf("can't open\n"); 
        }
    // If file can be opened
	else
	{
		fgets(message, 199, datafile);
		int length = strlen(message);
		message[length] = ' ';
		message[length + 1] = '\0';

        
		convertMorseToEnglish(message,output);
		
	}

    return 0;
}

