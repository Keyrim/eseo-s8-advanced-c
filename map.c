// External include
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "config.h"
#include "string.h"

// Internal include
#include "map.h"

// Config
#define MAP_NB_LINE    MAP_HEIGHT
#define MAP_NB_COLUMN   MAP_WIDTH

// Grille de jeu
static char** map = NULL;

void map_init(void)
{
    // Allocation mémoire
    map = (char **)malloc(MAP_NB_LINE * sizeof(char *));
    for (int i = 0; i < MAP_NB_LINE; i++)
    {
        map[i] = (char *)malloc(MAP_NB_COLUMN * sizeof(char));
    }

    // Remplit la map avec des espaces
    for(int i=0; i<MAP_NB_LINE; i++)
    {
        for(int j=0; j<MAP_NB_COLUMN; j++)
        {
            map[i][j] = ' ';
        }
    }
}

void map_print(void)
{
    // Nettoyage de la console
    system("clear");

    for(int j= 0; j<MAP_NB_LINE; j++)
    {
        //ligne de delimitation
        for(int i=0; i<MAP_NB_COLUMN; i++)
        {
            printf("+---");
        }
        printf("+\n");

        //ligne de contenu
        for(int i=0; i<MAP_NB_COLUMN; i++)
        {
            printf("| %c ",map[j][i]); //contenu
        }
        printf("|\n");
    }

    //ligne de delimitation
    for(int i=0; i<MAP_NB_COLUMN; i++)
    {
        printf("+---");
    }
    printf("+\n");
}

char map_get_char(coordinate_t coordinate)
{
    return map[coordinate.y][coordinate.x];
}

void map_set_car(char c, coordinate_t coordinate)
{
    map[coordinate.y][coordinate.x] = c;
}

void map_get_size(uint8_t* nb_column, uint8_t* nb_ligne)
{
    *nb_column = MAP_NB_COLUMN;
    *nb_ligne = MAP_NB_LINE;
}

void map_clear(void)
{
    uint8_t line = MAP_NB_LINE;
    while(line--)
    {
        memset(map[line], ' ', MAP_NB_COLUMN);
    }
}
