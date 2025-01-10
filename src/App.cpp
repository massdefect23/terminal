#include "App.h"
#include "SplashScreen.h"
#include "MainScreen.h"

#include <ncurses.h>

/**
 * - constructor
 * - destructor
 */
App::App() {}
App::~App() {}

void App::run()
{
    /**
     * initialise ncurses
     */
    initscr();
    start_color();
    noecho();
    curs_set(0);                        // hide cursor
    keypad(stdscr, true);               // enable arrow keys
    mousemask(ALL_MOUSE_EVENTS, NULL);  // enable mouse clicks

    /**
     * set up colour pairs
     */
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); 
    init_pair(2, COLOR_GREEN,  COLOR_BLACK);
    init_pair(3, COLOR_RED,    COLOR_BLACK);
    init_pair(4, COLOR_CYAN,   COLOR_BLACK);
    init_pair(5, COLOR_WHITE,  COLOR_BLACK);
    init_pair(6, COLOR_WHITE,  COLOR_BLACK);

    /**
     * main loop of states
     */
        bool running = true;
    AppState state = AppState::SPLASH;

    while (running) {
        switch (state) {
            case AppState::SPLASH: {
                // Show splash animation
                clear();
                refresh();
                SplashScreen::playSplashAnimation();
                bool proceed = SplashScreen::waitForButtonOrEnter();
                if (proceed) {
                    state = AppState::MAIN; 
                } else {
                    state = AppState::MAIN; // fallback
                }
                break;
            }

            case AppState::MAIN: {
                // Show main "Bloomberg-like" screen
                MainScreen::drawMainScreen();

                // Wait for user input in main loop
                bool inMain = true;
                while (inMain) {
                    int ch = getch();
                    switch(ch) {
                        case 'q':
                        case 'Q':
                            running = false;
                            inMain = false;
                            break;
                        case KEY_RESIZE:
                            MainScreen::drawMainScreen();
                            break;
                        default:
                            // ignore
                            break;
                    }
                }
                break;
            }
        } // switch

        if (!running) {
            break;
        }
    }

    // Cleanup
    endwin();
}