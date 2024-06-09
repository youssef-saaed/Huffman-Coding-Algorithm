#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type defs and Global variables
#define MAX_MESSAGE_LENGTH 200
#define LeftC i * 2
#define RightC i * 2 + 1
#define Parent i / 2
typedef char* string;

// Key-Code pair struct
typedef struct 
{
    char Key;
    string Code;
} Pair;

// Node struct
struct Node
{
    int Val;
    char Char;
    struct Node *Left, *Right;
};
typedef struct Node Node;

// Min-Heap struct
typedef struct
{
    Node **HeapArr;
    int Size;
    int MaxCapacity;
} MinHeap;


// Message input function
void ReadMessage(string *Message)
{
    *Message = malloc(sizeof(char) * MAX_MESSAGE_LENGTH);
    printf("Enter the message you need to compress: ");
    scanf("%[^\n]s", *Message);
}

// Characters and Frequency array generation function
int CharFreqArrConstructor(string Message, char **Characters, int **Frequencies)
{
    int *FrequencyArray = malloc(sizeof(int) * 128);
    for (int i = 0; i < 128; i++)
    {
        FrequencyArray[i] = 0;
    }
    int Count = 0;
    for (int i = 0; Message[i] != '\0'; i++)
    {
        if (!FrequencyArray[Message[i]])
        {
            Count++;
        }
        FrequencyArray[Message[i]]++;
    }
    *Characters = malloc(sizeof(char) * Count);
    *Frequencies = malloc(sizeof(int) * Count);
    int K = 0;
    for (int i = 0; i < 128; i++)
    {
        if (FrequencyArray[i])
        {
            (*Characters)[K] = (char)i;
            (*Frequencies)[K] = FrequencyArray[i];
            K++;
        }
    }
    free(FrequencyArray);
    return Count;
}

// Node constructor
Node* NewNode(int Val)
{
    Node *N = malloc(sizeof(Node));
    N->Val = Val;
    N->Left = NULL;
    N->Right = NULL;
    N->Char = '\0';
    return N;
}

// Min-Heap constructor
void NewMinHeap(MinHeap *Heap, int MaxCapacity)
{
    (*Heap).MaxCapacity = MaxCapacity;
    (*Heap).Size = 0;
    (*Heap).HeapArr = malloc(sizeof(Node*) * (MaxCapacity + 1));
    for (int i = 0; i <= MaxCapacity; i++)
    {
        (*Heap).HeapArr[i] = NULL;
    }
}

// Pair Constructor
Pair* NewPair(char Key, string Code)
{
    Pair *P = malloc(sizeof(Pair));
    P->Code = malloc(sizeof(char) * 8);
    strcpy(P->Code, Code);
    P->Key = Key;
    return P;
}

// Min Heap destructor
void FreeMinHeap(MinHeap *Heap)
{
    for (int i = 0; i < (*Heap).Size; i++)
    {
        if ((*Heap).HeapArr[i])
        {
            free((*Heap).HeapArr[i]);
        }
    }
    free((*Heap).HeapArr);
}

// Pair destructor
void FreePair(Pair *P)
{
    free((*P).Code);
}

// Binary Tree destructor
void FreeBinaryTree(Node *Root)
{
    if (!Root)
    {
        return;
    }
    FreeBinaryTree(Root->Left);
    FreeBinaryTree(Root->Right);
    free(Root);
}

// Swap Nodes
void SwapNodes(Node **A, Node **B)
{
    Node *Temp = *A;
    *A = *B;
    *B = Temp;
}

// Min-Heap insertion function
int InsertInMinHeap(MinHeap *Heap, Node **NodeV)
{
    if ((*Heap).Size == (*Heap).MaxCapacity)
    {
        return 0;
    }
    (*Heap).Size++;
    (*Heap).HeapArr[(*Heap).Size] = *NodeV;
    int i = (*Heap).Size;
    while (i != 1)
    {
        if ((*Heap).HeapArr[i]->Val < (*Heap).HeapArr[Parent]->Val)
        {
            SwapNodes(&((*Heap).HeapArr[i]), &((*Heap).HeapArr[Parent]));
            i = Parent;
            continue;
        }
        break;
    }
    return 1;
}

// Min-Heap min extraction function
int ExtractMin(MinHeap *Heap, Node **Min)
{
    if ((*Heap).Size == 0)
    {
        return 0;
    }
    *Min = (*Heap).HeapArr[1];
    (*Heap).HeapArr[1] = NULL;
    SwapNodes(&((*Heap).HeapArr[1]), &((*Heap).HeapArr[(*Heap).Size]));
    (*Heap).Size--;
    int i = 1;
    while (i < (*Heap).Size)
    {
        if (LeftC <= (*Heap).Size && RightC <= (*Heap).Size)
        {
            if ((*Heap).HeapArr[LeftC]->Val < (*Heap).HeapArr[i]->Val && (*Heap).HeapArr[LeftC]->Val <= (*Heap).HeapArr[RightC]->Val)
            {
                SwapNodes(&((*Heap).HeapArr[i]), &((*Heap).HeapArr[LeftC]));
                i = LeftC;
                continue;
            }
            if ((*Heap).HeapArr[RightC]->Val < (*Heap).HeapArr[i]->Val && (*Heap).HeapArr[RightC]->Val <= (*Heap).HeapArr[LeftC]->Val)
            {
                SwapNodes(&((*Heap).HeapArr[i]), &((*Heap).HeapArr[RightC]));
                i = RightC;
                continue;
            }
        }
        else if (LeftC <= (*Heap).Size && (*Heap).HeapArr[LeftC]->Val < (*Heap).HeapArr[i]->Val)
        {
            SwapNodes(&((*Heap).HeapArr[i]), &((*Heap).HeapArr[LeftC]));
            i = LeftC;
            continue;
        }
        break;
    }
    return 1;
}

// Huffman tree constructor
Node* HuffmanTree(char *Characters, int *Frequencies, int Count)
{
    MinHeap PriorityQueue;
    NewMinHeap(&PriorityQueue, Count);
    Node *Temp;
    for (int i = 0; i < Count; i++)
    {
        Temp = NewNode(Frequencies[i]);
        Temp->Char = Characters[i];
        InsertInMinHeap(&PriorityQueue, &Temp);
    }
    while (PriorityQueue.Size > 1)
    {
        Node *Min1, *Min2;
        ExtractMin(&PriorityQueue, &Min1);
        ExtractMin(&PriorityQueue, &Min2);
        Temp = NewNode(Min1->Val + Min2->Val);
        Temp->Left = Min1;
        Temp->Right = Min2;
        InsertInMinHeap(&PriorityQueue, &Temp);
    }
    ExtractMin(&PriorityQueue, &Temp);
    FreeMinHeap(&PriorityQueue);
    return Temp;
}

// Huffman code producer helper
void ProduceHuffmanCodeTraverser(Pair ***CharCodePairsArr, Node *TreeRoot, string Code, int *i)
{
    if (!TreeRoot)
    {
        return;
    }
    if (TreeRoot->Char)
    {
        (*CharCodePairsArr)[*i] = NewPair(TreeRoot->Char, Code);
        (*i)++;
    }
    char LeftCode[8], RightCode[8];
    strcpy(LeftCode, Code);
    strcpy(RightCode, Code);
    strcat(LeftCode, "0");
    strcat(RightCode, "1");
    ProduceHuffmanCodeTraverser(CharCodePairsArr, TreeRoot->Left, LeftCode, i);
    ProduceHuffmanCodeTraverser(CharCodePairsArr, TreeRoot->Right, RightCode, i);
}

// Huffman code producer function
Pair** ProduceHuffmanCode(char *Characters, int *Frequencies, int Count)
{
    Node *HuffmanTreeRoot = HuffmanTree(Characters, Frequencies, Count);
    Pair **CharCodePairsArr = malloc(sizeof(Pair*) * Count);
    int i = 0;
    ProduceHuffmanCodeTraverser(&CharCodePairsArr, HuffmanTreeRoot, "", &i);
    FreeBinaryTree(HuffmanTreeRoot);
    return CharCodePairsArr;
}

// Print bits before encoding 
void PrintBitsBeforeEncoding(string Message)
{
    size_t C = 0;
    printf("\n--------------------------------------------------------------\n");
    printf("The bits stored without Huffman Code Algorithm:\n");
    while (Message[C])
    {
        unsigned x = 1 << (sizeof(Message[C]) * 8 - 1);
        for (int i = 0; i < sizeof(Message[C]) * 8; i++)
        {
            printf("%d", (x & Message[C]) ? 1 : 0);
            x >>= 1;
        }
        C++;
    }
    printf("\nStorage size: %d bits\n", C * sizeof(Message[0]) * 8);
    printf("--------------------------------------------------------------\n\n");
}

// Print bits after encoding 
void PrintBitsAfterEncoding(string Message, Pair **CharsCodePair, int Count)
{
    size_t C = 0, Bits = 0;
    printf("\n--------------------------------------------------------------\n");
    printf("The bits stored with Huffman Code Algorithm:\n");
    while (Message[C])
    {
        for (int i = 0; i < Count; i++)
        {
            if (CharsCodePair[i]->Key == Message[C])
            {
                Bits += strlen(CharsCodePair[i]->Code);
                printf("%s", CharsCodePair[i]->Code);
            }
        }
        C++;
    }
    printf("\nStorage size: %d bits\n", Bits);
    printf("--------------------------------------------------------------\n\n");
}

// Algorithm program function
void HuffmanCodeAlgorithm()
{
    string Message;
    ReadMessage(&Message);
    char *Characters;
    int *Frequencies;
    int CharsCount = CharFreqArrConstructor(Message, &Characters, &Frequencies);
    Pair **CharsCodePair = ProduceHuffmanCode(Characters, Frequencies, CharsCount);
    free(Characters);
    free(Frequencies);
    for (int i = 0; i < CharsCount; i++)
    {
        printf("\"%c\" : %s\n", CharsCodePair[i]->Key, CharsCodePair[i]->Code);
    }
    PrintBitsBeforeEncoding(Message);
    PrintBitsAfterEncoding(Message, CharsCodePair, CharsCount);
    free(Message);
    for (int i = 0; i < CharsCount; i++)
    {
        FreePair(CharsCodePair[i]);
        free(CharsCodePair[i]);
    }
    free(CharsCodePair);
}

int main(void)
{
    HuffmanCodeAlgorithm();
    return 0;
}