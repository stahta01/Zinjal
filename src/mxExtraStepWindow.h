#ifndef MXEXTRASTEPWINDOW_H
#define MXEXTRASTEPWINDOW_H

#include "Cpp11.h"
#include "mxCommonPopup.h"
#include "mxCommonConfigControls.h"

class wxCheckBox;
class wxComboBox;
class wxTextCtrl;
class compile_extra_step;
class project_configuration;

class mxExtraStepWindow : public mxDialog {
private:
	_use_common_popup;
	compile_extra_step *step;
	wxComboBox *position;
	wxTextCtrl *name, *command, *output, *deps;
	wxCheckBox *check_rv, *hide_win, *delclean, *link_output;
	project_configuration *configuration;
public:
	static wxString new_name;
	mxExtraStepWindow(wxWindow *parent, project_configuration *conf, compile_extra_step *astep=nullptr);
	void OnOkButton(wxCommandEvent &evt);
	void OnCancelButton(wxCommandEvent &evt);
	void OnHelpButton(wxCommandEvent &evt);
	void OnCommandButton(wxCommandEvent &evt);
	void OnDepsButton(wxCommandEvent &evt);
	void OnOutputButton(wxCommandEvent &evt);
	DECLARE_EVENT_TABLE();
};

#endif

