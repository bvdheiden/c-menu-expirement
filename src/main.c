#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "main.h"

#define ROOT_MENU 0x00

#define RADIO_MENU 0x10

#define ALARM_MENU 0x20
#define ALARM_SET_MENU 0x21
#define ALARM_REMOVE_MENU 0x22

#define CONFIG_MENU 0x30

int main()
{
    // menu setup

    menu_node_t root = init_menu(ROOT_MENU, MENU, "ROOT");
    menu_node_t radio = init_menu(RADIO_MENU, MENU, "RADIO");
    menu_node_t alarm = init_menu(ALARM_MENU, MENU, "ALARM");
    menu_node_t alarm_set = init_menu(ALARM_SET_MENU, ITEM, "SET");
    menu_node_t alarm_remove = init_menu(ALARM_REMOVE_MENU, ITEM, "REMOV");
    menu_node_t config = init_menu(CONFIG_MENU, MENU, "CONFG");

    menu_node_t *current_menu = &root;

    add_item(&root, &radio);
    add_item(&root, &alarm);
    add_item(&root, &config);

    add_item(&alarm, &alarm_set);
    add_item(&alarm, &alarm_remove);

    char command;

    while (command != 'q')
    {
        print_menu(current_menu);
        fflush(stdout);

        command = getchar();

        if (command == 'w')
        {
            previous(current_menu);
        }
        else if (command == 's')
        {
            next(current_menu);
        }
        else if (command == 'a')
        {
            current_menu = deselect(current_menu);
        }
        else if (command == 'd')
        {
            current_menu = select(current_menu);
        }
    }
}