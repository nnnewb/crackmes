// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#  include <wx/wx.h>
#endif
#include "OTP.hpp"

class MyFrame : public wxFrame {
private:
  std::unique_ptr<TOTP> otp = std::unique_ptr<TOTP>(new TOTP("secret", 10));
  wxTimer *timer = new wxTimer();

  wxPanel *panel = nullptr;
  wxTextCtrl *txtCtrl = nullptr;
  wxStaticText *label = nullptr;
  wxButton *btn = nullptr;
  wxBoxSizer *vbox = nullptr;

public:
  MyFrame() : wxFrame(NULL, wxID_ANY, wxT("Hello World")) {
    SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));

    wxColour col1, col2;
    col1.Set(wxT("#4f5049"));
    col2.Set(wxT("#282c34"));

    panel = new wxPanel(this, -1);
    panel->SetBackgroundColour(col1);
    vbox = new wxBoxSizer(wxVERTICAL);

    txtCtrl = new wxTextCtrl(panel, wxID_ANY);
    txtCtrl->SetBackgroundColour(col2);
    txtCtrl->SetForegroundColour(wxColour(wxT("#8fb2bf")));

    label = new wxStaticText(panel, wxID_ANY, wxT("input serial here"));
    label->SetForegroundColour(wxColour(wxT("#dcdcdc")));

    btn = new wxButton(panel, wxID_ANY, wxT("try it!"));
    btn->SetBackgroundColour(col1);
    btn->SetForegroundColour(wxColour(wxT("#8fb2bf")));

    vbox->Add(label, 0, wxEXPAND | wxLEFT | wxRIGHT);
    vbox->Add(txtCtrl, 3, wxEXPAND | wxALL);
    vbox->Add(btn, 0, wxEXPAND | wxLEFT | wxRIGHT);

    panel->SetSizer(vbox);
    panel->SetMaxSize(panel->GetBestSize());
    panel->SetMinSize(panel->GetBestSize());

    timer->SetOwner(this);
    timer->Start(1000);

    this->Connect(wxEVT_TIMER, wxTimerEventHandler(MyFrame::onTimer));

    Centre();
  }

  void onTimer(wxTimerEvent &ev) {
    auto s = wxString::Format("serial answer: %06d", otp->get());
    this->label->SetLabelText(s);
    return;
  }

  virtual ~MyFrame() { delete timer; }

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
