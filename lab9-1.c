/*
Liam Hudson
COP3502
April 11, 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Node for linked list in HashType
struct ListNode {
    struct RecordType data;
    struct ListNode* next;
};

// Fill out this structure
struct HashType
{
	struct ListNode** array;
    int size;
};

// Create a new ListNode
struct ListNode* newListNode(struct RecordType data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Compute the hash function
int hash(int x, int recordSz)
{
	return x % recordSz;
}

void insertRecord(struct HashType* pHashArray, struct RecordType data) {
    int index = hash(data.id, pHashArray->size);
    struct ListNode* newNode = newListNode(data);
    newNode->next = pHashArray->array[index];
    pHashArray->array[index] = newNode;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		struct ListNode* node = pHashArray->array[i];
        if (node != NULL) {
            printf("Index %d -> ", i);
            while (node != NULL) {
                printf("%d %c %d -> ", node->data.id, node->data.name, node->data.order);
                node = node->next;
            }
            printf("NULL\n");
        }
	}
	printf("\n");
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input_lab_9.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType hashTable;
    hashTable.size = recordSz;
    hashTable.array = (struct ListNode**)malloc(recordSz * sizeof(struct ListNode*));
    for (int i = 0; i < recordSz; ++i) {
        hashTable.array[i] = NULL;
    }

    // Insert records into the hash table
    for (int i = 0; i < recordSz; ++i) {
        insertRecord(&hashTable, pRecords[i]);
    }

    // Display records in the hash table
    displayRecordsInHash(&hashTable, recordSz);

	free(pRecords);
}