#include "mxGprofOutput.h"
#include "mxSizers.h"
#include <wx/grid.h>
#include <wx/statline.h>
#include <wx/combobox.h>
#include <wx/notebook.h>

BEGIN_EVENT_TABLE(mxGprofOutput,wxDialog)
	EVT_GRID_CMD_LABEL_LEFT_CLICK(wxID_ANY,mxGprofOutput::OnClickTable)
	EVT_COMBOBOX(wxID_ANY,mxGprofOutput::OnComboChange)
END_EVENT_TABLE()

mxGprofOutput::mxGprofOutput(wxWindow *parent, wxString fname):wxDialog(parent, wxID_ANY, "gprof output", wxDefaultPosition, wxSize(700,400) ,wxALWAYS_SHOW_SB | wxALWAYS_SHOW_SB | wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER),data(fname.c_str()) {
	wxSizer *main_sizer=new wxBoxSizer(wxVERTICAL);
	
	wxNotebook *notebook = new wxNotebook(this,wxID_ANY);
	
	wxPanel *table_panel=new wxPanel(notebook,wxID_ANY);
	wxSizer *table_sizer=new wxBoxSizer(wxVERTICAL);
	grid_table=new wxGrid(table_panel,wxID_ANY);
	grid_table->CreateGrid(data.table.size(),7);
	grid_table->SetColLabelValue(0,"% time");
	grid_table->SetColLabelValue(1,"cum. secs");
	grid_table->SetColLabelValue(2,"self secs");
	grid_table->SetColLabelValue(3,"calls");
	grid_table->SetColLabelValue(4,"self s/call");
	grid_table->SetColLabelValue(5,"total s/call");
	grid_table->SetColLabelValue(6,"name");
	grid_table->SetRowLabelSize(0);
	FillTable();
	grid_table->AutoSizeColumns();
	table_sizer->Add(grid_table,sizers->Exp1);
	table_panel->SetSizer(table_sizer);
	
	wxPanel *graph_panel=new wxPanel(notebook,wxID_ANY);
	wxSizer *graph_sizer=new wxBoxSizer(wxVERTICAL);
	wxArrayString array;
	for(unsigned int i=0;i<data.graph.size();i++) array.Add(data.graph[i].name);
	combo = new wxComboBox(graph_panel,wxID_ANY,array[0],wxDefaultPosition,wxDefaultSize,array,wxCB_READONLY);
	combo->SetSelection(0);
	graph_sizer->Add(combo,sizers->Exp0);
	grid_graph=new wxGrid(graph_panel,wxID_ANY);
	grid_graph->CreateGrid(0,5);
	grid_graph->SetColLabelValue(0,"% time");
	grid_graph->SetColLabelValue(1,"self");
	grid_graph->SetColLabelValue(2,"children");
	grid_graph->SetColLabelValue(3,"called");
	grid_graph->SetColLabelValue(4,"name");
	grid_graph->SetRowLabelSize(0);
	FillGraph();
	graph_sizer->Add(grid_graph,sizers->Exp1);
	graph_panel->SetSizer(graph_sizer);
	
	notebook->AddPage(table_panel,"table");
	notebook->AddPage(graph_panel,"callgraph");
	main_sizer->Add(notebook,sizers->Exp1);
	
	SetSizer(main_sizer);
	Show();
}

static wxString to_str(float f) {
	wxString s;
	s.Printf("%.2f",f);
	return s;
}

void mxGprofOutput::FillTable ( ) {
	for(unsigned int i=0;i<data.table.size();i++) { 
		grid_table->SetCellValue(i,0,to_str(data.table[i].percent_time));	
		grid_table->SetCellValue(i,1,to_str(data.table[i].cumulative_seconds));	
		grid_table->SetCellValue(i,2,to_str(data.table[i].self_seconds));	
		grid_table->SetCellValue(i,3,wxString()<<data.table[i].calls);	
		grid_table->SetCellValue(i,4,to_str(data.table[i].self_s_calls));	
		grid_table->SetCellValue(i,5,to_str(data.table[i].total_s_calls));	
		grid_table->SetCellValue(i,6,data.table[i].name);	
	}
}

void mxGprofOutput::OnClickTable (wxGridEvent & event) {
	if (event.GetEventObject()!=grid_table) return;
	static int sorted=0;
	int new_sorted=event.GetCol()+1;
	if (new_sorted==sorted) {
		data.Sort(event.GetCol(),true);
		sorted=-new_sorted;
	} else {
		data.Sort(event.GetCol(),false);
		sorted=new_sorted;
	}
	FillTable();
}

void mxGprofOutput::FillGraph ( ) {
	int i=combo->GetSelection();
	if (i<0||i>=int(data.graph.size())) return;
	int sum=data.graph[i].calls_to.size()+data.graph[i].called_by.size()+2;
	if (sum>grid_graph->GetNumberRows()) grid_graph->AppendRows(sum-grid_graph->GetNumberRows());
	else if (sum<grid_graph->GetNumberRows()) grid_graph->DeleteRows(0,grid_graph->GetNumberRows()-sum);
	sum=0;
	grid_graph->SetCellValue(sum,0,""); grid_graph->SetCellValue(sum,1,""); grid_graph->SetCellValue(sum,2,"");
	grid_graph->SetCellValue(sum,3,""); grid_graph->SetCellValue(sum,4,"Es llamada por"); sum++;
	for(unsigned int j=0;j<data.graph[i].called_by.size();j++) { 
		grid_graph->SetCellValue(sum,0,to_str(data.graph[i].called_by[j].percent_time));
		grid_graph->SetCellValue(sum,1,to_str(data.graph[i].called_by[j].self));
		grid_graph->SetCellValue(sum,2,to_str(data.graph[i].called_by[j].children));
		grid_graph->SetCellValue(sum,3,data.graph[i].called_by[j].called);
		grid_graph->SetCellValue(sum,4,data.graph[i].called_by[j].name);
		sum++;
	}
	grid_graph->SetCellValue(sum,0,""); grid_graph->SetCellValue(sum,1,""); grid_graph->SetCellValue(sum,2,"");
	grid_graph->SetCellValue(sum,3,""); grid_graph->SetCellValue(sum,4,"Llama a"); sum++;
	for(unsigned int j=0;j<data.graph[i].calls_to.size();j++) { 
		grid_graph->SetCellValue(sum,0,to_str(data.graph[i].calls_to[j].percent_time));
		grid_graph->SetCellValue(sum,1,to_str(data.graph[i].calls_to[j].self));
		grid_graph->SetCellValue(sum,2,to_str(data.graph[i].calls_to[j].children));
		grid_graph->SetCellValue(sum,3,data.graph[i].calls_to[j].called);
		grid_graph->SetCellValue(sum,4,data.graph[i].calls_to[j].name);
		sum++;
	}	
	grid_graph->AutoSizeColumns();
}

void mxGprofOutput::OnComboChange (wxCommandEvent & event) {
	event.Skip();
	FillGraph();
}
