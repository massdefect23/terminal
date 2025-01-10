#ifndef APP_H
#define APP_H

enum class AppState
{
    SPLASH,
    MAIN
};

class App
{
    public:
        App();
        ~App();

        /**
         * main entry point
         */
        void run();
};



#endif // APP_H
