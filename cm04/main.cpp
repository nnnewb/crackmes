// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#  include <wx/wx.h>
#endif

class MyFrame : public wxFrame {
public:
  MyFrame() : wxFrame(NULL, wxID_ANY, wxT("Simple TOTP Checker")) {
    SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));

    auto panel = new wxPanel(this, -1);
    auto vbox = new wxBoxSizer(wxVERTICAL);

    panel->SetSizer(vbox);
    panel->SetMaxSize(panel->GetBestSize());
    panel->SetMinSize(panel->GetBestSize());

    Centre();
  }

private:
};

class MyApp : public wxApp {
public:
  virtual bool OnInit() {
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
