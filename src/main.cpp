
#include "Application.h"

int main(int argc, char **argv)
{
    Application app;

    if (!app.Init("Test Application"))
    {
        return 0;
    }

    app.Run();

    return 0;
}
