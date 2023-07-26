#include <exception>
#include <iostream>

#include "Application.h"

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
