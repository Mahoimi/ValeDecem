#ifndef GUI_HPP
#define GUI_HPP

#include <GL/glew.h>
#include <AntTweakBar.h>
#include <SFML/Window.hpp>

class GUI {
private:
    TwBar* m_bar;

public:
    GUI():m_bar(nullptr){}
    void init(const unsigned int width, const unsigned int height, const std::string& name);
    void addParameter(void* parameter, const ETwType& parameterType,const std::string &name, const std::string &definition, bool readandwrite=true);
    void draw() const;
    void terminate();
};

#endif // GUI_HPP
