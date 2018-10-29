#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "queue.h"

struct Node {
	void* data;
	struct Node* next;
};

struct queue {
	struct Node* head;
	struct Node* tail;
	int len;
};





queue_t queue_create(void)
{
	/*
	 * queue_create - initialize and return a queue pointer
	 * it will return a queue_t new queue
	 * 
	 */
	
	queue_t new = (queue_t)malloc(sizeof(queue_t)); // malloc enough space for the queue
	
	new->tail = new->head; // let the tail point to what the head points to
	new->head = NULL; // let the head point to null
	new->len = 0; // set the length of the queue to 0

	return new; // return the queue
}

int queue_destroy(queue_t queue)
{
	/*
	 *  queue_destory - will free a given queue
	 *  @queue - the queue to be freed
	 * 	return -1 if the queue is not empty
	 *  else return 0 after freeing
	 *  
	 */

	if(queue == NULL || queue_length(queue) > 0){ // check the length of the queue
		//printf("len=%d\n",queue_length(queue));
		return -1;
	}
	free(queue); // free the malloc'ed space
	return 0;
}

int queue_enqueue(queue_t queue, void *data)   
{
	/*
	 * queue_enqueue - place new data at the tail of the queue
	 * @queue - the queue where the new data will be placed
	 * @data - a pointer to the data to be stored at the new node
	 * return -1 if there is invalid input
	 * return 0 if sucessful 
	 *  
	 */
	
	if( queue == NULL || data == NULL){ 
		return -1;
	} // check if the input is NULL

	// create a new node
	struct Node* new = (struct Node*)malloc(sizeof(struct Node));
	new->data = data;
	new->next = NULL;
	


	// O(1) insertion:

	if(queue->head == NULL) {
		// if the queue previously points to nothing
		queue->head = new;
		queue->tail = queue->head;
		(queue->len)++; // increment the length of the queue
		return 0;
	}
	// regular insert
	queue->tail->next = new;
	queue->tail = new;
	(queue->len)++; // increment the length of the queue

	return 0;

}

int queue_dequeue(queue_t queue, void **data)
{
	/*
	 * queue_dequeue - delete data at the beginning of the queue
	 * @queue - the queue to cut off the head 
	 * @data - the pointer to the address of where to save the data of the head
	 * return -1 if invalid input
	 * return 0 if sucessful
	 * 
	 */

	if( (queue == NULL) || (data == NULL) || (queue_length(queue) == 0)){ // check for invalid input
		return -1;
	}

	*data = queue->head->data; // save the data
	queue->head = queue->head->next; // decrement the head
	(queue->len)--;

	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/*
	 * queue_delete - delete data at the end of the queue
	 * @queue - the queue to delete the data node 
	 * @data - the pointer to the data that is to be deleted
	 * return -1 if invalid input
	 * return 0 if sucessful
	 * 
	 */

	if( (queue == NULL) || (data == NULL) ){
		return -1;
	} // check for invalid input



	if(queue->head->data == data){
		// enter this if statement if element to delete is the head
		if(queue->head->next == NULL){
			// only one element in the @queue
			struct Node* deletedNode = queue->head;
			queue->head = NULL;
			(queue->len)--;
			free(deletedNode);
			return 0;
		}
		else{
			// head of a @queue with length > 1
			struct Node* deletedNode = queue->head;
			queue->head = queue->head->next;
			(queue->len)--;
			free(deletedNode);
			return 0;
		}
	}

	// if not the head of the list, iterate through the list until you get to the node before where the data to delete is
	struct Node* temp;
	for(temp=queue->head; temp->next!=NULL; temp=temp->next){
		if( (temp->next != NULL) && (temp->next->data == data) ){
			break;
		}
	}


	if(temp->next == NULL && temp->data != data){
		// at end of list and didnt find the value
		return -1;
	}
	else{
		// simple delete for a middle node
		struct Node* deletedNode = temp->next;
		temp->next = temp->next->next;
		(queue->len)--;
		free(deletedNode);
		temp = queue->head;
		for(temp=queue->head; temp->next!=NULL; temp=temp->next);
		queue->tail = temp;
		return 0;
	}

}



int queue_iterate(queue_t queue, queue_func_t func, void *arg, void **data)
{
	/*
	 * queue_iterate - iterate through a queue and call a function on each argument
	 * 					if the function returns 1, save that data to @data
	 * @queue - the queue to iterate through
	 * @func - the function to call on the elements
	 * @arg - arguments to pass into the function
	 * @data - the pointer to the address of where to save the data
	 * return -1 if invalid input
	 * return 0 if sucessful
	 * 
	 */

	if(queue == NULL || func == NULL){
		return -1;
	} // check for invlaid input

	struct Node *temp;
	int retval;
	
	for(temp = queue->head; temp->next != NULL; temp = temp->next){
		retval = (*func)(temp->data,arg); // call @func and save the return value
		if(retval == 1){
			if(data != NULL){
				*data = temp ->data; // save the data
			}
			return 0;
		}
	}
	// call the function on the last element in the queue, same logic as above
	retval = (*func)(temp->data,arg);
		if(retval == 1){
			if(data != NULL){
				*data = temp ->data;
			}
			return 0;
		}

	return 0;

}

int queue_length(queue_t queue)
{
	/*
	 * queue_length - return the length of the @queue
	 * @queue - the queue to get the length of
	 * return -1 if invalid input
	 * return length if sucessful
	 * 
	 */
	
	if( queue == NULL){
		return -1;
	}
	return queue->len;
	

}

void printQ( queue_t queue ){
	if(queue == NULL){
		printf("No queue fam\n");
		return;
	}
	if(queue->head == NULL) {
		printf("NULL\n");
		return;
	}

	struct Node* temp;
	for(temp=queue->head; temp->next!=NULL; temp=temp->next){
	 	printf("%d->", *(int*)(temp->data) );
	}
	printf("%d->",*(int*)(temp->data) );
	printf("NULL\n");
}

void printT( queue_t queue ){
	printf("Tail = %d\n", *(int*)queue->tail->data);
}

/* Callback function that increments items by a certain value */
static int inc_item(void *data, void *arg)
{
    int *a = (int*)data;
    int inc = (int)(long)arg;

    *a += inc;

    return 0;
}

/* Callback function that finds a certain item according to its value */
static int find_item(void *data, void *arg)
{
    int *a = (int*)data;
    int match = (int)(long)arg;

    if (*a == match)
        return 1;

    return 0;
}



void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    int *ptr = NULL;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < 10; i++)
        queue_enqueue(q, &data[i]);

    /* Add value '1' to every item of the queue */
    queue_iterate(q, inc_item, (void*)1, NULL);
    assert(data[0] == 2);

    /* Find and get the item which is equal to value '5' */
	printQ(q);
	printT(q);

    queue_iterate(q, find_item, (void*)10, (void**)&ptr);
    // assert(ptr != NULL);
    // assert(ptr == &data[3]);
    // assert(*ptr == 5);
}
/*
int main(){
	test_iterator();
	return 0;
}*/
/*
int main(){
	test_iterator();
	int i = -1;
	int* i_int_ptr = &i;
	int** i_int_ptr_ptr = &i_int_ptr;
	void* i_ptr = &i;
	void** ptr_ptr = &i_ptr;
	int temp;
	int len;
	int num = 5;
	int nums[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	puts("------ TEST queue_create() ------ ");
	queue_t head = queue_create();
	puts("SUCCESS");
	len = queue_length(head);
	printf("%d\n", len);
	
	
	puts("------ TEST queue_enqueue() & queue_length() ------ ");
	temp = queue_enqueue(head , &nums[4]);
	len = queue_length(head);
	printQ( head );
	if(temp == -1 || len == -1){
		puts("ERROR -1");
	}
	else{
		printf("SUCCESS - %d / 1\n",len);
	}
	num = -10;
	temp = queue_enqueue(head , &nums[3]);
	len = queue_length(head);
	printQ( head );
	if(temp == -1 || len == -1){
		puts("ERROR -1");
	}
	else{
		printf("SUCCESS - %d / 2\n",len);
	}
	num = 100;
	temp = queue_enqueue(head , &nums[2]);
	len = queue_length(head);
	printQ( head );
	if(temp == -1 || len == -1){
		puts("ERROR -1");
	}
	else{
		printf("SUCCESS - %d / 3\n",len);
	}
	
	puts("------ TEST dequeue() ------ ");
	temp = queue_dequeue(head, ptr_ptr);
	if( temp == -1){
		puts("ERROR -1");
	}
	else{
		printf("SUCESS i = %d | newlen= %d\n",i, queue_length(head) );
	}
	temp = queue_dequeue(head, ptr_ptr);
	if( temp == -1){
		puts("ERROR -1");
	}
	else{
		printf("SUCESS i = %d | newlen= %d\n",i, queue_length(head) );
	}
	temp = queue_dequeue(head, ptr_ptr);
	if( temp == -1){
		puts("ERROR -1");
	}
	else{
		printf("SUCESS i = %d | newlen= %d\n",i, queue_length(head) );
	}
	temp = queue_dequeue(head, ptr_ptr);
	if( temp == -1){
		puts("ERROR -1");
	}
	else{
		printf("SUCESS i = %d | newlen= %d\n",i, queue_length(head) );
	}
	
	puts("------ TEST delete() ------ ");
	num = 3;
	temp = queue_enqueue(head , &nums[10] );
	len = queue_length(head);
	printf("%d\n", len);
	num = 25;
	temp = queue_enqueue(head , &nums[6]);
	int k = 25;
	printQ( head );
	len = queue_length(head);
	printf("%d\n", len);
	temp = queue_delete(head, &nums[10]);
	if( temp == -1){
		puts("ERROR");
	}
	printQ( head );
	printT( head );
	len = queue_length(head);
	printf("%d\n", len);
	num = 66;
	temp = queue_enqueue(head , &nums[8]);
	len = queue_length(head);
	if(temp == -1 || len == -1){
		puts("ERROR -1");
	}
	else{
		printf("SUCCESS - %d\n",len);
	}
	printQ( head );
	len = queue_length(head);
	printf("%d\n", len);
	printT( head );
	num = -10;
	queue_delete(head,&nums[2]);
	printQ( head );
	len = queue_length(head);
	printf("%d\n", len);
	num = -10;
	temp = queue_delete(head,&nums[2]);
	if (temp == -1){
		puts("ERROR is good");
	}
	printQ( head );
	len = queue_length(head);
	printf("%d\n", len);
	i = -1;
	temp = queue_dequeue(head, ptr_ptr);
	if( temp == -1){
		puts("ERROR -1");
	}
	else{
		printQ(head);
		printf("ptr points to:%d\n", **(int**)ptr_ptr);
		printf("%d\n",i);
	}
	puts("------ TEST queue_destroy() ------ ");
	temp = queue_destroy(head);
	if( temp == -1){
		puts("ERROR");
	}
	else{
		puts("success");
	}
	queue_t newnew = queue_create();
	printQ( newnew );
	num = 7;
	queue_enqueue(newnew , &nums[7]);
	queue_dequeue(newnew,  (void**)i_int_ptr_ptr);
	printf("ptr points to:%d\n", **i_int_ptr_ptr);
		printf("%d\n",i);
	temp = queue_destroy(newnew);
	if( temp == -1){
		puts("ERROR1");
	}
	else{
		puts("success");
	}
	
	return 0;
}
*/