#ifndef MX_PROJECT_GENERAL_CONFIG_H
#define MX_PROJECT_GENERAL_CONFIG_H

#include "mxCommonConfigControls.h"
#include "mxCommonPopup.h"

class wxTextCtrl;
class wxCheckBox;
class wxPanel;
class wxNotebook;

class mxProjectGeneralConfig : public mxDialog {
private:
	_use_common_popup;
	wxTextCtrl *project_name;
	wxTextCtrl *inherits_from;
	wxTextCtrl *project_autocomp;
	wxTextCtrl *project_debug_macros;
	wxTextCtrl *project_autocodes;
//	wxCheckBox *custom_tab;
	wxTextCtrl *tab_width;
	wxCheckBox *tab_use_spaces;
	wxTextCtrl *default_fext_source;
	wxTextCtrl *default_fext_header;
public:
	mxProjectGeneralConfig();
	wxPanel *CreateTabGeneral(wxNotebook *notebook);
	wxPanel *CreateTabAdvanced(wxNotebook *notebook);
	wxPanel *CreateTabInfo(wxNotebook *notebook);
	void OnOkButton(wxCommandEvent &evt);
	void OnDoxygenConfigButton(wxCommandEvent &evt);
	void OnCompileConfigButton(wxCommandEvent &evt);
	void OnCancelButton(wxCommandEvent &evt);
	void OnHelpButton(wxCommandEvent &evt);
	void OnDebugMacrosOpen(wxCommandEvent &evt);
	void OnDebugMacrosEdit(wxCommandEvent &evt);
	void OnDebugMacros(wxCommandEvent &evt);
	void OnInheritsFrom(wxCommandEvent &evt);
	void OnAutocodesOpen(wxCommandEvent &evt);
	void OnAutocodesEdit(wxCommandEvent &evt);
	void OnAutocodes(wxCommandEvent &evt);
	void OnAutoimprovingInspections(wxCommandEvent &evt);
	void OnIndexesButton(wxCommandEvent &evt);
//	void OnCustomTabs(wxCommandEvent &evt);
	void OnCustomToolsConfig(wxCommandEvent &evt);
	void OnWxfbConfig(wxCommandEvent &evt);
	void OnCppCheckConfig(wxCommandEvent &evt);
	void OnBySrcCompilingOts(wxCommandEvent &evt);
	void OnDrawGraph(wxCommandEvent &evt);
	void OnRunLizard(wxCommandEvent &evt);
	void OnStatistics(wxCommandEvent &evt);
	DECLARE_EVENT_TABLE();
};

#endif

