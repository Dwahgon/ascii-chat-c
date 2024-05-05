#ifndef GAME_H
#define GAME_H

#include "list.h"

#include <stddef.h>

#define MAX_MESSAGES 100
#define MAX_MESSAGE_SIZE 100
#define MAX_PLAYER_NAME 16
#define MESSAGES_LINES 5

#define MOVE_RIGHT 0
#define MOVE_UP 1
#define MOVE_LEFT 2
#define MOVE_DOWN 3

struct player
{
    unsigned long id;
    unsigned short pos_x, pos_y;
    char name[MAX_PLAYER_NAME];
};

typedef struct
{
    list_t *players;
    struct player *my_player;

    unsigned short size_x, size_y;

    list_t *messages;

    char typing_message[MAX_MESSAGE_SIZE];
} game_t;

game_t *game_new(size_t size_x, size_t size_y);
void game_add_message(game_t *game, char *message);
void game_send_message(game_t *game);
void game_type_character(game_t *game, char character);
void game_erase_character(game_t *game);
void game_move_player(game_t *game, unsigned long player_id, unsigned short new_pos_x, unsigned short new_pos_y);
void game_move_my_player(game_t *game, short direction);
void game_add_player(game_t *game, struct player player);
void game_add_my_player(game_t *game, struct player player);
void game_free(game_t *game);

#endif