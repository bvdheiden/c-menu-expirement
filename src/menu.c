#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "menu.h"

/*
 *  Print the menu
 */
void print_menu(menu_node_t *menu)
{
    assert(menu->type == MENU);

    printf("\nMenu output:\n");

    menu_node_t *current = menu->child;
    while (current != NULL)
    {
        if (current->id == *menu->curr_child_id)
        {
            printf(">%s id:%d\n", current->text, current->id);
        }
        else
        {
            printf("|%s id:%d\n", current->text, current->id);
        }
        current = current->next;
    }

    printf("\n");
}

/*
 *  Initialize a new menu item
 */
menu_node_t init_menu(int id, menu_node_type_t type, const char *text)
{
    menu_node_t menu = {
        .id = id,
        .type = type,
        .prev = NULL,
        .next = NULL,
        .parent = NULL,
        .child = NULL};

    memcpy(menu.text, text, 5);

    return menu;
}

/*
 *  Add an item to the menu
 */
void add_item(menu_node_t *menu, menu_node_t *item)
{
    assert(menu->type == MENU);

    if (menu->child == NULL)
    {
        // add new child
        menu->child = item;
        menu->curr_child_id = &item->id;

        item->parent = menu;
    }
    else
    {
        menu_node_t *current = menu->child;

        // traverse to end of linked list
        while (current->next != NULL)
        {
            current = current->next;
        }

        // add new child to end of linked list
        current->next = item;
        item->prev = current;
        item->parent = menu;
    }
}

/*
 *  Get a pointer to the menu item matching the id
 */
menu_node_t *find(menu_node_t *menu, int id)
{
    assert(menu->type == MENU);

    menu_node_t *current = menu->child;

    // traverse to end of linked list
    while (current != NULL)
    {
        if (current->id == id)
            return current;

        current = current->next;
    }

    return NULL;
}

/*
 *  Get a pointer to the current menu item
 */
menu_node_t *get_current(menu_node_t *menu)
{
    return find(menu, *menu->curr_child_id);
}

/*
 *  Cycle to the previous item in the menu
 */
void previous(menu_node_t *menu)
{
    assert(menu->type == MENU);

    menu_node_t *current = get_current(menu);
    if (current->prev != NULL)
    {
        printf("cycle to previous id: %d\n", current->prev->id);
        menu->curr_child_id = &current->prev->id;
    }
}

/*
 *  Cycle to the next item in the menu
 */
void next(menu_node_t *menu)
{
    assert(menu->type == MENU);

    menu_node_t *current = get_current(menu);
    if (current->next != NULL)
    {
        printf("cycle to next id: %d\n", current->next->id);
        menu->curr_child_id = &current->next->id;
    }
}

menu_node_t *select(menu_node_t *menu)
{
    menu_node_t *current_child = get_current(menu);

    if (current_child != NULL && current_child->type == MENU)
    {
        printf("selecting id: %d\n", current_child->id);
        return current_child;
    }
    else
    {
        return menu;
    }
}

menu_node_t *deselect(menu_node_t *menu)
{
    if (menu->parent != NULL)
    {
        printf("deselecting id: %d\n", menu->id);
        return menu->parent;
    }
    else
    {
        return menu;
    }
}