/*https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux*/

#include <termios.h>
#include <stdio.h>

static struct termios old, current;


// Déclaration des fonctions statiques
static void init_terminos(int echo);
static void reset_terminos(void);
static char getch_(int echo);

/* Initialize new terminal i/o settings */
static void init_terminos(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
static void reset_terminos(void)
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
static char getch_(int echo)
{
  char ch;
  init_terminos(echo);
  ch = getchar();
  reset_terminos();
  return ch;
}

// Déclaration fonction publique

/* Read 1 character without echo */
char getch(void)
{
  return getch_(0);
}