#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() 
{
    Program* program = new Program("Minimal Path Finder");
    return true;
}