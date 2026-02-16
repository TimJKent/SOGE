#pragma once
#include "Application.hpp"

extern SOGE::Application *SOGE::CreateApplication();

int main()
{
    auto app = SOGE::CreateApplication();
    app->run();
    delete app;

    return 0;
}