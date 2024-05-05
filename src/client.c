#include "game.h"
#include "game_cli_renderer.h"
#include "client.h"

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void configure_console_settings(struct termios *oldt, struct termios *newt)
{
    tcgetattr(STDIN_FILENO, oldt);
    *newt = *oldt;
    newt->c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, newt);
}

void restore_console_settings(struct termios *oldt)
{
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);
}

int main(int argc, char *argv[])
{
    game_t *p_game;
    struct player my_player;
    static struct termios oldt, newt;
    int input;

    if (argc < 2)
    {
        printf("You must provide your username as a CLI argument");
        return 1;
    }
    if (strlen(argv[1]) >= MAX_PLAYER_NAME - 1)
    {
        printf("Your username must have at most %d characters", MAX_PLAYER_NAME - 1);
        return 1;
    }
    configure_console_settings(&oldt, &newt);

    p_game = game_new(10, 10);
    my_player.id = 0;
    my_player.pos_x = 0;
    my_player.pos_y = 0;
    strncpy(my_player.name, argv[1], MAX_PLAYER_NAME);
    game_add_my_player(p_game, my_player);

    while (1)
    {
        game_render(p_game);
        input = getchar();

        if (input == ESCAPE_ARROW_KEYS)
        {
            getchar();
            input = getchar();
            switch (input)
            {
            case ARROW_KEY_DOWN:
                game_move_my_player(p_game, MOVE_DOWN);
                break;
            case ARROW_KEY_UP:
                game_move_my_player(p_game, MOVE_UP);
                break;
            case ARROW_KEY_LEFT:
                game_move_my_player(p_game, MOVE_LEFT);
                break;
            case ARROW_KEY_RIGHT:
                game_move_my_player(p_game, MOVE_RIGHT);
                break;
            default:
                break;
            }
        }
        else if ('A' <= input && input <= 'z')
            game_type_character(p_game, input);
        else if (input == KEY_DEL)
            game_erase_character(p_game);
        else if (input == KEY_ENTER)
            game_send_message(p_game);
    }

    game_free(p_game);

    restore_console_settings(&oldt);

    return 0;
}