#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void update_scr(int kills1, int kills2, int wins1, int wins2, int losses1, int losses2, int deaths1, int deaths2) {
  int kills = kills2 - kills1;
  int wins = wins2 - wins1;
  double losses = losses2 - losses1;
  double deaths = deaths2 - deaths1;

  double kdr;
  if (deaths == 0) {
    kdr = kills;
  } else {
    kdr = kills / deaths; 
  }

  double winloss;
  if (losses == 0) {
    winloss = wins;
  } else {
    winloss = wins / losses; 
  }

  mvprintw(0, 0, " Lab Skywars Session Tracking");
  mvprintw(1, 0, " ");
  mvprintw(2, 0, " Session Kills: %d", kills);
  mvprintw(3, 0, " Session Wins: %d", wins);

  if (kdr >= 5) {
    mvprintw(4, 0, " Session K/D: ");
    attron(COLOR_PAIR(1));
    mvprintw(4, 14, "%.2f", kdr);
    attroff(COLOR_PAIR(1));
  } else {
    mvprintw(4, 0, " Session K/D: %.2f", kdr);
  }

  if (winloss >= 1) {
    mvprintw(5, 0, " Session W/L: ");
    attron(COLOR_PAIR(1));
    mvprintw(5, 14, "%.2f", winloss);
    attroff(COLOR_PAIR(1));
  } else {
    mvprintw(5, 0, " Session WL: %.2f", winloss);
  }

  mvprintw(6, 0, " ");
  mvprintw(7, 0, " Most Recent Map Played: ");
}

int main() {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  cbreak();
  timeout(5000);

  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color.\n");
    exit(1);
  }

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  while(1) {
    update_scr(2300, 2343, 200, 215, 38, 42, 37, 41);
    refresh();

    int a = getch();
    switch (a) {
      case 'q':
        endwin();
        exit(1);
    }
  }

  return 0;
}

