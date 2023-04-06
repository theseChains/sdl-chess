#include "Application.h"

#include <iostream>
#include <exception>

int main()
{
    try
    {
        Application application{};
        application.run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "exception: " << exception.what() << '\n';
    }

    return 0;
}
