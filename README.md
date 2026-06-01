# Linked List in C

A simple interactive CLI app for managing a linked list, with full CRUD operations.

## Features

- **List** — display all nodes
- **Create** — append a new node
- **Update** — edit an existing node by ID
- **Delete** — remove a node by ID (with confirmation)

## How to Run

```bash
gcc main.c -o linked-list
./linked-list
```

## Usage

On startup, you'll see a menu:

```
1. List
2. Create
3. Update
4. Delete
5. Quit
```

Enter the number corresponding to the action you want to perform.

## Project Structure

```
main.c       # All source code
```

## API Reference

### `struct Node`

The core data structure. Each node holds a string and a pointer to the next node.

```c
struct Node {
    char* data;
    struct Node* next;
};
```

---

### `void print_nodes(struct Node* nodes)`

Prints all nodes in the list with 1-based index numbering.

```c
print_nodes(main_list);
```

---

### `void every_node(struct Node* nodes, void (*cb)(struct Node*))`

Iterates over every node and calls the given callback on each one. Used internally for cleanup.

```c
every_node(main_list, free_node);
```

---

### `void append_node(struct Node** nodes, struct Node* new_node)`

Appends a node to the end of the list.

```c
struct Node* node = malloc(sizeof(struct Node));
node->data = "hello";
node->next = NULL;
append_node(&main_list, node);
```

---

### `char* update_node(struct Node** nodes, int idx, struct Node* updated_node)`

Replaces the node at the given 0-based index. Returns `"Updated"` on success or `"Invalid index"` if the index is out of range.

```c
update_node(&main_list, 0, updated_node);
```

---

### `char* delete_node(struct Node** nodes, int idx)`

Removes the node at the given 0-based index from the list. Returns `"Deleted"` on success or `"Invalid index"` if out of range.

```c
delete_node(&main_list, 0);
```

> **Note:** The removed node is unlinked from the list but not freed. Call `free_node()` separately if needed.

---

### `void free_node(struct Node* node)`

Frees the memory of a single node, including its `data` string.

```c
free_node(node);
```

---

### `struct Node* jump_to(struct Node* nodes, int idx)`

Returns the node at the given 0-based index, or `NULL` if the index is out of range.

```c
struct Node* target = jump_to(main_list, 2);
```

---

### `char* scan_str(char* label)`

Prints a label and reads a line of input from stdin. Returns a heap-allocated string — caller is responsible for freeing it.

```c
char* input = scan_str("Enter value: ");
// ... use input ...
free(input);
```

## Memory Management

All nodes and their `data` strings are heap-allocated via `malloc`. On exit (option 5), the program iterates over the remaining list and frees every node using `every_node` + `free_node` to avoid memory leaks.
