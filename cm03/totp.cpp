// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#  include <wx/wx.h>
#endif
#include "OTP.hpp"

enum { ID_BTN = 1 };

class MyFrame : public wxFrame {
private:
  std::unique_ptr<TOTP> otp = std::unique_ptr<TOTP>(new TOTP("secret", 10));

  wxPanel *panel = nullptr;
  wxBoxSizer *vbox = nullptr;
  wxStaticText *pwd = nullptr;
  wxStaticText *remain_time = nullptr;
  wxTimer *timer = nullptr;

public:
  MyFrame() : wxFrame(NULL, wxID_ANY, wxT("TOTP")) {
    SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));

    panel = new wxPanel(this, -1);
    panel->SetBackgroundColour(wxColour("#1e1e1e"));
    vbox = new wxBoxSizer(wxVERTICAL);

    pwd = new wxStaticText(panel, wxID_ANY, wxString::Format("PWD: %06d", otp->get()));
    pwd->SetForegroundColour(wxColour(wxT("#dcdcdc")));
    pwd->SetFont(wxFont(26, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    pwd->SetExtraStyle(wxALIGN_CENTER_HORIZONTAL);

    remain_time = new wxStaticText(panel, wxID_ANY, wxString::Format("ExpireIn: %ds", otp->get_next_tick()));
    remain_time->SetForegroundColour(wxColour(wxT("#dcdcdc")));
    remain_time->SetFont(wxFont(26, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    remain_time->SetExtraStyle(wxALIGN_CENTER_HORIZONTAL);

    vbox->Add(pwd, 0, wxEXPAND | wxLEFT | wxRIGHT);
    vbox->Add(remain_time, 0, wxEXPAND | wxLEFT | wxRIGHT);

    panel->SetSizer(vbox);
    panel->SetMaxSize(panel->GetBestSize());
    panel->SetMinSize(panel->GetBestSize());

    timer = new wxTimer();
    timer->SetOwner(this);

    Bind(wxEVT_TIMER, &MyFrame::onTimer, this);

    timer->Start(1000);
    Centre();
  }

  void onTimer(wxTimerEvent &ev) {
    pwd->SetLabelText(wxString::Format("PWD: %06d", otp->get()));
    remain_time->SetLabelText(wxString::Format("ExpireIn: %ds", otp->get_next_tick()));
    return;
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
