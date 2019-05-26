#include "text.hpp"

Text::Text(){
    text = std::list<std::pair<std::string, float>>();
    currentText = std::pair<std::string, float>("", 0);
    currentTime = 0;
    currentIndice = 0;
    maximumSize = 0;
}

void Text::addText(std::string content, float interval)
{
    maximumSize += (int)content.size();
    text.push_back(std::pair<std::string, float>(content, interval));
}
void Text::reservePrintText()
{
    ptext.reserve(maximumSize);
    ptext = "";
}

void Text::updateText(float deltaTime, Sound soundFX) //update ptext at regular interval
{
    if(text.size() > 0 && currentIndice == 0)
        currentText = text.front();
    if((int)ptext.size() < maximumSize)
    {
        currentTime += deltaTime;
        if(currentTime >= currentText.second)
        {
            ptext += currentText.first[currentIndice++];
            currentTime = currentTime - currentText.second;
            PlaySound(soundFX);
        }
        if(currentIndice >= (int)currentText.first.size()){
            currentIndice = 0;
            text.pop_front();
        }
    }
}

bool Text::isUpdateComplete()
{
    return ((int)ptext.size() == maximumSize);
}

void Text::completeText()
{
    currentText = text.front();
    for(; currentIndice < (int)currentText.first.size(); currentIndice++)
        ptext += currentText.first[currentIndice];
    text.pop_front();
    for (std::list<std::pair<std::string, float>>::iterator it = text.begin(); it != text.end(); ++it)
    {
        ptext += it->first;
    }
    text.clear();
}
