#include <GUI.h>
#include <Project.h>

void GUI::init(const unsigned int width, const unsigned int height, const std::string& name){
    TwInit(TW_OPENGL, NULL);
    TwWindowSize(width,height);
    m_bar = TwNewBar(name.c_str());
}

void GUI::addParameter(void* parameter, const ETwType& parameterType,const std::string &name, const std::string &definition, bool readandwrite){
    if (readandwrite)
        TwAddVarRW(m_bar, name.c_str(), parameterType, parameter,definition.c_str());
    else
        TwAddVarRO(m_bar, name.c_str(), parameterType, parameter,definition.c_str());
}

void TW_CALL PlayCallback(void *clientData)
{
    Project* nbs = (Project*)clientData;
    nbs->playNewSequence();
}

void GUI::addPlayButton(const std::string& name, void* project, const std::string &definition){
    TwAddButton(m_bar,name.c_str(),PlayCallback, project, definition.c_str());
}

void GUI::draw() const{
    TwDraw();
}

void GUI::terminate(){
    TwDeleteBar(m_bar);
    TwTerminate();
}
