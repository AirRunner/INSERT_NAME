#include "systems.hpp"

void systems::updatePos(entt::DefaultRegistry* registry, float deltaTime)
{
    registry->view<position, velocity>().each(
        [deltaTime](auto entity, auto& position, auto& velocity)
        {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
        }
    );
}

void systems::updateAnims(entt::DefaultRegistry* registry, int mode, float deltaTime)
{
    registry->view<anim>().each
    (
        [mode, deltaTime](auto entity, auto& anim)
        {
            anim.index += deltaTime/(anim.animHandle->animTime/anim.animHandle->size);
            if(anim.index > anim.animHandle->size - 1)
            {
                switch(mode)
                {
                    case 1: // Loop mode
                            anim.index = 0;
                        break;
                    case 2: // One Shot mode
                            anim.index = anim.animHandle->size - 1;
                        break;
                    case 3: // Random mode
                            if(rand()%(int)(3000/deltaTime) == 1)
                            {
                                anim.index = 0;
                            }
                            else
                            {
                                anim.index = anim.animHandle->size - 1;
                            }
                        break;
                    default:
                            anim.index = 0;
                        break;
                }
            }
        }
    );
    registry->view<button>().each
    (
     [deltaTime](auto entity, auto& button)
     {
        button.index += deltaTime/(button.animHandle->animTime/button.animHandle->size);
        if(button.index > button.animHandle->size - 1)
            button.index = button.animHandle->size - 1;
        if(button.selected == 0)
            button.index = 0;
     }
    );
}

void systems::updateMusic(entt::DefaultRegistry* registry)
{
    registry->view<bMusic>().each(
        [](auto entity, auto& music)
        {
            UpdateMusicStream(music.musicHandle->audio);
        }
    );
}

void systems::playMusic(entt::DefaultRegistry* registry)
{
    registry->view<bMusic>().each(
        [](auto entity, auto& music)
        {
            PlayMusicStream(music.musicHandle->audio);
        }
    );
}

void systems::pauseMusic(entt::DefaultRegistry* registry)
{
    registry->view<bMusic>().each(
        [](auto entity, auto& music)
        {
            PauseMusicStream(music.musicHandle->audio);
        }
    );
}

void systems::drawEntities(entt::DefaultRegistry* registry)
{
    registry->view<sprite, position>().each(
        [](auto entity, auto& sprite, auto& position)
        {
            float rotation = 0;
            Rectangle sourceRect, destRect;
            sourceRect = {0, 0, (float) sprite.texHandle->tex.width, (float) sprite.texHandle->tex.height};
            destRect = {(float) position.x, (float) position.y, sprite.width, sprite.height};
            Vector2 origin = {(float) sprite.width/2, (float) sprite.height/2};
            DrawTexturePro(sprite.texHandle->tex, sourceRect, destRect, origin, rotation, WHITE);
        }
    );
    registry->view<anim, position>().each(
        [](auto entity, auto& anim, auto& position)
        {
            float rotation = 0;
            Rectangle sourceRect, destRect;
            sourceRect = {0, 0, (float) anim.animHandle->anim[(int) anim.index].width, (float) anim.animHandle->anim[(int) anim.index].height};
            destRect = {(float) position.x, (float) position.y, anim.width, anim.height};
            Vector2 origin = {(float) anim.width/2, (float) anim.height/2};
            DrawTexturePro(anim.animHandle->anim[(int) anim.index], sourceRect, destRect, origin, rotation, WHITE);
        }
    );
    registry->view<tool, position>().each(
        [](auto entity, auto& tool, auto& position)
        {
            float rotation = 0;
            Rectangle sourceRect, destRect;
            sourceRect = {0, 0, (float) tool.texHandle->tex.width, (float) tool.texHandle->tex.height};
            destRect = {(float) position.x, (float) position.y, tool.width, tool.height};
            Vector2 origin = {(float) tool.width/2, (float) tool.height/2};
            DrawTexturePro(tool.texHandle->tex, sourceRect, destRect, origin, rotation, WHITE);
        }
    );
}

void systems::drawButtons(entt::DefaultRegistry* registry, const Font& font, float fontSize, float spacing)
{
    registry->view<button>().each(
        [font, fontSize, spacing](auto entity, auto& button)
        {
            float rotation = 0;
            Rectangle sourceRect;
            if(button.selected)
            {
                sourceRect = {0, 0, (float) button.animHandle->anim[(int)button.index].width, (float) button.animHandle->anim[(int)button.index].height};
                DrawTexturePro(button.animHandle->anim[(int)button.index], sourceRect, button.rect, {0, 0}, rotation, WHITE);
            }
            else
            {
                sourceRect = {0, 0, (float) button.texHandle->tex.width, (float) button.texHandle->tex.height};
                DrawTexturePro(button.texHandle->tex, sourceRect, button.rect, {0, 0}, rotation, WHITE);
            }
            systems::drawTextRecPro(font, button.text.c_str(), button.rect, fontSize, spacing, true, button.color, 0, 0, WHITE, WHITE, 1, 1);
        }
    );
}

bool systems::checkCollisionMouseButtons(entt::DefaultRegistry* registry, Vector2 mousePos)
{
    bool res = false;
    registry->view<button>().each(
        [mousePos, &res](auto entity, auto& button)
        {
            if(CheckCollisionPointRec(mousePos, button.rect))
            {
                Rectangle rect = button.rect;
                Vector2 padding = getScreenPadding();
                float scale = getScreenScale();
                rect.x *= scale;
                rect.y *= scale;
                rect.x += padding.x;
                rect.y += padding.y;
                rect.width *= scale;
                rect.height *= scale;
                if(CheckCollisionPointRec(mousePos, rect))
                {
                    res = true;
                }
            }
        }
    );
    return res;
}

std::uint32_t systems::checkCollisionMouseSprite(entt::DefaultRegistry* registry, Vector2 mousePos)
{
    std::uint32_t res = -1;
    registry->view<sprite, position>().each(
        [mousePos, &res](auto entity, auto& sprite, auto& position)
        {
            Vector2 pos = {position.x, position.y};
            if(CheckCollisionPointCircle(mousePos, pos, sprite.width/2))
            {
                res = entity;
            }
        }
    );
    return res;
}

std::uint32_t systems::checkCollisionMouseTool(entt::DefaultRegistry* registry, Vector2 mousePos)
{
    std::uint32_t res = -1;
    registry->view<tool, position>().each(
        [mousePos, &res](auto entity, auto& tool, auto& position)
        {
            Vector2 pos = {position.x, position.y};
            if(CheckCollisionPointCircle(mousePos, pos, tool.width/2))
            {
                res = entity;
            }
        }
    );
    return res;
}

float systems::getScreenScale()
{
    return std::min((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);
}

void systems::toggleFullscreen()
{
    if(GetScreenWidth() == GetMonitorWidth(0) && GetScreenHeight() == GetMonitorHeight(0))
    {
        Vector2 padding;
        padding.x = 100;
        padding.y = padding.x*(9.f/16.f);
        SetWindowPosition(padding.x, padding.y);
        SetWindowSize(GetMonitorWidth(0)-2*padding.x, GetMonitorHeight(0)-2*padding.y);
    }
    else
    {
        SetWindowPosition(0,0);
        SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
    }
}

Vector2 systems::getScreenPadding()
{
    Vector2 res;
    if((float)GetScreenWidth()/(float)GetScreenHeight() > 16.f/9.f)
    {
        res.y = 0; // In this case, the sceenHeight is the one that didn't change
        res.x = GetScreenWidth() - GetScreenHeight()*(16.f/9.f); //Getting all of the non used space
        res.x /= 2; //Dividing by two to get the padding
    }
    else
    {
        res.x = 0; // In this case, the sceenWidth is the one that didn't change
        res.y = GetScreenHeight() - GetScreenWidth()/(16.f/9.f); //Getting all of the non used space
        res.y /= 2; //Dividing by two to get the padding
    }
    return res;
}

void systems::drawTextRecPro(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectText, Color selectBack, int halign, int valign)
{
    int length = strlen(text);
    int textOffsetX = 0;        // Offset between characters
    int textOffsetY = 0;        // Required for line break!
    
    float scaleFactor = 0.0f;

    int letter = 0;             // Current character
    int index = 0;              // Index position in sprite font

    scaleFactor = fontSize/font.baseSize;


    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap? MEASURE_STATE : DRAW_STATE;
    int startLine = -1;   // Index where to begin drawing (where a line begins)
    int endLine = -1;     // Index where to stop drawing (where a line ends)

    // NOTE ; valign is used to set the vertical alignement of the text. When it is set at 0,
    // the text will be pushed to the top. When set to 1, the text will be centered. When set to 2,
    // it will be pushed to the bottom. The calculation is done through the measurement of the gap
    // between the total height of the text and the height of the rectangle.

    if(valign != 0 && wordWrap)
        textOffsetY = rec.height - MeasureHeightTextRec(font, text, rec, fontSize, spacing);
    if(valign == 1 && wordWrap)
        textOffsetY /= 2;

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        int glyphWidth = 0;
        int next = 1;
        letter = GetNextCodepoint(&text[i], &next);
        // NOTE: normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol so to not skip any we set `next = 1`
        if(letter == 0x3f) next = 1; 
        index = GetGlyphIndex(font, letter);
        i += next - 1;

        if (letter != '\n')
        {   
            glyphWidth = (font.chars[index].advanceX == 0)?
                         (int)(font.chars[index].rec.width*scaleFactor + spacing):
                         (int)(font.chars[index].advanceX*scaleFactor + spacing);
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw
        // before going outside of the `rec` container. We store this info inside
        // `startLine` and `endLine` then we change states, draw the text between those two
        // variables then change states again and again recursively until the end of the text
        // (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing
        // state immediately and begin drawing on the next line before we can get outside
        // the container.
        if (state == MEASURE_STATE)
        {
            // TODO: there are multiple types of `spaces` in UNICODE, maybe it's a good idea to add support for more
            // see: http://jkorpela.fi/chars/spaces.html 
            if ((letter == ' ') || (letter == '\t') || (letter == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth + 1) >= rec.width)
            {
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= next;
                if ((startLine + next) == endLine) endLine = i - next;
                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (letter == '\n')
            {
                state = !state;
            }

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                // NOTE ; valign is used to set the horizontal alignement of the text. When it is set at 0,
                // the text will be pushed to the left. When set to 1, the text will be centered. When set to 2,
                // it will be pushed to the right. The calculation is done through the measurement of the gap
                // between the total width of the Line and the width of the rectangle.
                if(halign != 0)
                {
                    char *cptext = new char[endLine - startLine];
                    for(int j = startLine+1; j <= endLine; j++)
                        cptext[j - startLine - 1] = text[j];
                    if(letter == '\n')
                        cptext[endLine - startLine - 1] = '\0';
                    else 
                        cptext[endLine - startLine] = '\0';

                    textOffsetX = (int)rec.width - (int)MeasureTextEx(font, cptext, fontSize, spacing).x;

                    delete[] cptext;
                }
                if(halign == 1)
                    textOffsetX /= 2;

                i = startLine;
                glyphWidth = 0;
            }

        }
        else
        {
            if (letter == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (int)((font.baseSize + font.baseSize/2)*scaleFactor);
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth + 1) >= rec.width))
                {
                    textOffsetY += (int)((font.baseSize + font.baseSize/2)*scaleFactor);
                    textOffsetX = 0;
                }

                if ((textOffsetY + (int)(font.baseSize*scaleFactor)) > rec.height) break;

                //draw selected
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    Rectangle strec = {rec.x + textOffsetX-1, rec.y + textOffsetY, (float)glyphWidth, (font.baseSize + font.baseSize/4)*scaleFactor };
                    DrawRectangleRec(strec, selectBack);
                    isGlyphSelected = true;
                }

                //draw glyph
                if ((letter != ' ') && (letter != '\t'))
                {
                    DrawTexturePro(font.texture, font.chars[index].rec,
                      (Rectangle){ rec.x + textOffsetX + font.chars[index].offsetX*scaleFactor,
                                   rec.y + textOffsetY + font.chars[index].offsetY*scaleFactor,
                                   font.chars[index].rec.width*scaleFactor,
                                   font.chars[index].rec.height*scaleFactor }, (Vector2){ 0, 0 }, 0.0f,
                                   (!isGlyphSelected)? tint : selectText);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (int)((font.baseSize + font.baseSize/2)*scaleFactor);
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                state = !state;
            }
        }
        textOffsetX += glyphWidth;
    }
}

int systems::MeasureHeightTextRec(Font font, const char *text, Rectangle rec, float fontSize, float spacing)
{

    int length = strlen(text);
    int textOffsetX = 0;        // Offset between characters
    int nbLines = 1;
    float scaleFactor = 0.0f;

    int letter = 0;             // Current character
    int index = 0;              // Index position in sprite font

    scaleFactor = fontSize/font.baseSize;

    enum { CURRENT_LINE = 0, NEW_LINE = 1 };
    int state = CURRENT_LINE;

    for (int i = 0; i < length; i++)
    {
        int glyphWidth = 0;
        int next = 1;
        letter = GetNextCodepoint(&text[i], &next);
        if(letter == 0x3f) next = 1; 
        index = GetGlyphIndex(font, letter);
        i += next - 1;

        if (letter != '\n')
        {   
            glyphWidth = (font.chars[index].advanceX == 0)?
                         (int)(font.chars[index].rec.width*scaleFactor + spacing):
                         (int)(font.chars[index].advanceX*scaleFactor + spacing);
        }

        if (state == CURRENT_LINE)
        {

            if ((textOffsetX + glyphWidth + 1) >= rec.width)
                state = !state;
            else if (letter == '\n')
                state = !state;
            if (state == NEW_LINE)
            {
                textOffsetX = 0;
                glyphWidth = 0;
                nbLines += 1;
                state = !state;
            }
        }
        textOffsetX += glyphWidth;
    }
    return (int)((font.baseSize + font.baseSize/2)*scaleFactor)*nbLines - (int)(font.baseSize/2*scaleFactor);
}

int systems::updateButtons(entt::DefaultRegistry* registry, Vector2 mousePos, bool mouseActive, int selected)
{
    int id = selected;
    registry->view<button>().each(
        [mousePos, mouseActive, &id](auto entity, auto& button)
        {
            Rectangle rect = button.rect;
            Vector2 padding = getScreenPadding();
            float scale = getScreenScale();
            rect.x *= scale;
            rect.y *= scale;
            rect.x += padding.x;
            rect.y += padding.y;
            rect.width *= scale;
            rect.height *= scale;
            if((mouseActive && CheckCollisionPointRec(mousePos, rect)) || id == button.id)
            {
                button.selected = 1;
                id = button.id;
            }
            else if(id != button.id)
            {
                button.selected = 0;
            }
        }
    );
    return id;
}

void systems::loadJson(rj::Document& doc, const char* path)
{
    std::ifstream ifs(path);
    rj::IStreamWrapper isw(ifs);
    doc.ParseStream(isw);
}

Rectangle systems::createRectangleForPadding(Rectangle rec, float top, float left, float right, float bottom)
{
    if(top + bottom > rec.height)
    {
        return rec;
    }
    if(left + right > rec.width)
    {
        return rec;
    }
    return {rec.x + left, rec.y + right, rec.width - (left + right), rec.height - (top + bottom)};
}
