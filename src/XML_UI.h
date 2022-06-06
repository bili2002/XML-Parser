#pragma once

#include "attribute.h"
#include "commands.h"

class XML_UI {
private:
    /* всички функции въвеждат данните а дадена заявка и я извикват след това */

    void open();
    void close();
    void save();
    void saveAs();
    void help();
    void exit(); 

    void doCommand(int command); //извиква подходящата функцция за командата
    int getCommand(); //взема команда

    int getNumber(); 
public:
    void run(); 
};