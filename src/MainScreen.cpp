#include "MainScreen.h"
#include <ncurses.h>
#include <string>

namespace MainScreen {

    static void drawLayout();

    void drawMainScreen() {
        clear();
        refresh();
        drawLayout();
    }

    static void drawLayout() {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

        /**
         * top bar in yellow
         */
        attron(COLOR_PAIR(1) | A_BOLD);
        mvhline(0, 0, ' ', max_x);
        std::string topBar = " GME US | -6.81 | 136.50 / 136.66N | 15x3 | Vol 582.304M ";
        if ((int)topBar.size() > max_x) {
            topBar = topBar.substr(0, max_x - 1);
        }
        mvaddstr(0, 0, topBar.c_str());
        attroff(COLOR_PAIR(1) | A_BOLD);

        /**
         * colour highlights 
         */
        attron(COLOR_PAIR(2) | A_BOLD); // green
        mvaddstr(0, 6, "US");
        attroff(COLOR_PAIR(2) | A_BOLD);

        attron(COLOR_PAIR(3) | A_BOLD); // red
        mvaddstr(0, 11, "-6.81");
        attroff(COLOR_PAIR(3) | A_BOLD);

        /**
         * split
         */
        int mainStartY = 1;
        int mainHeight = max_y - mainStartY;
        int leftWidth  = (int)(max_x * 0.6);
        int rightWidth = max_x - leftWidth;

        /**
         * vertical line
         */
        attron(COLOR_PAIR(5) | A_BOLD);
        for (int y = mainStartY; y < max_y; y++) {
            if (leftWidth < max_x) {
                mvaddch(y, leftWidth, '|');
            }
        }
        attroff(COLOR_PAIR(5) | A_BOLD);

        /**
         * message in left pane
         */
        int leftPaneCenterY = mainStartY + mainHeight / 2;
        int leftPaneCenterX = (leftWidth > 0) ? leftWidth / 2 : 0;
        std::string message = "Hello World";
        int msgStartX = leftPaneCenterX - (int)(message.size() / 2);
        if (msgStartX < 0) msgStartX = 0;

        attron(COLOR_PAIR(2) | A_BOLD);
        if (leftPaneCenterY < max_y) {
            mvaddstr(leftPaneCenterY, msgStartX, message.c_str());
        }
        attroff(COLOR_PAIR(2) | A_BOLD);

        /**
         * right pane place holders 
         */
        if (rightWidth > 0) {
            int rightPaneX = leftWidth + 2;

            attron(COLOR_PAIR(1) | A_BOLD);
            if (mainStartY + 2 < max_y)
                mvaddstr(mainStartY + 2, rightPaneX, "Ownership Summary");
            if (mainStartY + 3 < max_y)
                mvaddstr(mainStartY + 3, rightPaneX, "Insider Transactions");
            if (mainStartY + 4 < max_y)
                mvaddstr(mainStartY + 4, rightPaneX, "Options / Issuer Debt");
            attroff(COLOR_PAIR(1) | A_BOLD);

            attron(COLOR_PAIR(2) | A_BOLD);
            if (mainStartY + 6 < max_y)
                mvaddstr(mainStartY + 6, rightPaneX, "Insider - Based on Last 6 Months:");
            if (mainStartY + 7 < max_y)
                mvaddstr(mainStartY + 7, rightPaneX, "  # of Shares Held: 0.86");
            if (mainStartY + 8 < max_y)
                mvaddstr(mainStartY + 8, rightPaneX, "  # of Insiders: 10");
            attroff(COLOR_PAIR(2) | A_BOLD);

            attron(COLOR_PAIR(3) | A_BOLD);
            if (mainStartY + 10 < max_y)
                mvaddstr(mainStartY + 10, rightPaneX, "  # of Sellers Open Mkt: 5");
            if (mainStartY + 11 < max_y)
                mvaddstr(mainStartY + 11, rightPaneX, "  # of Shrs Sold Open Mkt: 5,500");
            attroff(COLOR_PAIR(3) | A_BOLD);
        }

        refresh();
    }

} 