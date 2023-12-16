#include "graph.h"

struct graph* createGraph(int n)
{
    struct graph* newGraph = (struct graph*)malloc(sizeof(struct graph)); 
    newGraph->N = n;
    newGraph->array = (struct adjList*)malloc(n*sizeof(struct adjList));
    for(int i = 0; i < n; i++)
    {
        newGraph->array[i].head = NULL;
    }
    return newGraph;
}

void addEdge(struct graph* graph, int source, int target, int weight)
{
    struct adjListNode* newNode = (struct adjListNode*)malloc(sizeof(struct adjListNode));
    newNode->graph_node_id = target;
    newNode->weight = weight;
    newNode->next = graph->array[source].head;
    graph->array[source].head = newNode;
}

void displayGraph(struct graph* graph, char** cities)
{
    int v;
    for (v = 0; v < graph->N; ++v)
    {
        struct adjListNode* pCrawl = graph->array[v].head;
        printf("%s is connected to:\n", cities[v]);
        while (pCrawl)
        {
            printf("%s\t", cities[pCrawl->graph_node_id]);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

void deleteEdge(struct graph* graph, int source, int target)
{
    struct adjListNode* pCrawl = graph->array[source].head;
    if(pCrawl->graph_node_id == target)
    {
        graph->array[source].head = pCrawl->next;
        free(pCrawl);
        return;
    }
    while (pCrawl->next)
    {
        if(pCrawl->next->graph_node_id == target)
        {
            struct adjListNode* temp = pCrawl->next;
            pCrawl->next = pCrawl->next->next;
            free(temp);
            return;
        }
        pCrawl = pCrawl->next;
    }
}