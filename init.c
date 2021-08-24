extern void stdio_init();
extern void pthread_init();

void init() {
    stdio_init();
    pthread_init();
}