#if !defined(__WIN32__) && !defined(__APPLE__)

#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/textfile.h>
#include "mxIconInstaller.h"
#include "mxSizers.h"
#include "mxUtils.h"
#include "mxBitmapButton.h"
#include "Language.h"
#include "ConfigManager.h"
#include "mxMessageDialog.h"
#include "execution_workaround.h"
#include "mxCommonConfigControls.h"

BEGIN_EVENT_TABLE(mxIconInstaller,wxDialog)
	EVT_BUTTON(wxID_OK,mxIconInstaller::OnButtonOk)
	EVT_BUTTON(wxID_CANCEL,mxIconInstaller::OnButtonCancel)
	EVT_CLOSE(mxIconInstaller::OnClose)
END_EVENT_TABLE()
	
	
static char icon_sizes[][5]={"16","24","32","48","64","128","256",""};

mxIconInstaller::mxIconInstaller(bool first_run):wxDialog(nullptr,wxID_ANY,LANG(XDG_CAPTION,"Iconos lanzadores")) {
	
	icon_installed=false; xdg_found=true;
	
	wxString res = mxUT::GetOutput("xdg-desktop-menu --version");
	if (!res.Len()||res.Find("bash")!=wxNOT_FOUND) {
		if (!first_run) 
			mxMessageDialog(nullptr,LANG(XDG_NO_XDG,"Debe instalar xdg-utils para tener acceso todas las funcionalidades"))
				.Title(LANG(XDG_CAPTION,"Iconos lanzadores")).IconInfo().Run();
		xdg_found=false;
//		return;
	}
	
	wxBoxSizer *sizer=new wxBoxSizer(wxVERTICAL);
	
	if (first_run) sizer->Add(new wxStaticText(this,wxID_ANY,LANG(XDG_FIRST_TIME,"�Desea crear un icono para acceder a ZinjaI desde el menu del sistema o el escritorio?")),sizers->BA5_Exp0);
	
	desktop = mxDialog::AddCheckBox(sizer,this,LANG(XDG_CREATE_DESKTOP,"Crear un icono en el escritorio"),false);
	menu = mxDialog::AddCheckBox(sizer,this,LANG(XDG_CREATE_MENU,"Crear un icono en el menu (en la categoria Programacion/Desarrollo)"),xdg_found);
	zpr = mxDialog::AddCheckBox(sizer,this,"Asociar los archivos de proyecto (.zpr)",xdg_found);
	cpp = mxDialog::AddCheckBox(sizer,this,"Asociar archivos .c/.cc/.cpp/.cxx/.c++/.h/.hh/.hxx/.hpp/.h++",xdg_found);
	if (!xdg_found) { menu->Enable(false); cpp->Enable(false); zpr->Enable(false); }
	
	wxBoxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
	
	mxBitmapButton *cancel_button = new mxBitmapButton (this, wxID_CANCEL, bitmaps->buttons.cancel, LANG(GENERAL_CANCEL_BUTTON,"&Cancelar")); 
	mxBitmapButton *ok_button = new mxBitmapButton (this, wxID_OK, bitmaps->buttons.ok, LANG(GENERAL_OK_BUTTON,"  &Aceptar  "));
	ok_button->SetMinSize(wxSize(ok_button->GetSize().GetWidth()<80?80:ok_button->GetSize().GetWidth(),ok_button->GetSize().GetHeight()));
	ok_button->SetDefault(); 
	bottomSizer->Add(cancel_button,sizers->BA5);
	bottomSizer->Add(ok_button,sizers->BA5);
	
	sizer->Add(bottomSizer,sizers->BA5_Right);
	
	SetSizerAndFit(sizer);
	
	Show(); ok_button->SetFocus();
	
}

void mxIconInstaller::OnButtonOk (wxCommandEvent & evt) {
	if (desktop->GetValue()) InstallDesktop(false);
	if (menu->GetValue()) InstallDesktop(true);
	if (zpr->GetValue()) InstallMimeZpr();
	if (cpp->GetValue()) InstallMimeSource();
	Close();
}

void mxIconInstaller::OnButtonCancel (wxCommandEvent & evt) {
	Close();
}

void mxIconInstaller::OnClose (wxCloseEvent & evt) {
	Destroy();
}

void mxIconInstaller::InstallIcons ( ) {
	if (icon_installed) return;
	
	for (const char (*sz)[5] = icon_sizes; (*sz)[0]!='\0';++sz) {
		wxString icon_file = DIR_PLUS_FILE(config->zinjai_dir,wxString("imgs/icons")<<*sz<<"/zinjai.png");
		mxExecute(wxString("xdg-icon-resource install --novendor --size ")<<*sz<<" \""<<icon_file<<"\"",wxEXEC_NODISABLE|wxEXEC_SYNC);
	}
	
	icon_installed=true;
}

void mxIconInstaller::InstallDesktop ( bool menu ) {
	if (!xdg_found) { MakeDesktopIcon(); return; }
	InstallIcons();
	wxString desk_file=DIR_PLUS_FILE(config->temp_dir,_T("zinjai.desktop"));
	wxTextFile fil(desk_file);
	if (fil.Exists())
		fil.Open();
	else
		fil.Create();
	fil.Clear();
	fil.AddLine(_T("[Desktop Entry]"));
	fil.AddLine(_T("Comment=IDE for C++ programming"));
	fil.AddLine(_T("Comment[es]=IDE para programar en C++"));
	fil.AddLine(_T("Encoding=UTF-8"));
	fil.AddLine(_T("Name=ZinjaI"));
	fil.AddLine(_T("Type=Application"));
	fil.AddLine(_T("Categories=Development"));
	fil.AddLine(_T("Icon=zinjai"));
	fil.AddLine(_T("MimeType=text/x-zinjai"));
	fil.AddLine(wxString(_T("Exec="))<<DIR_PLUS_FILE(config->zinjai_dir,_T("zinjai"))<<" %f");
	fil.Write();
	fil.Close();
	if (menu)
		mxExecute(wxString("xdg-desktop-menu install --novendor \"")<<desk_file<<"\"",wxEXEC_NODISABLE|wxEXEC_SYNC);
	else
		mxExecute(wxString("xdg-desktop-icon install --novendor \"")<<desk_file<<"\"",wxEXEC_NODISABLE|wxEXEC_SYNC);
}

void mxIconInstaller::InstallMimeZpr() { // todavia no se usa
	wxString mime_type="text/x-zinjai";
	wxString mime_desc="ZinjaI project";
	wxString icon="zinjai_zpr";
	wxArrayString exts;
	exts.Add("*.zpr");
	InstallMime(mime_type,mime_desc,icon,exts);
}

void mxIconInstaller::InstallMimeSource() { // todavia no se usa
	{
		wxString mime_type="text/x-zinjai-c-source";
		wxString mime_desc="C source file";
		wxString icon="zinjai_c";
		wxArrayString exts;
		exts.Add("*.c");
		InstallMime(mime_type,mime_desc,icon,exts);
	}
	{
		wxString mime_type="text/x-zinjai-cpp-header";
		wxString mime_desc="C/C++ header file";
		wxString icon="zinjai_h";
		wxArrayString exts;
		exts.Add("*.h");
		exts.Add("*.hh");
		exts.Add("*.hpp");
		exts.Add("*.hxx");
		exts.Add("*.h++");
		InstallMime(mime_type,mime_desc,icon,exts);
	}
	{
		wxString mime_type="text/x-zinjai-cpp-source";
		wxString mime_desc="C++ source file";
		wxString icon="zinjai_cpp";
		wxArrayString exts;
		exts.Add("*.cpp");
		exts.Add("*.cxx");
		exts.Add("*.c++");
		exts.Add("*.cc");
		InstallMime(mime_type,mime_desc,icon,exts);
	}
}

void mxIconInstaller::InstallMime ( wxString mime_type, wxString mime_desc, wxString icon, wxArrayString exts ) {
	wxString mime_type_ns = mime_type; mime_type_ns.Replace("/","-");
	wxString xml_file=DIR_PLUS_FILE(config->temp_dir,icon+".xml");
	wxTextFile fil(xml_file);
	if (fil.Exists())
		fil.Open();
	else
		fil.Create();
	fil.Clear();
	fil.AddLine("<?xml version=\"1.0\"?>");
	fil.AddLine("<mime-info xmlns='http://www.freedesktop.org/standards/shared-mime-info'>");
	fil.AddLine(wxString("<mime-type type=\"")<<mime_type<<"\">");
	fil.AddLine(wxString("<comment>")<<mime_desc<<"</comment>");
	fil.AddLine(wxString("<generic-icon name=\"")<<mime_type_ns<<"\" />");
	for (unsigned int i=0;i<exts.GetCount();i++)
		fil.AddLine(wxString("<glob pattern=\"")<<exts[i]<<"\" case-sensitive=\"false\" />");
	fil.AddLine("</mime-type>");
	fil.AddLine("</mime-info>");
	fil.Write();
	fil.Close();

	mxExecute(wxString("xdg-mime install --novendor \"")<<xml_file<<"\"",wxEXEC_NODISABLE|wxEXEC_SYNC);
	wxString icon_file;
	for (const char (*sz)[5] = icon_sizes; (*sz)[0]!='\0';++sz) {
		icon_file=DIR_PLUS_FILE(config->zinjai_dir,DIR_PLUS_FILE("imgs",DIR_PLUS_FILE("icons",DIR_PLUS_FILE(*sz,icon+".png"))));
		mxExecute(wxString("xdg-icon-resource install --context mimetypes --size ")<<*sz<<" \""<<icon_file<<"\" "<<mime_type_ns,wxEXEC_NODISABLE|wxEXEC_SYNC);
	}
	mxExecute(wxString("xdg-mime default zinjai.desktop ")<<mime_type,wxEXEC_NODISABLE|wxEXEC_SYNC);
}

void mxIconInstaller::MakeDesktopIcon() {
		
	wxString desk_dir = DIR_PLUS_FILE(wxFileName::GetHomeDir(),_T("Desktop"));
	if (!wxFileName::DirExists(desk_dir) && wxFileName::DirExists(DIR_PLUS_FILE(wxFileName::GetHomeDir(),_T("Escritorio"))))
		desk_dir=DIR_PLUS_FILE(wxFileName::GetHomeDir(),_T("Escritorio"));
	
	wxTextFile fil(DIR_PLUS_FILE(desk_dir,_T("ZinjaI.desktop")));
	if (fil.Exists())
		fil.Open();
	else
		fil.Create();
	fil.Clear();
	fil.AddLine(_T("[Desktop Entry]"));
	fil.AddLine(_T("Comment=IDE for C++ programming"));
	fil.AddLine(_T("Comment[es]=IDE para programar en C++"));
	fil.AddLine(_T("Encoding=UTF-8"));
	fil.AddLine(wxString(_T("Icon="))<<DIR_PLUS_FILE(config->zinjai_dir,_T("imgs/zinjai-64x64.png")));
	fil.AddLine(_T("Name=ZinjaI"));
	fil.AddLine(_T("Name[es]=ZinjaI"));
	fil.AddLine(_T("Type=Link"));
	fil.AddLine(wxString(_T("URL="))<<DIR_PLUS_FILE(config->zinjai_dir,_T("zinjai")));
	fil.Write();
	fil.Close();
}


#endif


