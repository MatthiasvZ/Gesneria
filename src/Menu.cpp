#include "Menu.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../assets/menu/menuAtlas.png.h"

#define TOTAL_SELECTIONS 3
#define SELECTION_NONE      0
#define SELECTION_PLAY_GAME 1
#define SELECTION_OPTIONS   2
#define SELECTION_QUIT_GAME 3

#define LOGO 0
#define CORNER_BOTTOM_LEFT  0
#define CORNER_TOP_LEFT     1
#define CORNER_TOP_RIGHT    2
#define CORNER_BOTTOM_RIGHT 3

#define MAIN_SELECTIONS_INIT_LEFT_X   (0.4f * aspectRatio)
#define MAIN_SELECTIONS_INIT_RIGHT_X  MAIN_SELECTIONS_INIT_LEFT_X + 0.5f
#define MAIN_SELECTIONS_TOP_Y    -0.2f // The top of the topmost selection
#define MAIN_SELECTIONS_BOTTOM_Y -0.3f // The bottom of the topmost selection
#define MAIN_SELECTIONS_DISTANCE 0.15f
#define MAIN_SELECTIONS_CURRENT_LEFT_X              (vertices[0])
#define MAIN_SELECTIONS_CURRENT_RIGHT_X             (vertices[8])
#define MAIN_SELECTIONS_CURRENT_TOP_Y(SELECTION)    (vertices[5] - (SELECTION - 1) * MAIN_SELECTIONS_DISTANCE)
#define MAIN_SELECTIONS_CURRENT_BOTTOM_Y(SELECTION) (vertices[1] - (SELECTION - 1) * MAIN_SELECTIONS_DISTANCE)

#define LOGO_INIT_LEFT_X  -0.75f
#define LOGO_INIT_RIGHT_X  0.75f
#define LOGO_INIT_TOP_Y    0.9f
#define LOGO_INIT_BOTTOM_Y 0.5f
#define LOGO_CURRENT_LEFT_X   (vertices[4 * 4 * TOTAL_SELECTIONS])
#define LOGO_CURRENT_RIGHT_X  (vertices[4 * 4 * TOTAL_SELECTIONS + 8])
#define LOGO_CURRENT_BOTTOM_Y (vertices[4 * 4 * TOTAL_SELECTIONS + 1])
#define LOGO_CURRENT_TOP_Y    (vertices[4 * 4 * TOTAL_SELECTIONS + 5])

#define ANIMATION_NONE           0
#define ANIMATION_MOVE_OFFSCREEN 1
#define ANIMATION_MOVE_IN        2

constexpr float getTexCoordX(const unsigned int element, const unsigned int corner)
{
    if (element == LOGO)
        switch (corner)
        {
            case CORNER_BOTTOM_LEFT: [[fallthrough]];
            case CORNER_TOP_LEFT:
                return 0.0f;
                break;
            case CORNER_BOTTOM_RIGHT: [[fallthrough]];
            case CORNER_TOP_RIGHT:
                return 1.0f;
                break;
        }

    return (element - 1) % 3 / 3.0f + (corner == CORNER_BOTTOM_LEFT || corner == CORNER_TOP_LEFT ? 0.0f : 1.0f / 3.0f);
}

constexpr float getTexCoordY(const unsigned int element, const unsigned int corner)
{
    if (element == LOGO)
        switch (corner)
        {
            case CORNER_BOTTOM_LEFT: [[fallthrough]];
            case CORNER_BOTTOM_RIGHT:
                return 2.0f / 6.0f;
                break;
            case CORNER_TOP_LEFT: [[fallthrough]];
            case CORNER_TOP_RIGHT:
                return 1.0f;
                break;
        }

    return (element >= 4 ? 0.0f : 1.0f / 6.0f) + (corner == CORNER_BOTTOM_LEFT || corner == CORNER_BOTTOM_RIGHT ? 0.0f : 1.0f / 6.0f);
}

inline std::vector<float> vertexPositions(float aspectRatio)
{
    return
    {
        /* X                          Y                                                        U                                                       V     */
        // Start game
        MAIN_SELECTIONS_INIT_LEFT_X,  MAIN_SELECTIONS_BOTTOM_Y,                                getTexCoordX(SELECTION_PLAY_GAME, CORNER_BOTTOM_LEFT),  getTexCoordY(SELECTION_PLAY_GAME, CORNER_BOTTOM_LEFT),
        MAIN_SELECTIONS_INIT_LEFT_X,  MAIN_SELECTIONS_TOP_Y,                                   getTexCoordX(SELECTION_PLAY_GAME, CORNER_TOP_LEFT),     getTexCoordY(SELECTION_PLAY_GAME, CORNER_TOP_LEFT),
        MAIN_SELECTIONS_INIT_RIGHT_X, MAIN_SELECTIONS_TOP_Y,                                   getTexCoordX(SELECTION_PLAY_GAME, CORNER_TOP_RIGHT),    getTexCoordY(SELECTION_PLAY_GAME, CORNER_TOP_RIGHT),
        MAIN_SELECTIONS_INIT_RIGHT_X, MAIN_SELECTIONS_BOTTOM_Y,                                getTexCoordX(SELECTION_PLAY_GAME, CORNER_BOTTOM_RIGHT), getTexCoordY(SELECTION_PLAY_GAME, CORNER_BOTTOM_RIGHT),

        // Options
        MAIN_SELECTIONS_INIT_LEFT_X,  MAIN_SELECTIONS_BOTTOM_Y - 1 * MAIN_SELECTIONS_DISTANCE, getTexCoordX(SELECTION_OPTIONS, CORNER_BOTTOM_LEFT),  getTexCoordY(SELECTION_PLAY_GAME, CORNER_BOTTOM_LEFT),
        MAIN_SELECTIONS_INIT_LEFT_X,  MAIN_SELECTIONS_TOP_Y - 1 * MAIN_SELECTIONS_DISTANCE,    getTexCoordX(SELECTION_OPTIONS, CORNER_TOP_LEFT),     getTexCoordY(SELECTION_PLAY_GAME, CORNER_TOP_LEFT),
        MAIN_SELECTIONS_INIT_RIGHT_X, MAIN_SELECTIONS_TOP_Y - 1 * MAIN_SELECTIONS_DISTANCE,    getTexCoordX(SELECTION_OPTIONS, CORNER_TOP_RIGHT),    getTexCoordY(SELECTION_PLAY_GAME, CORNER_TOP_RIGHT),
        MAIN_SELECTIONS_INIT_RIGHT_X, MAIN_SELECTIONS_BOTTOM_Y - 1 * MAIN_SELECTIONS_DISTANCE, getTexCoordX(SELECTION_OPTIONS, CORNER_BOTTOM_RIGHT), getTexCoordY(SELECTION_PLAY_GAME, CORNER_BOTTOM_RIGHT),

        // Quit game
        MAIN_SELECTIONS_INIT_LEFT_X,  MAIN_SELECTIONS_BOTTOM_Y - 2 * MAIN_SELECTIONS_DISTANCE, getTexCoordX(SELECTION_QUIT_GAME, CORNER_BOTTOM_LEFT),  getTexCoordY(SELECTION_PLAY_GAME, CORNER_BOTTOM_LEFT),
        MAIN_SELECTIONS_INIT_LEFT_X,  MAIN_SELECTIONS_TOP_Y - 2 * MAIN_SELECTIONS_DISTANCE,    getTexCoordX(SELECTION_QUIT_GAME, CORNER_TOP_LEFT),     getTexCoordY(SELECTION_PLAY_GAME, CORNER_TOP_LEFT),
        MAIN_SELECTIONS_INIT_RIGHT_X, MAIN_SELECTIONS_TOP_Y - 2 * MAIN_SELECTIONS_DISTANCE,    getTexCoordX(SELECTION_QUIT_GAME, CORNER_TOP_RIGHT),    getTexCoordY(SELECTION_PLAY_GAME, CORNER_TOP_RIGHT),
        MAIN_SELECTIONS_INIT_RIGHT_X, MAIN_SELECTIONS_BOTTOM_Y - 2 * MAIN_SELECTIONS_DISTANCE, getTexCoordX(SELECTION_QUIT_GAME, CORNER_BOTTOM_RIGHT), getTexCoordY(SELECTION_PLAY_GAME, CORNER_BOTTOM_RIGHT),

        // Logo
        LOGO_INIT_LEFT_X,  LOGO_INIT_BOTTOM_Y, getTexCoordX(LOGO, CORNER_BOTTOM_LEFT),  getTexCoordY(LOGO, CORNER_BOTTOM_LEFT),
        LOGO_INIT_LEFT_X,  LOGO_INIT_TOP_Y,    getTexCoordX(LOGO, CORNER_TOP_LEFT),     getTexCoordY(LOGO, CORNER_TOP_LEFT),
        LOGO_INIT_RIGHT_X, LOGO_INIT_TOP_Y,    getTexCoordX(LOGO, CORNER_TOP_RIGHT),    getTexCoordY(LOGO, CORNER_TOP_RIGHT),
        LOGO_INIT_RIGHT_X, LOGO_INIT_BOTTOM_Y, getTexCoordX(LOGO, CORNER_BOTTOM_RIGHT), getTexCoordY(LOGO, CORNER_BOTTOM_RIGHT)
    };
}

// TODO remove
#define MENU_BACKGROUND_LENGTH MENU_ATLAS_LENGTH
#define MENU_BACKGROUND MENU_ATLAS


Menu::Menu(PT::Window* p_Window)
    : shader(PT_SHADER_XYUV_M),
      vertices(vertexPositions(1.0f)), vbo(vertices), ibo(PT::tIndsSquares<unsigned char>(vertices.size() / 8)),
      backgroundVbo(std::vector<float>({
        -2.0f, -1.0f, 0.0f, 0.0f,
        -2.0f,  1.0f, 0.0f, 1.0f,
         2.0f,  1.0f, 1.0f, 1.0f,
         2.0f, -1.0f, 1.0f, 0.0f
      })), backgroundIbo(PT::tIndsSquares<unsigned char>(1)), p_Window(p_Window),
      tex_menuAtlas(MENU_ATLAS_LENGTH, MENU_ATLAS, 0, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR), tex_menuBackground(MENU_BACKGROUND_LENGTH, MENU_BACKGROUND, 1),
      aspectRatio(1.0f), state(MAIN_SCREEN), nextState(NONE), deltaTime(0.0f), animationPlaying(false)

{
    vao.addBuffer(vbo, shader.getLayout());
    backgroundVao.addBuffer(backgroundVbo, shader.getLayout());
    GLEC(glClearColor(0.265625f, 0.4375f, 0.3203125f, 1.0f));
    glm::mat4 scaleMat = glm::scale(glm::vec3(1.0f / aspectRatio, 1.0f, 1.0f));
    shader.setUniformMat4f("u_Mat", scaleMat);
}

void Menu::update(float deltaTime)
{
    this->deltaTime = deltaTime;

    GLEC(glGetFloatv(GL_VIEWPORT, vp));
    if (aspectRatio != vp[2] / vp[3])
    {
        float newAspectRatio = vp[2] / vp[3];
        for (unsigned long int i {0}; i < 4 * 4 * TOTAL_SELECTIONS; i += 4)
        {
            vertices[i] += newAspectRatio - aspectRatio;
        }
        for (unsigned long int i {4 * 4 * TOTAL_SELECTIONS}; i < 4 * 4 * (TOTAL_SELECTIONS + 1); i += 4)
        {
            vertices[i] -= newAspectRatio - aspectRatio;
        }
        vbo.updateData(vertices);

        aspectRatio = newAspectRatio;
        glm::mat4 scaleMat = glm::scale(glm::vec3(1.0f / aspectRatio, 1.0f, 1.0f));
        shader.setUniformMat4f("u_Mat", scaleMat);
    }

    switch (animationPlaying)
    {
        case ANIMATION_NONE:
            switch (state)
            {
                case MAIN_SCREEN:
                    switch (mouseOn())
                    {
                        case SELECTION_PLAY_GAME:
                            animation_Highlight(SELECTION_PLAY_GAME);
                            if (p_Window->getMouseButton(GLFW_MOUSE_BUTTON_1) == true)
                            {
                                nextState = WAITING_TO_BEGIN_GAME;
                                animation_MoveOffscreen();
                            }
                            break;
                        case SELECTION_OPTIONS:
                            animation_Highlight(SELECTION_OPTIONS);
                            if (p_Window->getMouseButton(GLFW_MOUSE_BUTTON_1) == true)
                            {
                                nextState = OPTION_MENU;
                                animation_MoveOffscreen();
                            }
                            break;
                        case SELECTION_QUIT_GAME:
                            animation_Highlight(SELECTION_QUIT_GAME);
                            if (p_Window->getMouseButton(GLFW_MOUSE_BUTTON_1) == true)
                                state = WAITING_TO_CLOSE;
                            break;
                    }
                    if (ActiveHighlight != mouseOn())
                        animation_UnHighlight(ActiveHighlight);
                    break;
                case OPTION_MENU:
                    // TODO
                    nextState = MAIN_SCREEN;
                    animation_MoveIn();
                    break;
            }
            break;
        case ANIMATION_MOVE_OFFSCREEN:
            animation_MoveOffscreen();
            break;
        case ANIMATION_MOVE_IN:
            animation_MoveIn();
            break;
    }

    shader.setUniform1i("texSlot", 1);
    // PT::drawVA(backgroundVao, backgroundIbo, shader);
    shader.setUniform1i("texSlot", 0);
    PT::drawVA(vao, ibo, shader);
}

unsigned int Menu::mouseOn()
{
    if (animationPlaying)
        return SELECTION_NONE;

    double mouseX, mouseY;
    p_Window->getCursorPos(&mouseX, &mouseY);
    double cursorX {(mouseX / vp[2]  * 2 - 1) * aspectRatio};
    double cursorY {(-mouseY / vp[3]  * 2 + 1)};

    for (unsigned int selection {1}; selection <= TOTAL_SELECTIONS; ++selection)
        if (cursorX > MAIN_SELECTIONS_CURRENT_LEFT_X && cursorX < MAIN_SELECTIONS_CURRENT_RIGHT_X &&
            cursorY > MAIN_SELECTIONS_CURRENT_BOTTOM_Y(selection) && cursorY < MAIN_SELECTIONS_CURRENT_TOP_Y(selection))
            return selection;
    return SELECTION_NONE;
}

#define ANIMATION_DELAY 0.4f
void Menu::animation_MoveOffscreen()
{
    animationPlaying = ANIMATION_MOVE_OFFSCREEN;

    if (!(MAIN_SELECTIONS_CURRENT_LEFT_X > aspectRatio + ANIMATION_DELAY))
        for (long unsigned int i {0}; i < 4 * 4 * TOTAL_SELECTIONS; i += 4)
            vertices[i] += 1.6f * deltaTime * aspectRatio;

    if (!(LOGO_CURRENT_RIGHT_X < -aspectRatio - ANIMATION_DELAY))
        for (long unsigned int i {4 * 4 * TOTAL_SELECTIONS}; i < 4 * 4 * (TOTAL_SELECTIONS + 1); i += 4)
            vertices[i] -= 2.6f * deltaTime * aspectRatio;

    vbo.updateData(vertices);

    if (MAIN_SELECTIONS_CURRENT_LEFT_X > aspectRatio + ANIMATION_DELAY && LOGO_CURRENT_RIGHT_X < -aspectRatio - ANIMATION_DELAY)
    {
        state = nextState;
        animationPlaying = false;
    }
}

void Menu::animation_MoveIn()
{
    animationPlaying = ANIMATION_MOVE_IN;

    if (!(MAIN_SELECTIONS_CURRENT_LEFT_X <= MAIN_SELECTIONS_INIT_LEFT_X))
        for (long unsigned int i {0}; i < 4 * 4 * TOTAL_SELECTIONS; i += 4)
            vertices[i] -= 1.6f * deltaTime * aspectRatio;

    if (!(LOGO_CURRENT_RIGHT_X >= LOGO_INIT_RIGHT_X))
        for (long unsigned int i {4 * 4 * TOTAL_SELECTIONS}; i < 4 * 4 * (TOTAL_SELECTIONS + 1); i += 4)
            vertices[i] += 2.6f * deltaTime * aspectRatio;

    vbo.updateData(vertices);

    if (MAIN_SELECTIONS_CURRENT_LEFT_X <= MAIN_SELECTIONS_INIT_LEFT_X && LOGO_CURRENT_RIGHT_X >= LOGO_INIT_RIGHT_X)
    {
        state = nextState;
        animationPlaying = false;
    }
}

#define HIGHLIGHT_AMOUNT 0.01f
void Menu::animation_Highlight(unsigned int option)
{
    if (ActiveHighlight == option)
        return;

    vertices[16 * (option - 1)  + 0]  -= HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 1]  -= HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 4]  -= HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 5]  += HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 8]  += HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 9]  += HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 12] += HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 13] -= HIGHLIGHT_AMOUNT;

    vbo.updateData(vertices);
    ActiveHighlight = option;
}

void Menu::animation_UnHighlight(unsigned int option)
{
    if (ActiveHighlight != option || !ActiveHighlight)
        return;

    vertices[16 * (option - 1)  + 0] += HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 1]  += HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 4]  += HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 5]  -= HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 8]  -= HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 9]  -= HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 12] -= HIGHLIGHT_AMOUNT;
    vertices[16 * (option - 1)  + 13] += HIGHLIGHT_AMOUNT;

    vbo.updateData(vertices);
    ActiveHighlight = SELECTION_NONE;
}

Menu::~Menu()
{
    vao.remove();
    vbo.remove();
    ibo.remove();
    backgroundVao.remove();
    backgroundVbo.remove();
    backgroundIbo.remove();
}
