#pragma once

namespace SOGE
{
    class Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;
        void run();
    };

    Application *CreateApplication();
}