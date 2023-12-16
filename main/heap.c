#include "heap.h"

struct minHeapNode* new_min_heap_node(int n, int dist)
{
	struct minHeapNode* node = (struct minHeapNode*)malloc(sizeof(struct minHeapNode));
	node->graph_node_id = n;
	node->dist = dist;
	return node;
}

struct minheap *create_heap(int m)
{
	struct minheap* h = (struct minheap*)malloc(sizeof(struct minheap));
	h->max_size = m;
	h->cur_size = 0;
	h->array = (struct minHeapNode**)malloc(sizeof(struct minHeapNode*)*m);
	h->pos = (int*)malloc(sizeof(int)*m);
	return h;
}

int insert_heap(struct minheap *h, struct minHeapNode *n)
{
	if(h->cur_size == h->max_size)
		return 0;
	h->array[h->cur_size] = n;
	h->pos[n->graph_node_id] = h->cur_size;
	h->cur_size++;
	return 1;
}

int delete_heap(struct minheap *h)
{
	if(h->cur_size == 0)
		return 0;
	struct minHeapNode* node = h->array[0];
	h->array[0] = h->array[h->cur_size-1];
	h->pos[h->array[0]->graph_node_id] = 0;
	h->cur_size--;
	return 1;
}

void decreaseKey(struct minheap* h, int n, int dist)
{
	int i = h->pos[n];
	h->array[i]->dist = dist;
	while(i>0 && h->array[i]->dist < h->array[(i-1)/2]->dist)
	{
		h->pos[h->array[i]->graph_node_id] = (i-1)/2;
		h->pos[h->array[(i-1)/2]->graph_node_id] = i;
		struct minHeapNode* temp = h->array[i];
		h->array[i] = h->array[(i-1)/2];
		h->array[(i-1)/2] = temp;
		i = (i-1)/2;
	}
}

struct minHeapNode *findmin(struct minheap *h)
{
	return h->array[0];
}

void destroy_heap(struct minheap *h)
{
	free(h->array);
	free(h->pos);
	free(h);
}

void display_heap(struct minheap *h)
{
	int i;
	printf("\n");
	for(i=0;i<h->cur_size;i++)
	{
		printf("%d ",h->array[i]->graph_node_id);
	}
}

int is_empty(struct minheap *h)
{
	if(h->cur_size == 0)
		return 1;
	else
		return 0;
}