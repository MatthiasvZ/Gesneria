#include "Petroleum.h"
#include "Application.h"

int main()
{
    PT::setDataDir((std::getenv("HOME") + (std::string)"/.local/share/gesneria").c_str());
    PT::Config cfg {PT::parseConfig()};
    // cfg.vsync = true;

    PT::Window window(cfg);
    PT::initGL(cfg);
    GLEC(glDisable(GL_DEPTH_TEST));
    window.changeTitle("Gesneria");

    Application app(&window);

    float previousTime = glfwGetTime();
    while (window.shouldRun() && app.getState() != APP_STATE_AWAITING_CLOSURE)
    {
        PT::clearScreen();

        float deltaTime = glfwGetTime() - previousTime;
        previousTime = glfwGetTime();

        app.update(deltaTime);

        window.update();
        PT::doEvents();
    }

    return 0;
}
