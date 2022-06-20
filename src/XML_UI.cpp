#include <iostream>
#include <fstream>
#include <cstring>

#include "XML_UI.h"
#include "Element.h"

void XML_UI::open() {
    //close();
    std::cin>>currFile;
    //std::cerr<<currFile;
    
    char* temp = nullptr;
    currFile.toRealStringIn(temp);
    std::ifstream is("in.txt", std::ios::binary);
    if (temp != nullptr) {
        delete[] temp;
    }

    if (!is.is_open()) {
        std::cerr<<"Error: File couldn't open.\n";
        return;
    }

    Element::input(is);
    is.close();
}

void XML_UI::close() {
    currFile.clear();
    Element::destructTree();
}

void XML_UI::save() {
    char* temp = nullptr;
    currFile.toRealStringIn(temp);
    std::ofstream os(temp, std::ios::trunc);
    if (temp == nullptr) {
        delete[] temp;
    }
    
    if (!os.is_open()) {
        std::cerr<<"Error: File couldn't open.\n";
        return;
    }

    Element::print(os);
    os.close();
}

void XML_UI::saveAs() {
    MyString tempFile;
    std::cin>>tempFile;

    char* temp = nullptr;
    tempFile.toRealStringIn(temp);
    std::ofstream os(temp, std::ios::trunc);
    if (temp == nullptr) {
        delete[] temp;
    }
    
    if (!os.is_open()) {
        std::cerr<<"Error: File couldn't open.\n";
        return;
    }

    Element::print(os);
    os.close();
}

void XML_UI::help() {
    //TO DO
}

void XML_UI::exit() {
    if (currFile.empty()) {
        std::exit(0);
    }

    std::cerr<<"You have an open file with unsaved changes, please select close or save first.\n";

    while (true) {
        MyString temp;
        std::cin>>temp;
        if (temp == commandString[CLOSE]) {
            close();
            break;
        } else if (temp == commandString[SAVE]) {
            save();
            break;
        } else if (temp == commandString[SAVEAS]) {
            saveAs();
            break;
        } else {
            std::cerr<<"There is no such command.\n";
        }
    }
    
    std::exit(0);
}

void XML_UI::print() {
    Element::print(std::cout);
}

void XML_UI::select() {
    MyString id = getString();
    MyString key = getString();
    Element::printAttributeValue(std::cout, id, key);
}

void XML_UI::set() {
    MyString id = getString();
    MyString key = getString();
    MyString value = getString();
    Element::setAttributeValue(id, key, value);
}

void XML_UI::children() {
    MyString id = getString();
    Element::printChildren(std::cout, id);
}

void XML_UI::child() {
    MyString id = getString();
    int num = getNumber();
    Element::printChild(std::cout, id, num-1);
}

void XML_UI::text() {
    MyString id = getString();
    Element::printText(std::cout, id);
}

void XML_UI::delet() {
    MyString id = getString();
    MyString key = getString();
    Element::deleteAttribute(id, key);

}

void XML_UI::newChild() {
    MyString id = getString();
    MyString tag = getString();
    Element::addChild(id, tag);
}

void XML_UI::xpath() {
    MyString path = getString();
    Element::xpath(std::cout, path);
}

void XML_UI::doCommand(int command) {
    if (currFile.empty()) {
        if (command == Commands::OPEN) {
            open();
        } else if (command == Commands::EXIT) {
            exit();
        } else {
            std::cerr<<"Error: You should first open a file.\n";
        }
        return;
    }

    switch (command)
    {
    case Commands::OPEN :
        open();
        break;
    
    case Commands::CLOSE :
        close();
        break;

    case Commands::SAVE :
        save();
        break;

    case Commands::SAVEAS :
        saveAs();
        break;

    case Commands::HELP :
        help();
        break;

    case Commands::EXIT :
        exit();
        break;

    case Commands::PRINT :
        print();
        break;

    case Commands::SELECT :
        select();
        break;

    case Commands::SET :
        set();
        break;

    case Commands::CHILDREN :
        children();
        break;

    case Commands::CHILD :
        child();
        break;

    case Commands::TEXT :
        text();
        break;

    case Commands::DELETE :
        delet();
        break;

    case Commands::NEWCHILD :
        newChild();
        break;

    case Commands::XPATH :
        xpath();
        break;

    default:
        std::cerr<<"Error: No such command.\n";
        break;
    }
}

int XML_UI::getCommand() {
    MyString command;
    std::cin>>command; 

    bool foundCommand = false;
    int commandNumber = -1;
    for (const MyString& currCommand : commandString) {
        commandNumber++;
        if (command == currCommand) {
            foundCommand = true;
            break;
        }
    }

    if (!foundCommand) {
        return -1;
    }

    return commandNumber;
}

int XML_UI::getNumber() {
    int temp;
    std::cin>>temp;
    return temp;
}

MyString XML_UI::getString() {
    MyString temp;
    std::cin>>temp;
    return temp;
}

void XML_UI::run() {
    help();
    while (true) {
        doCommand(getCommand());
    }
}