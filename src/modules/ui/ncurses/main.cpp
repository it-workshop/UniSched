#include <ncurses.h>

#include <abstractui.h>

class ncursesUI: public Core::AbstractUI {
private:
protected:
public:

    ncursesUI(std::vector<Core::Module *>* modules, void *handle);

    virtual void init(const std::vector<std::string>& args);
    virtual int run();
};

ncursesUI::ncursesUI(std::vector<Core::Module *>* modules, void *handle):
        AbstractUI("ncurses", modules, handle)
{
}

void ncursesUI::init(const std::vector<std::string>& args)
{
}

int ncursesUI::run()
{
    return 0;
}

extern "C" {

void init(std::vector<Core::Module *>* modules, void *handle)
{
    new ncursesUI(modules, handle);
}

};

