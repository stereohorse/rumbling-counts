#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define DISP_W 1920
#define DISP_H 1080

#define BUFFER_W 800
#define BUFFER_H 600

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

  ALLEGRO_DISPLAY *disp = al_create_display(DISP_W, DISP_H);
  must_init(disp, "display");

  ALLEGRO_BITMAP *buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
  must_init(buffer, "buffer");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

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
      al_set_target_bitmap(buffer);

      al_clear_to_color(al_map_rgb(0, 0, 0));

      al_set_target_backbuffer(disp);
      al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

      al_flip_display();

      redraw = false;
    }
  }

  al_destroy_bitmap(buffer);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}
