#ifndef TILES_H
#define TILES_H

#include <stdbool.h>

typedef struct Tilemap {
    char* version;
    char* tiled_version;
    char* orientation;
    char* render_order;
    unsigned short w;
    unsigned short h;
    unsigned short tile_w;
    unsigned short tile_h;
    bool infinite;
} Tilemap;

#endif
