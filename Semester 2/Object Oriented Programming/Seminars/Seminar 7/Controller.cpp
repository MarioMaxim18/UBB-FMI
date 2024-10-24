#include "Controller.h"
#include <iostream>


void Controller::add(string title, string artist, string path)
{
    MediaItem m1{ title, artist, path };
    r.add(m1);
    std::cout<<"added new song"<<title<<std::endl;
    UndoStack.push(std::make_unique<UndoAdd>(m1, r)); // create a unique pointer
}

void Controller::remove(string title, string artist)
{
    MediaItem m1{ title, artist, ""};
    r.remove(m1);
    UndoStack.push(std::make_unique<UndoRemove>(m1, r));
}

//const MediaItem& Controller::find(std::string title, std::string artist) const noexcept(false)
//{
//    // TODO: insert return statement here
//}

void Controller::undo()
{
    if (UndoStack.empty())
        throw std::runtime_error("Stack is empty!");
    UndoStack.top()->executeUndo();
    UndoStack.pop();
}
