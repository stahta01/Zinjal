#ifndef MXWXFBINHERITER_H
#define MXWXFBINHERITER_H
#include <wx/dialog.h>
#include <wx/arrstr.h>

class wxComboBox;
class wxTextCtrl;

class mxWxfbInheriter : public wxDialog {
	enum { WXFBI_NEW_CLASS_ANY, WXFBI_NEW_CLASS_SPECIFIC, WXFBI_UPDATE_EXISTING_CLASS } mode;
	wxArrayString wxfb_classes; ///< classes autogenerated by wxfb (all if mode==WXFBI_NEW_CLASS_ANY, a single class if mode==WXFBI_NEW_CLASS_SPECIFIC, not used otherwise)
	wxArrayString user_classes; ///< classes inherited from wxfb's autogenerated classes (if mode==WXFBI_UPDATE_EXISTING_CLASS, not used otherwise)
private:
	wxComboBox *base_class;
	wxTextCtrl *child_class;
public:
	mxWxfbInheriter(wxWindow *parent, wxString classname, bool update);
	void FillBaseArray();
	void OnClose(wxCloseEvent &evt);
	void OnButtonOk(wxCommandEvent &evt);
	void OnButtonCancel(wxCommandEvent &evt);
	void OkNewClass();
	void OkUpdateClass();
	DECLARE_EVENT_TABLE();
};

#endif

