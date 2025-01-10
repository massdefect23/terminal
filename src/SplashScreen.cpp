#include "SplashScreen.h"
#include <ncurses.h>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>

namespace SplashScreen {

    /**
     * animate single row welcome message
     */
    void playSplashAnimation() {
        clear();
        refresh();

        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

        std::string text = "WELCOME TO THE TERMINAL";
        int textLen = (int)text.size();

        int centerY = max_y / 2;
        int centerX = (max_x - textLen) / 2;
        if (centerX < 0) centerX = 0;

        int delayMs = 40; // type speed
        attron(A_BOLD | COLOR_PAIR(6));
        for (int i = 0; i < textLen; i++) {
            mvaddch(centerY, centerX + i, text[i]);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
        attroff(A_BOLD | COLOR_PAIR(6));
        refresh();

        // short ellipsis
        int64_t startTime = (int64_t)time(nullptr);
        int64_t duration  = 1; // second
        int dotX = centerX + textLen + 1;
        int dotY = centerY;

        while (((int64_t)time(nullptr) - startTime) < duration) {
            for (int dotCount = 1; dotCount <= 3; dotCount++) {
                if (((int64_t)time(nullptr) - startTime) >= duration) break;
                attron(A_BOLD | COLOR_PAIR(6));
                for (int d = 0; d < dotCount; d++) {
                    mvaddch(dotY, dotX + d, '.');
                }
                for (int d = dotCount; d < 3; d++) {
                    mvaddch(dotY, dotX + d, ' ');
                }
                attroff(A_BOLD | COLOR_PAIR(6));
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
            }
        }

        mvaddstr(dotY, dotX, "   ");
        refresh();
    }

    /**
     * wait for the enter or mouse click
     */
    bool waitForButtonOrEnter() {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

        std::string buttonText = "[ ENTER ]";
        int btnWidth  = (int)buttonText.size();
        int btnHeight = 1;

        int btnY = (max_y / 2) + 2;
        if (btnY >= max_y) btnY = max_y - 1;
        int btnX = (max_x - btnWidth) / 2;
        if (btnX < 0) btnX = 0;

        attron(A_BOLD | COLOR_PAIR(2));
        mvaddstr(btnY, btnX, buttonText.c_str());
        attroff(A_BOLD | COLOR_PAIR(2));

        std::string msg = "Click the button or press ENTER to continue...";
        mvaddstr(max_y - 2, 1, msg.c_str());
        refresh();

        int btnXend = btnX + btnWidth;
        int btnYend = btnY + btnHeight;

        while(true) {
            int ch = getch();
            if (ch == '\n' || ch == KEY_ENTER) {
                return true;
            }
            else if (ch == KEY_MOUSE) {
                MEVENT event;
                if (getmouse(&event) == OK) {
                    if (event.bstate & BUTTON1_CLICKED) {
                        int mx = event.x;
                        int my = event.y;
                        if (my >= btnY && my < btnYend &&
                            mx >= btnX && mx < btnXend) {
                            return true;
                        }
                    }
                }
            }
            else if (ch == KEY_RESIZE) {
                // Re-run entire splash on resize
                clear();
                playSplashAnimation();

                getmaxyx(stdscr, max_y, max_x);
                btnX = (max_x - btnWidth) / 2;
                btnY = (max_y / 2) + 2;
                if (btnY >= max_y) btnY = max_y - 1;
                if (btnX < 0) btnX = 0;

                attron(A_BOLD | COLOR_PAIR(2));
                mvaddstr(btnY, btnX, buttonText.c_str());
                attroff(A_BOLD | COLOR_PAIR(2));

                msg = "Click the button or press ENTER to continue...";
                mvaddstr(max_y - 2, 1, msg.c_str());
                refresh();

                btnXend = btnX + btnWidth;
                btnYend = btnY + btnHeight;
            }
        }
        return true;
    }

} 