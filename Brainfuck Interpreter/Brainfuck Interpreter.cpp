#include "App.h"

int main(int argc, char* argv[])
{
    BFI::App app(argv[1]);
    app.run();
    return 0;
}
