#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
  char* data;
  struct Node* next;
};

int print_label(char *label) {
  return printf("========= %s =========\n", label);
}

void print_nodes(struct Node* nodes) {
  struct Node* node = nodes;

  print_label("Lists");
  for (int idx = 1; 1; idx++) {
    if (node == NULL) {
      print_label("Lists");
      return;
    }
    printf("%d. %s\n", idx, node->data);
    node = node->next;
  }
}

void free_node(struct Node* node) {
  if (node == NULL) return;
  if (node->data != NULL) free(node->data);
  free(node);
}

void every_node(struct Node* nodes, void (*cb)(struct Node*)) {
  struct Node* node = nodes;
  while (1) {
    if (node == NULL) return;
    cb(node);
    node = node->next;
  }
}

void append_node(struct Node** nodes, struct Node* new_node) {
  if (*nodes == NULL) {
    *nodes = new_node;
    return;
  }

  struct Node* node = *nodes;
  while (1) {
    if (node->next == NULL) {
      node->next = new_node;
      return;
    }
    node = node->next;
  }
}

char* update_node(struct Node** nodes, int idx, struct Node* updated_note) {
  struct Node** node = nodes;

  for (int i = 0; i <= idx; i++) {
    if (*node == NULL) return "Invalid index";
    if (i == idx) {
      updated_note->next = (*node)->next;
      *node = updated_note;
      return "Updated";
    }
    node = &((*node)->next);
  }

  return "Invalid index";
}

char* delete_node(struct Node** nodes, int idx) {
  struct Node** node = nodes;

  for (int i = 0; i <= idx; i++) {
    if (*node == NULL) return "Invalid index";
    if (i == idx) {
      struct Node* to_delete = *node;
      *node = (*node)->next;
      free_node(to_delete); 
      return "Deleted";
    }
    node = &((*node)->next);
  }

  return "Invalid index";
}

struct Node* jump_to(struct Node* nodes, int idx) {
  struct Node* node = nodes;
  for (int i = 0; i < idx; i++) {
    if (node == NULL) return NULL;
    node = node->next;
  }
  return node;
}

char* scan_str(char *label) {
  char buffer[256];
  printf("%s", label);

  // flush leftover '\n' from previous scanf
  int c;
  while ((c = getchar()) != '\n' && c != EOF);

  if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    buffer[strcspn(buffer, "\n")] = '\0';
  } else {
    buffer[0] = '\0';
  }

  char* data = malloc(strlen(buffer) + 1);
  strcpy(data, buffer);
  return data;
}

int main() {
  struct Node* main_list = NULL;

  printf("Welcome to linked-list\n");

  while (1) {
    printf("1. List\n");
    printf("2. Create\n");
    printf("3. Update\n");
    printf("4. Delete\n");
    printf("5. Quit\n");

    int main_choice;
    scanf("%d", &main_choice);

    switch (main_choice) {
      case 1:
        print_nodes(main_list);
        break;

      case 2: {
        char* data = scan_str("List: ");

        struct Node* list = malloc(sizeof(struct Node));
        list->next = NULL;
        list->data = data;

        append_node(&main_list, list);
        break;
      }
      case 3: {
        int id;
        printf("Select ID: ");
        scanf("%d", &id);
        struct Node* selected = jump_to(main_list, id - 1);
        if (selected == NULL) {
          printf("Invalid ID\n");
          break;
        }

        printf("List: %s\n", selected->data);
        char* data = scan_str("Update List: ");

        struct Node* updated_list = malloc(sizeof(struct Node));
        updated_list->next = NULL;
        updated_list->data = data;

        char* result = update_node(&main_list, id - 1, updated_list);
        print_label(result);
        break;
      }
      case 4: {
        int id;
        printf("Select ID: ");
        scanf("%d", &id);
        struct Node* selected = jump_to(main_list, id - 1);
        if (selected == NULL) {
          printf("Invalid ID\n");
          break;
        }

        printf("List: %s\n", selected->data);
        char* confirmation = scan_str("Are you sure to delete this list? (Y/n): ");
        if (tolower(confirmation[0]) == 'y' || strcmp(confirmation, "") == 0) {
          char* result = delete_node(&main_list, id - 1);
          print_label(result);
        }
        break;
      }
      case 5:
        printf("Bye!\n");
        goto end;
      default:
        printf("Invalid choice\n");
        break;
    }
  }

  end:
  every_node(main_list, free_node);
  return 0;
}
