#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

typedef void (draw_screen_fn)(void);

void load_data_game_screen(ALLEGRO_BITMAP* sprites);
void draw_game_screen(void);
