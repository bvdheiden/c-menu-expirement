#ifndef MENU_H
#define MENU_H

typedef enum menu_node_type
{
    ITEM,
    MENU
} menu_node_type_t;

typedef struct menu_node
{
    int id;
    char text[5];
    menu_node_type_t type;

    struct menu_node *prev;
    struct menu_node *next;
    struct menu_node *parent;
    struct menu_node *child;
    int *curr_child_id;
} menu_node_t;

void print_menu(menu_node_t *menu);
menu_node_t init_menu(int id, menu_node_type_t type, const char *text);
void add_item(menu_node_t *menu, menu_node_t *item);
menu_node_t *find(menu_node_t *menu, int id);
menu_node_t *get_current(menu_node_t *menu);
void previous(menu_node_t *menu);
void next(menu_node_t *menu);
menu_node_t *select(menu_node_t *menu);
menu_node_t *deselect(menu_node_t *menu);

#endif