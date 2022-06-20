#pragma once

#include "attribute.h"
#include "commands.h"

class XML_UI {
private:
    MyString currFile;

    void open();    //opens and read a file
    void close();   //closes a file
    void save();    //saves the xml file
    void saveAs();  //save the xml file in a new file
    void help();    //gives help
    void exit();    //exits the program

    /* всички функции въвеждат данните за дадена заявка и я извикват след това */
    void print();       //prints the xml file
    void select();      //prints the value of an atribute
    void set();         //changes the value of an atribute
    void children();    //prints the children to an element
    void child();       //prints a child to an element
    void text();        //prints the text of an element
    void delet();       //deletes a given attribute
    void newChild();    //adds a child
    void xpath();       //xpath

    void doCommand(int command);    //calls the function for the command
    int getCommand();               //reads a command

    int getNumber();                //reads a number
    MyString getString();           //reads a string
public:
    void run();                     //runs the program
};