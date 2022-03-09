#include "visualizer.h"
#include "visualizer.cpp"

Visualizer *v = new Visualizer;

int main(int argc, char *argv[])
{
    v->Start();
    while(v->isRunning)
    {
        if(!v->startVis) v->DrawStartMenu();
        else
        {
            v->HandleEvents();
            v->Show();
        }
    }
    v->Destroy();
    return 0;
}
