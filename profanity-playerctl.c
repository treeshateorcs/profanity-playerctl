#include <playerctl/playerctl.h>
#include <profapi.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void *cb(void *unused) {
  gchar res[1024];
  while (1) {
    PlayerctlPlayer *plctl = playerctl_player_new(NULL, NULL);
    gchar *artist = playerctl_player_get_artist(plctl, NULL);
    gchar *title = playerctl_player_get_title(plctl, NULL);
    sprintf(res, "<presence><status>%s - %s</status></presence>", artist,
            title);
    prof_send_stanza(res);
    struct timespec ts;
    ts.tv_sec = 5;
    ts.tv_nsec = 0;
    nanosleep(&ts, NULL);
  }
}

void prof_on_connect(const char *const account_name,
                     const char *const fulljid) {
  PlayerctlPlayer *plctl = playerctl_player_new(NULL, NULL);
  pthread_t thread;
  if (pthread_create(&thread, NULL, cb, NULL)) {
    fprintf(stderr, "Error creating thread\n");
  }
}
