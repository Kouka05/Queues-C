#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100  

typedef struct {
    int front, rear, size;
    int data[MAX_SIZE];
} Queue;

Queue* initialize();
void enqueue(Queue* q, int x);
int dequeue(Queue* q);
int isEmpty(Queue* q);
int isFull(Queue* q);
int maximum(Queue* q);
void swapFirstLast(Queue* q);
void insert(Queue* q, int value, int index);
void reverseOdd(Queue* q);
void reverse(Queue* q, int k);
void display(Queue* q);
void menu();

Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

int isEmpty(Queue* q) {
    return q->size == 0;
}

int isFull(Queue* q) {
    return q->size == MAX_SIZE;
}

void enqueue(Queue* q, int x) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue %d\n", x);
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = x;
    q->size++;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return value;
}

int maximum(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return -1;
    }
    int maxVal = q->data[q->front];
    for (int i = 1; i < q->size; i++) {
        int index = (q->front + i) % MAX_SIZE;
        if (q->data[index] > maxVal)
            maxVal = q->data[index];
    }
    return maxVal;
}

void swapFirstLast(Queue* q) {
    if (q->size < 2) {
        printf("Queue has less than 2 elements. Swap not possible.\n");
        return;
    }
    int lastIndex = (q->rear) % MAX_SIZE;
    int temp = q->data[q->front];
    q->data[q->front] = q->data[lastIndex];
    q->data[lastIndex] = temp;
}

void insert(Queue* q, int value, int index) {
    if (isFull(q)) {
        printf("Queue is full. Cannot insert %d\n", value);
        return;
    }
    if (index < 0 || index > q->size) {
        printf("Invalid index.\n");
        return;
    }

    for (int i = q->size; i > index; i--) {
        q->data[(q->front + i) % MAX_SIZE] = q->data[(q->front + i - 1) % MAX_SIZE];
    }
    q->data[(q->front + index) % MAX_SIZE] = value;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->size++;
}

void reverseOdd(Queue* q) {
    int oddIndexes[MAX_SIZE], oddValues[MAX_SIZE], count = 0;

    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % MAX_SIZE;
        if (q->data[index] % 2 != 0) {
            oddIndexes[count] = index;
            oddValues[count] = q->data[index];
            count++;
        }
    }

    for (int i = 0; i < count; i++) {
        q->data[oddIndexes[i]] = oddValues[count - i - 1];
    }
}

void reverse(Queue* q, int k) {
    if (k <= 0 || k > q->size) {
        printf("Invalid value of k.\n");
        return;
    }

    int temp[k];
    for (int i = 0; i < k; i++) {
        temp[i] = q->data[(q->front + i) % MAX_SIZE];
    }

    for (int i = 0; i < k; i++) {
        q->data[(q->front + i) % MAX_SIZE] = temp[k - i - 1];
    }
}

void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = 0; i < q->size; i++) {
        printf("%d ", q->data[(q->front + i) % MAX_SIZE]);
    }
    printf("\n");
}

void menu() {
    Queue* q = initialize();
    int choice, value, index, k;

    while (1) {
        printf("\nQueue Operations Menu:\n");
        printf("1. Enqueue\n2. Dequeue\n3. Find Maximum\n4. Swap First and Last\n");
        printf("5. Insert at Index\n6. Reverse Odd Numbers\n7. Reverse First k Elements\n");
        printf("8. Display Queue\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(q, value);
                break;
            case 2:
                value = dequeue(q);
                if (value != -1) printf("Dequeued: %d\n", value);
                break;
            case 3:
                value = maximum(q);
                if (value != -1) printf("Maximum value: %d\n", value);
                break;
            case 4:
                swapFirstLast(q);
                printf("Swapped first and last elements.\n");
                break;
            case 5:
                printf("Enter value and index: ");
                scanf("%d %d", &value, &index);
                insert(q, value, index);
                break;
            case 6:
                reverseOdd(q);
                printf("Reversed odd numbers in the queue.\n");
                break;
            case 7:
                printf("Enter k: ");
                scanf("%d", &k);
                reverse(q, k);
                break;
            case 8:
                display(q);
                break;
            case 9:
                free(q);
                printf("Exiting program.\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
