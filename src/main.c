#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <screens.h>

void must_init(bool test, const char *description) {
  if (test) {
    return;
  }

  printf("Couldn't initialize %s\n", description);
  exit(1);
}

int main() {
  must_init(al_init(), "engine");
  must_init(al_install_keyboard(), "keyboard");
  must_init(al_init_image_addon(), "image engine");

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  must_init(queue, "queue");

  ALLEGRO_DISPLAY *disp = al_create_display(1920, 1080);
  must_init(disp, "display");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  draw_screen_fn* draw_screen = &draw_game_screen;

  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;

  al_start_timer(timer);

  while (1) {
    al_wait_for_event(queue, &event);

    switch (event.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    case ALLEGRO_EVENT_TIMER:
      redraw = true;
      break;
    }

    if (done) {
      break;
    }

    if (redraw && al_is_event_queue_empty(queue)) {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_flip_display();
      
      draw_screen();

      redraw = false;
    }
  }

  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}
