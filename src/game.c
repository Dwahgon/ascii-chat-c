#include "game.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>

game_t *game_new(size_t size_x, size_t size_y)
{
    game_t *p_game = (game_t *)malloc(sizeof(game_t));
    p_game->messages = list_new();
    p_game->players = list_new();
    p_game->my_player = NULL;
    p_game->size_x = size_x;
    p_game->size_y = size_y;
    strcpy(p_game->typing_message, "");
    return p_game;
}

void game_add_message(game_t *game, char *message)
{
    size_t message_size = strlen(message);
    size_t data_size = MIN(MAX_MESSAGE_SIZE, message_size) * sizeof(char);

    /* Truncate message */
    if (message_size >= MAX_MESSAGE_SIZE)
        message[MAX_MESSAGE_SIZE - 1] = '\0';

    /* Remove oldest message if max messages reached */
    if (game->messages->length == MAX_MESSAGES)
        list_remove(game->messages, 0);

    list_push_end(game->messages, message, data_size);
}

void game_send_message(game_t *game)
{
    game_add_message(game, game->typing_message);
    game->typing_message[0] = '\0';
}

void game_type_character(game_t *game, char character)
{
    size_t char_i = strlen(game->typing_message);
    if (char_i >= MAX_MESSAGE_SIZE)
        return;
    game->typing_message[char_i] = character;
    game->typing_message[char_i + 1] = '\0';
}

void game_erase_character(game_t *game)
{
    size_t typing_message_len = strlen(game->typing_message);
    if (typing_message_len != 0)
        game->typing_message[typing_message_len - 1] = '\0';
}
void game_move_player(game_t *game, unsigned long player_id, unsigned short new_pos_x, unsigned short new_pos_y)
{
    struct list_node *p_player_node = game->players->p_start;
    while (p_player_node != NULL && ((struct player *)p_player_node->data)->id != player_id)
        p_player_node = p_player_node->p_next;
    if (p_player_node == NULL)
        return;
    ((struct player *)p_player_node->data)->pos_x = new_pos_x;
    ((struct player *)p_player_node->data)->pos_y = new_pos_y;
}

void game_move_my_player(game_t *game, short direction)
{
    direction = direction % 4;
    game->my_player->pos_x = modulus((int)game->my_player->pos_x + (direction == MOVE_RIGHT) - (direction == MOVE_LEFT), game->size_x);
    game->my_player->pos_y = modulus((int)game->my_player->pos_y + (direction == MOVE_DOWN) - (direction == MOVE_UP), game->size_y);
}

void game_add_player(game_t *game, struct player player)
{
    list_push_end(game->players, &player, sizeof(struct player));
}

void game_add_my_player(game_t *game, struct player player)
{
    if (game->my_player != NULL)
        return;
    game_add_player(game, player);
    game->my_player = (struct player *)list_at(game->players, game->players->length - 1);
}

void game_free(game_t *game)
{
    list_free(game->messages);
    list_free(game->players);
    free(game);
}