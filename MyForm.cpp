#include "MyForm.h"

using namespace::System;
using namespace::System::Windows::Forms;


[STAThread]
int Main(cli::array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    FileSystemGUI::MyForm form;
    Application::Run(% form);
    return 0;
}
