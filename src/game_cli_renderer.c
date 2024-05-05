#include "game.h"
#include "utils.h"

#include <stdio.h>

void game_render_view(game_t *p_game)
{
    int x, y;
    struct list_node *p;
    for (y = 0; y < p_game->size_y; y++)
    {
        for (x = 0; x < p_game->size_y; x++)
        {
            for (p = p_game->players->p_start; p != NULL; p = p->p_next)
            {
                if (((struct player *)p->data)->pos_x == x && ((struct player *)p->data)->pos_y == y)
                {
                    printf(p->data == p_game->my_player ? "@" : "O");
                    goto end;
                }
            }
            printf(".");
        end:;
        }
        printf("\n");
    }
}

void game_render_chat(game_t *p_game)
{
    struct list_node *p_node = p_game->messages->p_end;
    size_t messages_count = MIN(p_game->messages->length, MESSAGES_LINES), i;
    for (i = 0; i < MESSAGES_LINES - 1 && p_node && p_node->p_prev != NULL; i++)
        p_node = p_node->p_prev;

    for (i = 0; i < MESSAGES_LINES; i++)
    {
        if (messages_count + i >= MESSAGES_LINES)
        {
            printf(p_node->data);
            p_node = p_node->p_next;
        }
        printf("\n");
    }

    printf(p_game->typing_message);
}

void game_render(game_t *p_game)
{
    printf("\e[1;1H\e[2J");
    game_render_view(p_game);
    game_render_chat(p_game);
}