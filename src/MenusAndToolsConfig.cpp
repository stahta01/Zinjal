#include "MenusAndToolsConfig.h"
#include "Language.h"
#include "mxUtils.h"
#include "ConfigManager.h"
#include "ProjectManager.h"
#include "mxMainWindow.h"
#include "mxMessageDialog.h"

MenusAndToolsConfig *menu_data;
#if defined(__APPLE__)
	#define _if_not_apple(a,b) b
#else
	#define _if_not_apple(a,b) a
#endif
#if defined(__WIN32__)
	#define _if_win32(a,b) a
#else
	#define _if_win32(a,b) b
#endif

MenusAndToolsConfig::MenusAndToolsConfig () {
//	tools_custom_item=new wxMenuItem*[10];
//	for (int i=0;i<10;i++) tools_custom_item[i] = NULL;
	file_source_history = new wxMenuItem*[CM_HISTORY_MAX_LEN];
	for (int i=0;i<CM_HISTORY_MAX_LEN;i++) file_source_history[i]=NULL;
	file_project_history = new wxMenuItem*[CM_HISTORY_MAX_LEN];
	for (int i=0;i<CM_HISTORY_MAX_LEN;i++) file_project_history[i]=NULL;
}

void MenusAndToolsConfig::LoadMenuData ( ) {
	
	menues[mnFILE].label = LANG(MENUITEM_FILE,"&Archivo"); {
		AddMenuItem(mnFILE, myMenuItem(wxID_NEW, LANG(MENUITEM_FILE_NEW,"&Nuevo...")).ShortCut("Ctrl+N").Description("Crear un nuevo archivo").Icon("nuevo.png"));
		AddMenuItem(mnFILE, myMenuItem(mxID_FILE_PROJECT, LANG(MENUITEM_FILE_NEW_PROJECT,"&Nuevo Proyecto...")).ShortCut("Ctrl+Shift+N").Description("Crear un nuevo proyecto").Icon("proyecto.png"));
		AddMenuItem(mnFILE, myMenuItem(wxID_OPEN, LANG(MENUITEM_FILE_OPEN,"&Abrir...")).ShortCut("Ctrl+O").Description("Abrir un archivo o un proyecto existente...").Icon("abrir.png").Map());
		BeginSubMenu(mnFILE,LANG(MENUITEM_FILE_RECENT_SOURCES,"Fuentes Abiertos Recientemente"),"Muestra los ultimos archivos abiertos como programas simples","recentSimple.png",mxID_FILE_SOURCE_RECENT,maMAPPED);
			AddSeparator(mnFILE);
			AddMenuItem(mnFILE, myMenuItem(mxID_FILE_SOURCE_HISTORY_MORE,LANG(MENU_FILE_RECENT_MORE,"Mas...")).Description("Muestra un dialogo con la lista completa de archivos recientes").Icon("recentMore.png"));
		EndSubMenu(mnFILE);
		BeginSubMenu(mnFILE,LANG(MENUITEM_FILE_RECENT_PROJECTS,"Proyectos Abiertos Recientemente"),"Muestra los ultimos proyectos abiertos","recentProject.png",mxID_FILE_PROJECT_RECENT,maMAPPED);
			AddSeparator(mnFILE);
			AddMenuItem(mnFILE, myMenuItem(mxID_FILE_PROJECT_HISTORY_MORE,LANG(MENU_FILE_RECENT_MORE,"Mas...")).Description("Muestra un dialogo con la lista completa de archivos recientes").Icon("recentMore.png"));
		EndSubMenu(mnFILE);
		AddMenuItem(mnFILE, myMenuItem(wxID_SAVE, LANG(MENUITEM_FILE_SAVE,"&Guardar")).ShortCut("Ctrl+S").Description("Guardar el archivo actual").Icon("guardar.png"));
		AddMenuItem(mnFILE, myMenuItem(wxID_SAVEAS, LANG(MENUITEM_FILE_SAVE_AS,"G&uardar Como...")).ShortCut("Ctrl+Shift+S").Description("Guardar el archivo actual con otro nombre...").Icon("guardarComo.png"));
		AddMenuItem(mnFILE, myMenuItem(mxID_FILE_SAVE_ALL, LANG(MENUITEM_FILE_SAVE_ALL,"Guardar &Todo...")).ShortCut("Ctrl+Alt+Shift+S").Description("Guarda todos los archivos abiertos y el proyecto actual...").Icon("guardarTodo.png"));
		AddMenuItem(mnFILE, myMenuItem(mxID_FILE_SAVE_PROJECT, LANG(MENUITEM_FILE_SAVE_PROJECT,"Guar&dar Proyecto")).ShortCut("Ctrl+Alt+S").Description("Guardar la configuaricion actual del proyecto").Icon("guardarProyecto.png").Project(true));
		AddMenuItem(mnFILE, myMenuItem(mxID_FILE_EXPORT_HTML, LANG(MENUITEM_FILE_EXPORT_HTML,"Exportar a HTML...")).Description("Genera un archiv HTML con el codigo fuente").Icon("exportHtml.png"));
		AddMenuItem(mnFILE, myMenuItem(mxID_FILE_PRINT, LANG(MENUITEM_FILE_PRINT,"&Imprimir...")).Description("Imprime el codigo fuente actual").Icon("imprimir.png"));
		AddMenuItem(mnFILE, myMenuItem(mxID_FILE_RELOAD, LANG(MENUITEM_FILE_RELOAD,"&Recargar")).ShortCut("Ctrl+Shift+R").Description("Recarga la version en disco del archivo actual.").Icon("recargar.png"));
		AddMenuItem(mnFILE, myMenuItem(wxID_CLOSE, LANG(MENUITEM_FILE_CLOSE,"&Cerrar")).ShortCut("Ctrl+W").Description("Cerrar el archivo actual").Icon("cerrar.png"));
		AddMenuItem(mnFILE, myMenuItem(mxID_FILE_CLOSE_ALL, LANG(MENUITEM_FILE_CLOSE_ALL,"Cerrar &Todo")).ShortCut("Ctrl+Alt+Shift+W").Description("Cierra todos los archivos abiertos").Icon("cerrarTodo.png"));
		AddMenuItem(mnFILE, myMenuItem(mxID_FILE_CLOSE_PROJECT, LANG(MENUITEM_FILE_CLOSE_PROJECT,"Cerrar Pro&yecto")).ShortCut("Ctrl+Shift+W").Description("Cierra el proyecto actual").Icon("cerrarProyecto.png").Project(true));
		AddSeparator(mnFILE);
		AddMenuItem(mnFILE, myMenuItem(mxID_FILE_PROJECT_CONFIG, LANG(MENUITEM_FILE_PROJECT_CONFIG,"&Configuracion del Proyecto...")).ShortCut("Ctrl+Shift+P").Description("Configurar las propiedades generales de un proyecto...").Icon("projectConfig.png").Project(true));
		AddMenuItem(mnFILE, myMenuItem(mxID_FILE_PREFERENCES, LANG(MENUITEM_FILE_PREFERENCES,"&Preferencias...")).ShortCut("Ctrl+P").Description("Configurar el entorno...").Icon("preferencias.png"));
		AddSeparator(mnFILE);
		AddMenuItem(mnFILE, myMenuItem(wxID_EXIT, LANG(MENUITEM_FILE_EXIT,"&Salir")).ShortCut("Alt+F4").Description("Salir del programa!").Icon("salir.png"));
	}
	
	
	menues[mnEDIT].label = LANG(MENUITEM_EDIT,"&Edicion"); {
		AddMenuItem(mnEDIT, myMenuItem(wxID_UNDO, LANG(MENUITEM_EDIT_UNDO,"&Deshacer")).ShortCut("Ctrl+Z").Description("Deshacer el ultimo cambio").Icon("deshacer.png"));
		AddMenuItem(mnEDIT, myMenuItem(wxID_REDO, LANG(MENUITEM_EDIT_REDO,"&Rehacer")).ShortCut("Ctrl+Shift+Z").Description("Rehacer el ultimo cambio desecho").Icon("rehacer.png"));
		AddSeparator(mnEDIT);
		AddMenuItem(mnEDIT, myMenuItem(wxID_CUT, LANG(MENUITEM_EDIT_CUT,"C&ortar")).ShortCut("Ctrl+X").Description("Cortar la seleccion al portapapeles").Icon("cortar.png"));
		AddMenuItem(mnEDIT, myMenuItem(wxID_COPY, LANG(MENUITEM_EDIT_COPY,"&Copiar")).ShortCut("Ctrl+C").Description("Copiar la seleccion al portapapeles").Icon("copiar.png"));
		AddMenuItem(mnEDIT, myMenuItem(wxID_PASTE, LANG(MENUITEM_EDIT_PASTE,"&Pegar")).ShortCut("Ctrl+V").Description("Pegar el contenido del portapapeles").Icon("pegar.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_TOGGLE_LINES_UP, LANG(MENUITEM_EDIT_LINES_UP,"Mover Hacia Arriba")).ShortCut("Ctrl+T").Description("Mueve la o las lineas seleccionadas hacia arriba").Icon("toggleLinesUp.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_TOGGLE_LINES_DOWN, LANG(MENUITEM_EDIT_LINES_DOWN,"Mover Hacia Abajo")).ShortCut("Ctrl+Shift+T").Description("Mueve la o las lineas seleccionadas hacia abajo").Icon("toggleLinesDown.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_DUPLICATE_LINES, LANG(MENUITEM_EDIT_DUPLICATE_LINES,"&Duplicar Linea(s)")).ShortCut("Ctrl+L").Description("Copia la linea actual del cursor, o las lineas seleccionadas, nuevamente a continuacion").Icon("duplicarLineas.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_DELETE_LINES, LANG(MENUITEM_EDIT_DELETE_LINES,"&Eliminar Linea(s)")).ShortCut("Shift+Ctrl+L").Description("Elimina la linea actual del cursor nuevamente, o las lineas seleccionadas").Icon("borrarLineas.png"));
		AddSeparator(mnEDIT);
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_GOTO_FUNCTION, LANG(MENUITEM_EDIT_GOTO_FUNCTION,"&Ir a Funcion/Clase/Metodo...")).ShortCut("Ctrl+Shift+G").Description("Abrir el fuente con la declaracion de una funcion, clase o metodo...").Icon("irAFuncion.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_GOTO_FILE, LANG(MENUITEM_EDIT_GOTO_FILE,"&Ir a Archivo...")).ShortCut("Ctrl+Shift+F").Description("Abrir un archivo en particular buscandolo por parte de su nombre...").Icon("irAArchivo.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_GOTO, LANG(MENUITEM_EDIT_GOTO_LINE,"&Ir a Linea...")).ShortCut("Ctrl+G").Description("Mover el cursor a una linea determinada en el archivo...").Icon("irALinea.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_FIND, LANG(MENUITEM_EDIT_FIND,"&Buscar...")).ShortCut("Ctrl+F").Description("Buscar una cadena en el archivo...").Icon("buscar.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_FIND_PREV, LANG(MENUITEM_EDIT_FIND_PREV,"Buscar &Anterior")).ShortCut("Shift+F3").Description("Repetir la ultima busqueda a partir del cursor hacia atras").Icon("buscarAnterior.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_FIND_NEXT, LANG(MENUITEM_EDIT_FIND_NEXT,"Buscar &Siguiente")).ShortCut("F3").Description("Repetir la ultima busqueda a partir del cursor").Icon("buscarSiguiente.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_REPLACE, LANG(MENUITEM_EDIT_REPLACE,"&Reemplazar...")).ShortCut("Ctrl+R").Description("Reemplazar una cadena con otra en el archivo...").Icon("reemplazar.png"));
		AddSeparator(mnEDIT);
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_INSERT_HEADER, LANG(MENUITEM_EDIT_INSERT_INCLUDE,"Insertar #include Correspondiente")).ShortCut("Ctrl+H").Description("Si es posible, inserta el #include necesario para utilizar la funcion/clase en la cual se encuentra el cursor.").Icon("insertarInclude.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_COMMENT, LANG(MENUITEM_EDIT_COMMENT,"Comentar")).ShortCut("Ctrl+D").Description("Convierte el texto seleccionado en comentario anadiendo \"//\" a cada linea").Icon("comentar.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_UNCOMMENT, LANG(MENUITEM_EDIT_UNCOMMENT,"Descomentar")).ShortCut("Shift+Ctrl+D").Description("Descomente el texto seleccionado eliminando \"//\" de cada linea").Icon("descomentar.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_INDENT, LANG(MENUITEM_EDIT_INDENT,"Indentar Blo&que")).ShortCut("Ctrl+I").Description("Corrige el indentado de un bloque de codigo agregando o quitando tabs segun corresponda").Icon("indent.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_BRACEMATCH, LANG(MENUITEM_EDIT_BRACEMATCH,"Seleccionar Blo&que")).ShortCut("Ctrl+M").Description("Seleccionar todo el bloque correspondiente a la llave o parentesis sobre el cursor").Icon("mostrarLlave.png"));
		AddMenuItem(mnEDIT, myMenuItem(wxID_SELECTALL, LANG(MENUITEM_EDIT_SELECT_ALL,"&Seleccionar Todo")).ShortCut("Ctrl+A").Description("Seleccionar todo el contenido del archivo").Icon("seleccionarTodo.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_MARK_LINES, LANG(MENUITEM_EDIT_HIGHLIGHT_LINES,"&Resaltar Linea(s)/Quitar Resaltado")).ShortCut("Ctrl+B").Description("Resalta la linea pintandola de otro color").Icon("marcar.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_GOTO_MARK, LANG(MENUITEM_EDIT_FIND_HIGHLIGHTS,"Buscar &Resaltado")).ShortCut("Ctrl+Shift+B").Description("Mueve el cursor a la siguiente linea resaltada").Icon("irAMarca.png"));
		AddMenuItem(mnEDIT, myMenuItem(mxID_EDIT_LIST_MARKS, LANG(MENUITEM_EDIT_LIST_HIGHLIGHTS,"&Listar Lineas Resaltadas")).ShortCut("Ctrl+Alt+B").Description("Muestra una lista de las lineas marcadas en todos los archivos").Icon("listarMarcas.png"));
	}

	
	menues[mnVIEW].label = LANG(MENUITEM_VIEW,_if_not_apple("&Ver","Ver")); {
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_DUPLICATE_TAB, LANG(MENUITEM_VIEW_SPLIT_VIEW,"&Duplicar vista")).Icon("duplicarVista.png"));
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_LINE_WRAP, LANG(MENUITEM_VIEW_LINE_WRAP,"&Ajuste de linea")).ShortCut("Alt+F11").Description("Muestra las lineas largas como en varios renglones").Icon("lineWrap.png").Checkeable(false));	
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_WHITE_SPACE, LANG(MENUITEM_VIEW_WHITE_SPACES,"Mostrar espacios y caracteres de &fin de linea")).Description("Muestra las lineas largas como en varios renglones").Icon("whiteSpace.png").Checkeable(false));	
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_CODE_STYLE, LANG(MENUITEM_VIEW_SYNTAX_HIGHLIGHT,"&Colorear Sintaxis")).ShortCut("Shift+F11").Description("Resalta el codigo con diferentes colores y formatos de fuente.").Icon("syntaxColour.png").Checkeable(false));	
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_CODE_COLOURS, LANG(MENUITEM_VIEW_CODE_COLOURS,"Configurar esquema de colores...")).Icon("preferencias.png"));
		BeginSubMenu(mnVIEW,LANG(MENUITEM_VIEW_FOLDING,"Plegado"),"Muestra opciones para plegar y desplegar codigo en distintos niveles","folding.png");
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_FOLD,LANG(MENUITEM_FOLD_FOLD_THIS_LINE,"Plegar en esta linea")).ShortCut(_if_not_apple("Alt+Up","")).Icon("foldOne.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_UNFOLD,LANG(MENUITEM_FOLD_UNFOLD_THIS_LINE,"Desplegar en esta linea")).ShortCut(_if_not_apple("Alt+Down","")).Icon("unfoldOne.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_HIDE_1,LANG(MENUITEM_FOLD_FOLD_LEVEL_1,"Plegar el primer nivel")).ShortCut(_if_not_apple("Ctrl+1","")).Description("Cierra todos los bolques del primer nivel").Icon("fold1.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_HIDE_2,LANG(MENUITEM_FOLD_FOLD_LEVEL_2,"Plegar el segundo nivel")).ShortCut(_if_not_apple("Ctrl+2","")).Description("Cierra todos los bolques del segundo nivel").Icon("fold2.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_HIDE_3,LANG(MENUITEM_FOLD_FOLD_LEVEL_3,"Plegar el tercer nivel")).ShortCut(_if_not_apple("Ctrl+3","")).Description("Cierra todos los bolques del tercer nivel").Icon("fold3.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_HIDE_4,LANG(MENUITEM_FOLD_FOLD_LEVEL_4,"Plegar el cuarto nivel")).ShortCut(_if_not_apple("Ctrl+4","")).Description("Cierra todos los bolques del cuarto nivel").Icon("fold4.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_HIDE_5,LANG(MENUITEM_FOLD_FOLD_LEVEL_5,"Plegar el quinto nivel")).ShortCut(_if_not_apple("Ctrl+5","")).Description("Cierra todos los bolques del quinto nivel").Icon("fold5.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_HIDE_ALL,LANG(MENUITEM_FOLD_FOLD_ALL_LEVELS,"Plegar todos los niveles")).ShortCut(_if_not_apple("Ctrl+0","")).Description("Cierra todos los bolques de todos los niveles").Icon("foldAll.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_SHOW_1,LANG(MENUITEM_FOLD_UNFOLD_LEVEL_1,"Desplegar el primer nivel")).ShortCut(_if_not_apple("Alt+1","")).Description("Abre todos los bolques del primer nivel").Icon("unfold1.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_SHOW_2,LANG(MENUITEM_FOLD_UNFOLD_LEVEL_2,"Desplegar el segundo nivel")).ShortCut(_if_not_apple("Alt+2","")).Description("Abre todos los bolques del segundo nivel").Icon("unfold2.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_SHOW_3,LANG(MENUITEM_FOLD_UNFOLD_LEVEL_3,"Desplegar el tercer nivel")).ShortCut(_if_not_apple("Alt+3","")).Description("Abre todos los bolques del tercer nivel").Icon("unfold3.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_SHOW_4,LANG(MENUITEM_FOLD_UNFOLD_LEVEL_4,"Desplegar el cuarto nivel")).ShortCut(_if_not_apple("Alt+4","")).Description("Abre todos los bolques del cuarto nivel").Icon("unfold4.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_SHOW_5,LANG(MENUITEM_FOLD_UNFOLD_LEVEL_5,"Desplegar el quinto nivel")).ShortCut(_if_not_apple("Alt+5","")).Description("Abre todos los bolques del quinto nivel").Icon("unfold5.png"));
			AddMenuItem(mnVIEW, myMenuItem(mxID_FOLD_SHOW_ALL,LANG(MENUITEM_FOLD_UNFOLD_ALL_LEVELS,"Desplegar todos los niveles")).ShortCut(_if_not_apple("Alt+0","")).Description("Abre todos los bolques de todos los niveles").Icon("unfoldAll.png"));
		EndSubMenu(mnVIEW);
		AddSeparator(mnVIEW);
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_FULLSCREEN, LANG(MENUITEM_VIEW_FULLSCREEN,"Ver a Pantalla &Completa")).ShortCut("F11").Description("Muestra el editor a pantalla completa, ocultando tambien los demas paneles").Icon("fullScreen.png").Checkeable(false));
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_BEGINNER_PANEL, LANG(MENUITEM_VIEW_BEGINNER_PANEL,"Mostrar Panel de Mini-Plantillas")).Description("Muestra un panel con plantillas y estructuras basicas de c++").Icon("beginer_panel.png").Checkeable(false));
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_LEFT_PANELS, LANG(MENUITEM_VIEW_LEFT_PANELS,"&Mostrar Panel de Arboles")).Description("Muestra el panel con los arboles de proyecto, simbolos y explorador de archivos").Checkeable(false));
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_PROJECT_TREE, LANG(MENUITEM_VIEW_PROJECT_TREE,"&Mostrar Arbol de &Proyecto")).Description("Muestra el panel del arbol de proyecto/archivos abiertos").Icon("projectTree.png").Checkeable(false));
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_EXPLORER_TREE, LANG(MENUITEM_VIEW_EXPLORER_TREE,"Mostrar &Explorardor de Archivos")).ShortCut("Ctrl+E").Description("Muestra el panel explorador de archivos").Icon("explorerTree.png").Checkeable(false));
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_SYMBOLS_TREE, LANG(MENUITEM_VIEW_SYMBOLS_TREE,"Mostrar Arbol de &Simbolos")).Description("Analiza el codigo fuente y construye un arbol con los simbolos declarados en el mismo.").Icon("symbolsTree.png").Checkeable(false));
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_COMPILER_TREE, LANG(MENUITEM_VIEW_COMPILER_TREE,"&Mostrar Resultados de la Compilacion")).Description("Muestra un panel con la salida del compilador").Icon("compilerTree.png").Checkeable(false));
		BeginSubMenu(mnVIEW, LANG(MENUITEM_VIEW_TOOLBARS,"Barras de herramientas"));
			// los atributos de Checkeable se setean m�s tarde porque a esta altura todav�a no se ley� la configuracion
			AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_TOOLBAR_FILE, LANG(MENUITEM_VIEW_TOOLBAR_FILE,"&Mostrar Barra de Herramientas Archivo")).Description("Muestra la barra de herramientas para el manejo de archivos")/*.Checkeable(_toolbar_visible(tbFILE))*/);
			AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_TOOLBAR_EDIT, LANG(MENUITEM_VIEW_TOOLBAR_EDIT,"&Mostrar Barra de Herramientas Edicion")).Description("Muestra la barra de herramientas para la edicion del fuente")/*.Checkeable(_toolbar_visible(tbEDIT))*/);
			AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_TOOLBAR_VIEW, LANG(MENUITEM_VIEW_TOOLBAR_VIEW,"&Mostrar Barra de Herramientas Ver")).Description("Muestra la barra de herramientas para las opciones de visualizacion")/*.Checkeable(_toolbar_visible(tbVIEW))*/);
			AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_TOOLBAR_FIND, LANG(MENUITEM_VIEW_TOOLBAR_FIND,"&Mostrar Barra de Busqueda Rapida")).Description("Muestra un cuadro de texto en la barra de herramientas que permite buscar rapidamente en un fuente")/*.Checkeable(_toolbar_visible(tbFIND))*/);
			AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_TOOLBAR_RUN, LANG(MENUITEM_VIEW_TOOLBAR_RUN,"&Mostrar Barra de Herramientas Ejecucion")).Description("Muestra la barra de herramientas para la compilacion y ejecucion del programa")/*.Checkeable(_toolbar_visible(tbRUN))*/);
			AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_TOOLBAR_TOOLS, LANG(MENUITEM_VIEW_TOOLBAR_TOOLS,"&Mostrar Barra de Herramientas Herramientas")).Description("Muestra la barra de herramientas para las herramientas adicionales")/*.Checkeable(_toolbar_visible(tbTOOLS))*/);
			AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_TOOLBAR_PROJECT, LANG(MENUITEM_VIEW_TOOLBAR_PROJECT,"&Mostrar Barra de Herramientas Proyecto")).Description("Muestra la barra de herramientas para las herramientas personalizables propias del proyecto")/*.Checkeable(_toolbar_visible(tbPROJECT))*/.Project(true));
			AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_TOOLBAR_DEBUG, LANG(MENUITEM_VIEW_TOOLBAR_DEBUG,"&Mostrar Barra de Herramientas Depuracion")).Description("Muestra la barra de herramientas para la depuracion del programa")/*.Checkeable(_toolbar_visible(tbDEBUG))*/);
			AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_TOOLBAR_MISC, LANG(MENUITEM_VIEW_TOOLBAR_MISC,"&Mostrar Barra de Herramientas Miscelanea")).Description("Muestra la barra de herramientas con commandos miselaneos")/*.Checkeable(_toolbar_visible(tbMISC))*/);
			AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_TOOLBARS_CONFIG, LANG(MENUITEM_VIEW_TOOLBARS_CONFIG,"&Configurar...")).Icon("preferencias.png"));
		EndSubMenu(mnVIEW);
		AddSeparator(mnVIEW);
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_PREV_ERROR, LANG(MENUITEM_VIEW_PREV_ERROR,"&Ir a error anterior")).ShortCut(_if_win32("Ctrl+>","Ctrl+Shift+<")).Description("Selecciona el error/advertencia anterior de la salida del compilador.").Icon("errorPrev.png"));
		AddMenuItem(mnVIEW, myMenuItem(mxID_VIEW_NEXT_ERROR, LANG(MENUITEM_VIEW_NEXT_ERROR,"&Ir a siguiente error")).ShortCut("Ctrl+<").Description("Selecciona el proximo error/advertencia de la salida del compilador.").Icon("errorNext.png"));
	}
	
	
	menues[mnRUN].label = LANG(MENUITEM_RUN,"E&jecucion"); {
		AddMenuItem(mnRUN, myMenuItem( mxID_RUN_RUN, LANG(MENUITEM_RUN_RUN,"&Ejecutar...")).ShortCut("F9").Description("Guarda y compila si es necesario, luego ejecuta el programa").Icon("ejecutar.png").Map());
		AddMenuItem(mnRUN, myMenuItem( mxID_RUN_RUN_OLD, LANG(MENUITEM_RUN_OLD,"Ejecutar (sin recompilar)...")).ShortCut("Ctrl+F9").Description("Ejecuta el binario existente sin recompilar primero").Icon("ejecutar_old.png"));
		AddMenuItem(mnRUN, myMenuItem( mxID_RUN_COMPILE, LANG(MENUITEM_RUN_COMPILE,"&Compilar")).ShortCut("Shift+F9").Description("Guarda y compila el fuente actual").Icon("compilar.png").Map());
		AddMenuItem(mnRUN, myMenuItem( mxID_RUN_CLEAN, LANG(MENUITEM_RUN_CLEAN,"&Limpiar")).ShortCut("Ctrl+Shift+F9").Description("Elimina los objetos y ejecutables compilados").Icon("limpiar.png").Map());
		AddMenuItem(mnRUN, myMenuItem( mxID_RUN_STOP, LANG(MENUITEM_RUN_STOP,"&Detener")).Description("Detiene la ejecucion del programa").Icon("detener.png").Map());
		AddMenuItem(mnRUN, myMenuItem( mxID_RUN_CONFIG, LANG(MENUITEM_RUN_OPTIONS,"&Opciones...")).ShortCut("Alt+F9").Description("Configura la compilacion y ejecucion de los programas").Icon("opciones.png"));
	}
	
	
	menues[mnDEBUG].label = LANG(MENUITEM_DEBUG,"&Depuracion"); {
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_RUN, LANG(MENUITEM_DEBUG_START,"&Iniciar/Continuar")).ShortCut("F5").Icon("depurar.png"));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_PAUSE, LANG(MENUITEM_DEBUG_PAUSE,"Interrum&pir")).Icon("pausar.png").Debug(true));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_STOP, LANG(MENUITEM_DEBUG_STOP,"&Detener")).ShortCut("Shift+F5").Icon("detener.png").Debug(true));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_STEP_IN, LANG(MENUITEM_DEBUG_STEP_IN,"Step &In")).ShortCut("F6").Icon("step_in.png").Debug(true));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_STEP_OVER, LANG(MENUITEM_DEBUG_STEP_OVER,"Step &Over")).ShortCut("F7").Icon("step_over.png").Debug(true));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_STEP_OUT, LANG(MENUITEM_DEBUG_STEP_OUT,"Step O&ut")).ShortCut("Shift+F6").Icon("step_out.png").Debug(true));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_RUN_UNTIL, LANG(MENUITEM_DEBUG_RUN_UNTIL,"Ejecutar &Hasta el Cursor")).ShortCut("Shift+F7").Icon("run_until.png").Debug(true));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_RETURN, LANG(MENUITEM_DEBUG_RETURN,"&Return")).ShortCut("Ctrl+F6").Icon("return.png").Debug(true));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_JUMP, LANG(MENUITEM_DEBUG_JUMP,"Continuar Desde Aqui")).ShortCut("Ctrl+F5").Icon("debug_jump.png").Debug(true));
		AddSeparator(mnDEBUG);
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_TOGGLE_BREAKPOINT, LANG(MENUITEM_DEBUG_TOGGLE_BREAKPOINT,"&Agregar/quitar Breakpoint")).ShortCut("F8").Icon("breakpoint.png"));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_BREAKPOINT_OPTIONS, LANG(MENUITEM_DEBUG_BREAKPOINT_OPTIONS,"&Opciones del Breakpoint...")).ShortCut("Ctrl+F8").Icon("breakpoint_options.png"));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_LIST_BREAKPOINTS, LANG(MENUITEM_DEBUG_LIST_BREAKPOINTS,"&Listar Watch/Break points...")).ShortCut("Shift+F8").Icon("breakpoint_list.png"));
		AddSeparator(mnDEBUG);
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_INSPECT, LANG(MENUITEM_DEBUG_INSPECT,"Panel de In&specciones")).Icon("inspect.png"));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_BACKTRACE, LANG(MENUITEM_DEBUG_BACKTRACE,"&Trazado Inverso")).Icon("backtrace.png"));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_THREADLIST, LANG(MENUITEM_DEBUG_THREADLIST,"&Hilos de Ejecucion")).Icon("threadlist.png"));
		AddMenuItem(mnDEBUG, myMenuItem( mxID_DEBUG_LOG_PANEL, LANG(MENUITEM_DEBUG_SHOW_LOG_PANEL,"&Mostrar mensajes del depurador")).Icon("debug_log_panel.png"));
		AddSeparator(mnDEBUG);
#ifndef __WIN32__
		BeginSubMenu(mnDEBUG, LANG(MENUITEM_DEBUG_MORE,"M�s..."));
			AddMenuItem(mnDEBUG, myMenuItem(mxID_DEBUG_ATTACH, LANG(MENUITEM_DEBUG_ATTACH,"&Adjuntar...")).Icon("debug_attach.png").Debug(false));
			AddMenuItem(mnDEBUG, myMenuItem(mxID_DEBUG_CORE_DUMP, LANG(MENUITEM_DEBUG_LOAD_CORE_DUMP,"Cargar &Volcado de Memoria...")).Icon("core_dump.png").Debug(false));
			AddMenuItem(mnDEBUG, myMenuItem(mxID_DEBUG_CORE_DUMP,LANG(MENUITEM_SAVE_CORE_DUMP,"Guardar &Volcado de Memoria...")).Icon("core_dump.png").Debug(true));
			AddMenuItem(mnDEBUG, myMenuItem(mxID_DEBUG_ENABLE_INVERSE_EXEC, LANG(MENUITEM_DEBUG_ENABLE_INVERSE,"Habilitar Ejecucion Hacia Atras")).Icon("reverse_enable.png").Checkeable(false).Debug(true));
			AddMenuItem(mnDEBUG, myMenuItem(mxID_DEBUG_INVERSE_EXEC, LANG(MENUITEM_DEBUG_INVERSE,"Ejecutar Hacia Atras")).Icon("reverse_toggle.png").Checkeable(false).Debug(true));
			AddMenuItem(mnDEBUG, myMenuItem(mxID_DEBUG_SET_SIGNALS, LANG(MENUITEM_DEBUG_SET_SIGNALS,"Configurar comportamiento ante se�ales...")).Icon("debug_set_signals.png"));
			AddMenuItem(mnDEBUG, myMenuItem(mxID_DEBUG_SEND_SIGNAL, LANG(MENUITEM_DEBUG_SEND_SIGNALS,"Enviar se�al...")).Icon("debug_send_signal.png").Debug(true));
			AddMenuItem(mnDEBUG, myMenuItem(mxID_DEBUG_GDB_COMMAND, LANG(MENUITEM_DEBUG_GDB_COMMAND,"Introducir comandos gdb...")).Icon("gdb_command.png").Debug(true));
			AddMenuItem(mnDEBUG, myMenuItem(mxID_DEBUG_PATCH, LANG(MENUITEM_DEBUG_PATCH,"Actualizar ejecutable (experimental)...")).Icon("debug_patch.png").Debug(true));
		EndSubMenu(mnDEBUG);
#endif
	}
	
	
	menues[mnTOOLS].label = LANG(MENUITEM_TOOLS,"&Herramientas"); {
		AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DRAW_FLOW, LANG(MENUITEM_TOOLS_DRAW_FLOWCHART,"Dibujar Diagrama de &Flujo...")).Description("Genera un diagrama de flujo a partir del bloque de codigo actual").Icon("flujo.png"));
		AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DRAW_CLASSES, LANG(MENUITEM_TOOLS_DRAW_CLASS_HIERARCHY,"Dibujar &Jerarquia de Clases...")).Icon("clases.png"));
		
		AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_CODE_COPY_FROM_H, LANG(MENUITEM_TOOLS_CODE_COPY_FROM_H,"Implementar M�todos/Funciones faltantes...")).ShortCut("Ctrl+Shift+H").Icon("copy_code_from_h.png"));
		
		BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_COMMENTS,"Coment&arios"),"Permite alinear o quitar los comentarios del codigo","comments.png");
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_ALIGN_COMMENTS, LANG(MENUITEM_TOOLS_COMMENTS_ALIGN_COMMENTS,"&Alinear Comentarios...")).Description("Mueve todos los comentarios hacia una determinada columna").Icon("align_comments.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_EDIT_COMMENT, LANG(MENUITEM_TOOLS_COMMENTS_COMMENT,"&Comentar")).Description("Convierte el texto seleccionado en comentario anadiendo \"//\" a cada linea").Icon("comentar.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_EDIT_UNCOMMENT, LANG(MENUITEM_TOOLS_COMMENTS_UNCOMMENT,"&Descomentar")).Description("Descomente el texto seleccionado eliminando \"//\" de cada linea").Icon("descomentar.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_REMOVE_COMMENTS, LANG(MENUITEM_TOOLS_COMMENTS_DELETE_COMMENTS,"&Eliminar Comentarios")).Description("Quita todos los comentarios del codigo fuente o de la seleccion").Icon("remove_comments.png"));
		EndSubMenu(mnTOOLS);
		
		BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_PREPROC,"Preprocesador"),"Muestra informaci�n generada por el preprocesador de C++","preproc.png");
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_PREPROC_EXPAND_MACROS, LANG(MENUITEM_TOOLS_PREPROC_EXPAND_MACROS,"Expandir Macros")).ShortCut("Ctrl+Shift+M").Icon("preproc_expand_macros.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_PREPROC_MARK_VALID, LANG(MENUITEM_TOOLS_PREPROC_MARK_VALID,"Marcar Lineas No Compiladas")).ShortCut("Ctrl+Alt+M").Icon("preproc_mark_valid.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_PREPROC_UNMARK_ALL, LANG(MENUITEM_TOOLS_PREPROC_UNMARK_ALL,"Borrar Marcas")).ShortCut("Ctrl+Alt+Shift+M").Icon("preproc_unmark_all.png"));
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_PREPROC_HELP, LANG(MENUITEM_TOOLS_PREPROC_HELP,"Ayuda...")).Icon("ayuda.png"));
		EndSubMenu(mnTOOLS);
		
		AddSeparator(mnTOOLS);
		
		AddMenuItem(mnTOOLS, myMenuItem( mxID_TOOLS_MAKEFILE, LANG(MENUITEM_TOOLS_GENERATE_MAKEFILE,"&Generar Makefile...")).Description("Genera el Makefile a partir de los fuentes y la configuracion seleccionada").Icon("makefile.png").Project(true));
		AddMenuItem(mnTOOLS, myMenuItem( mxID_TOOLS_CONSOLE, LANG(MENUITEM_TOOLS_OPEN_TERMINAL,"Abrir Co&nsola...")).Description("Inicia una terminal para interactuar con el interprete de comandos del sistema operativo").Icon("console.png"));
		AddMenuItem(mnTOOLS, myMenuItem( mxID_TOOLS_EXE_PROPS, LANG(MENUITEM_TOOLS_EXE_INFO,"&Propiedades del Ejecutable...")).Description("Muestra informacion sobre el archivo compilado").Icon("exeinfo.png"));
		AddMenuItem(mnTOOLS, myMenuItem( mxID_TOOLS_PROJECT_STATISTICS, LANG(MENUITEM_TOOLS_PROJECT_STATISTICS,"E&stadisticas del Proyecto...")).Description("Muestra informacion estadistica sobre los fuentes y demas archivos del proyecto").Icon("proystats.png").Project(true));
		AddMenuItem(mnTOOLS, myMenuItem( mxID_TOOLS_DRAW_PROJECT, LANG(MENUITEM_TOOLS_DRAW_PROJECT,"Grafo del Proyecto...")).Icon("draw_project.png").Project(true));
		
		BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_SHARE,"Compartir Archivos en la &Red Local"),"Permite enviar o recibir codigos fuentes a traves de una red LAN","share.png");
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_SHARE_OPEN, LANG(MENUITEM_TOOLS_SHARE_OPEN,"&Abrir compartido...")).Description("Abre un archivo compartido por otra PC en la red local.").Icon("abrirs.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_SHARE_SHARE, LANG(MENUITEM_TOOLS_SHARE_SHARE,"&Compartir actual...")).Description("Comparte el archivo en la red local.").Icon("compartir.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_SHARE_LIST, LANG(MENUITEM_TOOLS_SHARE_LIST,"&Ver lista de compartidos propios...")).Description("Comparte el archivo en la red local.").Icon("share_list.png"));
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_SHARE_HELP, LANG(MENUITEM_TOOLS_SHARE_HELP,"A&yuda...")).Description("Muestra ayuda acerca de la comparticion de archivos en ZinjaI").Icon("ayuda.png"));
		EndSubMenu(mnTOOLS);
		
		AddSeparator(mnTOOLS);
		
		BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_DIFF,"&Comparar Archivos (diff)"),"Muestra opciones para plegar y desplegar codigo en distintos niveles","diff.png");
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DIFF_TWO,LANG(MENUITEM_TOOLS_DIFF_TWO,"&Dos fuentes abiertos...")).Description("Compara dos archivos de texto abiertos y los colorea segun sus diferencias").Icon("diff_sources.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DIFF_DISK,LANG(MENUITEM_TOOLS_DIFF_DISK,"&Fuente actual contra archivo en disco...")).Description("Compara un archivo abierto contra un archivo en disco y lo colorea segun sus diferencias").Icon("diff_source_file.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DIFF_HIMSELF,LANG(MENUITEM_TOOLS_DIFF_HIMSELF,"&Cambios en fuente actual contra su version en disco...")).Description("Compara un archivos abierto y modificado contra su version en disco y lo colorea segun sus diferencias").Icon("diff_source_himself.png"));
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DIFF_PREV,LANG(MENUITEM_TOOLS_DIFF_PREV,"Ir a Diferencia Anterior")).ShortCut("Shift+Alt+PageUp").Icon("diff_prev.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DIFF_NEXT,LANG(MENUITEM_TOOLS_DIFF_NEXT,"Ir a Siguiente Diferencia")).ShortCut("Shift+Alt+PageDown").Icon("diff_next.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DIFF_SHOW,LANG(MENUITEM_TOOLS_DIFF_SHOW,"Mostrar Cambio")).ShortCut("Alt+Shift+Ins").Description("Muestra en un globo emergente el cambio a aplicar").Icon("diff_show.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DIFF_APPLY,LANG(MENUITEM_TOOLS_DIFF_APPLY,"Apl&icar Cambio")).ShortCut("Alt+Ins").Description("Aplica el cambio marcado en la linea actual").Icon("diff_apply.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DIFF_DISCARD,LANG(MENUITEM_TOOLS_DIFF_DISCARD,"De&scartar Cambio")).ShortCut("Alt+Del").Description("Descarta el cambio marcado en la linea actual").Icon("diff_discard.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DIFF_CLEAR,LANG(MENUITEM_TOOLS_DIFF_CLEAR,"&Borrar Marcas")).ShortCut("Alt+Shift+Del").Description("Quita los colores y marcas que se agregaron en un fuente producto de una comparacion").Icon("diff_clear.png"));
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DIFF_HELP,LANG(MENUITEM_TOOLS_DIFF_HELP,"A&yuda...")).Description("Muestra ayuda acerca de la comparacion de fuentes en ZinjaI").Icon("ayuda.png"));
		EndSubMenu(mnTOOLS);
		
		BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_DOXYGEN,"Generar &Documentaci�n (doxygen)"),"Doxygen permite generar automaticamente documentacion a partir del codigo y sus comentarios","doxy.png",wxID_ANY,maPROJECT);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DOXY_GENERATE,LANG(MENUITEM_TOOLS_DOXYGEN_GENERATE,"&Generar...")).ShortCut("Ctrl+Shift+F1").Description("Ejecuta doxygen para generar la documentacion de forma automatica").Icon("doxy_run.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DOXY_CONFIG,LANG(MENUITEM_TOOLS_DOXYGEN_CONFIGURE,"&Configurar...")).Description("Permite establecer opciones para el archivo de configuracion de doxygen").Icon("doxy_config.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DOXY_VIEW,LANG(MENUITEM_TOOLS_DOXYGEN_VIEW,"&Ver...")).ShortCut("Ctrl+F1").Description("Abre un explorador y muestra la documentacion generada").Icon("doxy_view.png"));
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_DOXY_HELP,LANG(MENUITEM_TOOLS_DOXYGE_HELP,"A&yuda...")).Description("Muestra una breve ayuda acerca de la integracion de Doxygen en ZinjaI").Icon("ayuda.png"));
		EndSubMenu(mnTOOLS);
		
		BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_WXFB,"Dise�ar &Interfases (wxFormBuilder)"),"Dise�o visual de interfaces con la biblioteca wxWidgets","wxfb.png",wxID_ANY,maPROJECT);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_WXFB_CONFIG,LANG(MENUITEM_TOOLS_WXFB_CONFIG,"Configurar &Integracion con wxFormBuilder...")).Description("Configura caracter�sticas adicionales que facilitan el uso de wxFormBuilder").Icon("wxfb_activate.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_WXFB_NEW_RES,LANG(MENUITEM_TOOLS_WXFB_NEW_RESOURCE,"&Adjuntar un Nuevo Proyecto wxFB...")).Description("Crea un nuevo proyecto wxFormBuilder y lo agrega al proyecto en ZinjaI").Icon("wxfb_new_res.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_WXFB_LOAD_RES,LANG(MENUITEM_TOOLS_WXFB_LOAD_RESOURCE,"&Adjuntar un Proyecto wxFB Existente...")).Description("Agrega un proyecto wxFormBuilder ya existente al proyecto en ZinjaI").Icon("wxfb_load_res.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_WXFB_REGEN,LANG(MENUITEM_TOOLS_WXFB_REGENERATE,"&Regenerar Proyectos wxFB")).ShortCut("Shift+Alt+F9").Description("Ejecuta wxFormBuilder para regenerar los archivos de recurso o fuentes que correspondan").Icon("wxfb_regen.png").Map());
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_WXFB_INHERIT_CLASS,LANG(MENUITEM_TOOLS_WXFB_INHERIT,"&Generar Clase Heredada...")).Description("Genera una nueva clase a partir de las definidas por algun proyecto wxfb").Icon("wxfb_inherit.png").Map());
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_WXFB_UPDATE_INHERIT,LANG(MENUITEM_TOOLS_WXFB_UPDATE_INHERIT,"Act&ualizar Clase Heredada...")).Description("Actualiza los metodos de una clase que hereda de las definidas por algun proyecto wxfb").Icon("wxfb_update_inherit.png").Map());
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_WXFB_HELP_WX,LANG(MENUITEM_TOOLS_WXFB_REFERENCE,"Referencia &wxWidgets...")).Description("Muestra la ayuda de la biblioteca wxWidgets").Icon("ayuda_wx.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_WXFB_HELP,LANG(MENUITEM_TOOLS_WXFB_HELP,"A&yuda wxFB...")).Description("Muestra una breve ayuda acerca de la integracion de wxFormBuilder en ZinjaI").Icon("ayuda.png"));
		EndSubMenu(mnTOOLS);
		
		BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_CPPCHECK,"An�lisis Est�tico (cppcheck)"),"","cppcheck.png",wxID_ANY,maPROJECT);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_CPPCHECK_RUN, LANG(MENUITEM_TOOLS_CPPCHECK_RUN,"Iniciar...")).Icon("cppcheck_run.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_CPPCHECK_CONFIG, LANG(MENUITEM_TOOLS_CPPCHECK_CONFIG,"Configurar...")).Icon("cppcheck_config.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_CPPCHECK_VIEW, LANG(MENUITEM_TOOLS_CPPCHECK_VIEW,"Mostrar Panel de Resultados")).Icon("cppcheck_view.png"));
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_CPPCHECK_HELP,LANG(MENUITEM_TOOLS_CPPCHECK_HELP,"A&yuda...")).Icon("ayuda.png"));
		EndSubMenu(mnTOOLS);
		
		BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_GPROF,"Perfil de Ejecuci�n (gprof)"),"Gprof permite analizar las llamadas a funciones y sus tiempos de ejecucion.","gprof.png");
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_GPROF_SET, LANG(MENUITEM_TOOLS_GPROF_ACTIVATE,"Habilitar/Deshabilitar")).Description("A�ade/remueve los argumentos necesarios a la configuraci�n de compilaci�n y reconstruye el ejecutable.").Icon("comp_for_prof.png"));
			BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_GPROF_LAYOUT,"Algoritmo de Dibujo"),"Permite seleccionar entre dos algoritmos diferentes para dibujar el grafo","dotfdp.png");
				AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_GPROF_DOT, LANG(MENUITEM_TOOLS_GPROF_DOT,"dot"))/*.Checkeable(config->Init.graphviz_dot)*/);
				AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_GPROF_FDP, LANG(MENUITEM_TOOLS_GPROF_FDP,"fdp"))/*.Checkeable(config->Init.graphviz_dot)*/);
			EndSubMenu(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_GPROF_SHOW, LANG(MENUITEM_TOOLS_GPROF_SHOW,"Visualizar Resultados (grafo)...")).Description("Muestra graficamente la informacion de profiling de la ultima ejecucion.").Icon("showgprof.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_GPROF_LIST, LANG(MENUITEM_TOOLS_GPROF_LIST,"Listar Resultados (texto)")).Description("Muestra la informacion de profiling de la ultima ejecucion sin procesar.").Icon("listgprof.png"));
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_GPROF_HELP,LANG(MENUITEM_TOOLS_GPROF_HELP,"A&yuda...")).Description("Muestra ayuda acerca de como generar e interpretar la informacion de profiling").Icon("ayuda.png"));
		EndSubMenu(mnTOOLS);
		
		BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_GCOV,"&Test de Cobertura (experimental, gcov)"),"Gcov permite contabilizar cuantas veces se ejecuta cada linea del c�digo fuente.","gcov.png");
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_GCOV_SET, LANG(MENUITEM_TOOLS_GCOV_ACTIVATE,"Habilitar/Deshabilitar")).Description("A�ade/remueve los argumentos necesarios a la configuraci�n de compilaci�n y reconstruye el ejecutable.").Icon("gcov_set.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_GCOV_SHOW, LANG(MENUITEM_TOOLS_GCOV_SHOW_BAR,"Mostrar barra de resultados")).Description("Muestra un panel con los conteos por linea en el margen izquierdo de la ventana.").Icon("gcov_show.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_GCOV_RESET, LANG(MENUITEM_TOOLS_GCOV_RESET,"Eliminar resultados")).Description("Elimina los archivos de resultados generados por el test de cobertura.").Icon("gcov_reset.png"));
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_GCOV_HELP,LANG(MENUITEM_TOOLS_GCOV_HELP,"A&yuda...")).Description("Muestra ayuda acerca de como generar e interpretar la informacion del test de cobertura").Icon("ayuda.png"));
		EndSubMenu(mnTOOLS);
		
	#if !defined(_WIN32) && !defined(__WIN32__)
		BeginSubMenu(mnTOOLS,LANG(MENUITEM_TOOLS_VALGRIND,"An�lisis Din�mico (valgrind)"),"Valgrind permite analizar el uso de memoria dinamica para detectar perdidas y otros errores","valgrind.png");
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_VALGRIND_RUN, LANG(MENUITEM_TOOLS_VALGRIND_RUN,"Ejecutar...")).Icon("valgrind_run.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_VALGRIND_VIEW, LANG(MENUITEM_TOOLS_VALGRIND_VIEW,"Mostrar Panel de Resultados")).Icon("valgrind_view.png"));
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_VALGRIND_HELP, LANG(MENUITEM_TOOLS_VALGRIND_HELP,"A&yuda...")).Icon("ayuda.png"));
		EndSubMenu(mnTOOLS);
	#endif
		
		BeginSubMenu(mnTOOLS, LANG(MENUITEM_TOOLS_CUSTOM_TOOLS,"Herramientas Personalizables"),"","customTools.png",mxID_TOOLS_CUSTOM_TOOLS,maMAPPED);
			for (int i=0;i<MAX_CUSTOM_TOOLS;i++)
				AddMenuItem(mnTOOLS, myMenuItem(mxID_CUSTOM_TOOL_0+i, wxString()<<i<<": <NULL>").Description(wxString(LANG(MENUITEM_TOOLS_CUSTOM_TOOLS,"Herramientas Personalizables"))<<" -> "<<i<<": <NULL>").Icon(wxString("customTool")<<i<<".png"));
			AddSeparator(mnTOOLS);
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_CUSTOM_TOOLS_SETTINGS, LANG(MENUITEM_TOOLS_CUSTOM_TOOLS_SETTINGS,"&Configurar (generales)...")).Icon("customToolsSettings.png"));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_PROJECT_TOOLS_SETTINGS, LANG(MENUITEM_TOOLS_PROJECT_TOOLS_SETTINGS,"&Configurar (de proyecto)...")).Icon("projectToolsSettings.png").Project(true));
			AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_CUSTOM_HELP, LANG(MENUITEM_TOOLS_CUSTOM_HELP,"A&yuda...")).Icon("ayuda.png"));
		EndSubMenu(mnTOOLS);
		
		AddSeparator(mnTOOLS);
		
		AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_CREATE_TEMPLATE, LANG(MENUITEM_TOOLS_CREATE_TEMPLATE,"Guardar como nueva plantilla...")).Description("Permite guardar el programa simple o proyecto actual como plantilla").Icon("create_template.png"));
		AddMenuItem(mnTOOLS, myMenuItem(mxID_TOOLS_INSTALL_COMPLEMENTS, LANG(MENUITEM_TOOLS_INSTALL_COMPLEMENTS,"Instalar Complementos...")).Description("Permite instalar un complemento ya descargado para ZinjaI").Icon("updates.png"));
	}	
	
	
	menues[mnHELP].label = LANG(MENUITEM_HELP,"A&yuda"); {
		AddMenuItem(mnHELP, myMenuItem(mxID_HELP_ABOUT, LANG(MENUITEM_HELP_ABOUT,"Acerca de...")).Description("Acerca de...").Icon("acercaDe.png"));
		AddMenuItem(mnHELP, myMenuItem(mxID_HELP_TUTORIAL, LANG(MENUITEM_HELP_TUTORIALS,"Tutoriales...")).Description("Abre el cuadro de ayuda y muestra el indice de tutoriales disponibles").Icon("tutoriales.png"));
		AddMenuItem(mnHELP, myMenuItem(mxID_HELP_GUI, LANG(MENUITEM_HELP_ZINJAI,"Ayuda sobre ZinjaI...")).ShortCut("F1").Description("Muestra la ayuda sobre el uso y las caracteristicas de este entorno...").Icon("ayuda.png"));
		AddMenuItem(mnHELP, myMenuItem(mxID_HELP_CPP, LANG(MENUITEM_HELP_CPP,"Referencia C/C++...")).ShortCut("Alt+F1").Description("Muestra una completa referencia sobre el lenguaje").Icon("referencia.png"));
		AddMenuItem(mnHELP, myMenuItem(mxID_HELP_TIP, LANG(MENUITEM_HELP_TIPS,"&Mostrar sugerencias de uso...")).Description("Muestra sugerencias sobre el uso del programa...").Icon("tip.png"));
		AddMenuItem(mnHELP, myMenuItem(mxID_HELP_OPINION, LANG(MENUITEM_HELP_OPINION,"Enviar sugerencia o reportar error...")).Description("Permite acceder a los foros oficiales de ZinjaI para dejar sugerencias, comentarios o reportar errores").Icon("opinion.png"));
		AddMenuItem(mnHELP, myMenuItem(mxID_HELP_UPDATES, LANG(MENUITEM_HELP_UPDATES,"&Buscar actualizaciones...")).Description("Comprueba a traves de Internet si hay versiones mas recientes de ZinjaI disponibles...").Icon("updates.png"));
	}
	
}

void MenusAndToolsConfig::LoadToolbarsData ( ) {
	
	icon_size=24;
	
	toolbars[tbFILE].Init("file",LANG(CAPTION_TOOLBAR_FILE,"Archivo"),"T:1:0"); {
		AddToolbarItem(tbFILE,myToolbarItem("new_file",menues[mnFILE],wxID_NEW).Visible());
		AddToolbarItem(tbFILE,myToolbarItem("new_project",menues[mnFILE],mxID_FILE_PROJECT));
		AddToolbarItem(tbFILE,myToolbarItem("open",menues[mnFILE],wxID_OPEN).Visible());
		AddToolbarItem(tbFILE,myToolbarItem("recent_simple",menues[mnFILE],mxID_FILE_SOURCE_HISTORY_MORE));
		AddToolbarItem(tbFILE,myToolbarItem("recent_project",menues[mnFILE],mxID_FILE_PROJECT_HISTORY_MORE));
		AddToolbarItem(tbFILE,myToolbarItem("open_header",mxID_FILE_OPEN_H,"abrir_h.png",LANG(TOOLBAR_CAPTION_FILE_OPEN_H,"Abrir h/cpp Complementario")));
		AddToolbarItem(tbFILE,myToolbarItem("open_selected",mxID_FILE_OPEN_SELECTED,"abrir_sel.png",LANG(TOOLBAR_CAPTION_FILE_OPEN_SELECTED,"Abrir Seleccionado")));
		AddToolbarItem(tbFILE,myToolbarItem("save",menues[mnFILE],wxID_SAVE).Visible());
		AddToolbarItem(tbFILE,myToolbarItem("save_as",menues[mnFILE],wxID_SAVEAS).Visible());
		AddToolbarItem(tbFILE,myToolbarItem("save_all",menues[mnFILE],mxID_FILE_SAVE_ALL));
		AddToolbarItem(tbFILE,myToolbarItem("save_project",menues[mnFILE],mxID_FILE_SAVE_PROJECT));
		AddToolbarItem(tbFILE,myToolbarItem("export_html",menues[mnFILE],mxID_FILE_EXPORT_HTML));
		AddToolbarItem(tbFILE,myToolbarItem("print",menues[mnFILE],mxID_FILE_PRINT));
		AddToolbarItem(tbFILE,myToolbarItem("reload",menues[mnFILE],mxID_FILE_RELOAD));
		AddToolbarItem(tbFILE,myToolbarItem("close",menues[mnFILE],wxID_CLOSE));
		AddToolbarItem(tbFILE,myToolbarItem("close_all",menues[mnFILE],mxID_FILE_CLOSE_ALL));
		AddToolbarItem(tbFILE,myToolbarItem("close_project",menues[mnFILE],mxID_FILE_CLOSE_PROJECT));
		AddToolbarItem(tbFILE,myToolbarItem("project_config",menues[mnFILE],mxID_FILE_PROJECT_CONFIG));
	}
	
	
	toolbars[tbEDIT].Init("edit",LANG(CAPTION_TOOLBAR_EDIT,"Edici�n"),"T:1:1"); {
		AddToolbarItem(tbEDIT,myToolbarItem("undo",menues[mnEDIT],wxID_UNDO).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("redo",menues[mnEDIT],wxID_REDO).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("copy",menues[mnEDIT],wxID_COPY).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("cut",menues[mnEDIT],wxID_CUT).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("paste",menues[mnEDIT],wxID_PASTE).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("move_up",menues[mnEDIT],mxID_EDIT_TOGGLE_LINES_UP));
		AddToolbarItem(tbEDIT,myToolbarItem("move_down",menues[mnEDIT],mxID_EDIT_TOGGLE_LINES_DOWN));
		AddToolbarItem(tbEDIT,myToolbarItem("duplicate",menues[mnEDIT],mxID_EDIT_DUPLICATE_LINES));
		AddToolbarItem(tbEDIT,myToolbarItem("delete_lines",menues[mnEDIT],mxID_EDIT_DELETE_LINES));
		AddToolbarItem(tbEDIT,myToolbarItem("goto_line",menues[mnEDIT],mxID_EDIT_GOTO).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("goto_class",menues[mnEDIT],mxID_EDIT_GOTO_FUNCTION).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("goto_file",menues[mnEDIT],mxID_EDIT_GOTO_FILE).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("find",menues[mnEDIT],mxID_EDIT_FIND).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("find_prev",menues[mnEDIT],mxID_EDIT_FIND_PREV));
		AddToolbarItem(tbEDIT,myToolbarItem("find_next",menues[mnEDIT],mxID_EDIT_FIND_NEXT).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("replace",menues[mnEDIT],mxID_EDIT_REPLACE).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("inser_header",menues[mnEDIT],mxID_EDIT_INSERT_HEADER).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("comment",menues[mnEDIT],mxID_EDIT_COMMENT).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("uncomment",menues[mnEDIT],mxID_EDIT_UNCOMMENT).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("indent",menues[mnEDIT],mxID_EDIT_INDENT).Visible());
		AddToolbarItem(tbEDIT,myToolbarItem("select_block",menues[mnEDIT],mxID_EDIT_BRACEMATCH));
		AddToolbarItem(tbEDIT,myToolbarItem("select_all",menues[mnEDIT],wxID_SELECTALL));
		AddToolbarItem(tbEDIT,myToolbarItem("toggle_user_mark",menues[mnEDIT],mxID_EDIT_MARK_LINES));
		AddToolbarItem(tbEDIT,myToolbarItem("find_user_mark",menues[mnEDIT],mxID_EDIT_GOTO_MARK));
		AddToolbarItem(tbEDIT,myToolbarItem("list_user_marks",menues[mnEDIT],mxID_EDIT_LIST_MARKS));
		AddToolbarItem(tbEDIT,myToolbarItem("autocomplete",mxID_EDIT_FORCE_AUTOCOMPLETE,"autocompletar.png",LANG(TOOLBAR_CAPTION_EDIT_FORCE_AUTOCOMPLETE,"Autocompletar")));
	}
	
	
	toolbars[tbVIEW].Init("view",LANG(CAPTION_TOOLBAR_VIEW,"Ver"),"t:1:3"); {
		AddToolbarItem(tbVIEW,myToolbarItem("split_view",menues[mnVIEW],mxID_VIEW_DUPLICATE_TAB).Visible());
		AddToolbarItem(tbVIEW,myToolbarItem("line_wrap",menues[mnVIEW],mxID_VIEW_LINE_WRAP).Visible());
		AddToolbarItem(tbVIEW,myToolbarItem("white_space",menues[mnVIEW],mxID_VIEW_WHITE_SPACE).Visible());
		AddToolbarItem(tbVIEW,myToolbarItem("sintax_colour",menues[mnVIEW],mxID_VIEW_CODE_STYLE).Visible());
		AddToolbarItem(tbVIEW,myToolbarItem("update_symbols",mxID_VIEW_UPDATE_SYMBOLS,"symbolsTree.png",LANG(TOOLBAR_CAPTION_VIEW_SYMBOLS_TREE,"Arbol de simbolos")));
		AddToolbarItem(tbVIEW,myToolbarItem("explorer_tree",menues[mnVIEW],mxID_VIEW_EXPLORER_TREE));
		AddToolbarItem(tbVIEW,myToolbarItem("project_tree",menues[mnVIEW],mxID_VIEW_PROJECT_TREE));
		AddToolbarItem(tbVIEW,myToolbarItem("compiler_tree",menues[mnVIEW],mxID_VIEW_COMPILER_TREE));
		AddToolbarItem(tbVIEW,myToolbarItem("full_screen",menues[mnVIEW],mxID_VIEW_FULLSCREEN).Visible());
		AddToolbarItem(tbVIEW,myToolbarItem("beginner_panel",menues[mnVIEW],mxID_VIEW_BEGINNER_PANEL));
		AddToolbarItem(tbVIEW,myToolbarItem("prev_error",menues[mnVIEW],mxID_VIEW_PREV_ERROR).Visible());
		AddToolbarItem(tbVIEW,myToolbarItem("next_error",menues[mnVIEW],mxID_VIEW_NEXT_ERROR).Visible());
		AddToolbarItem(tbVIEW,myToolbarItem("fold_all",menues[mnVIEW],mxID_FOLD_HIDE_ALL));
		AddToolbarItem(tbVIEW,myToolbarItem("fold_1",menues[mnVIEW],mxID_FOLD_HIDE_1)); // 1,LANG(TOOLBAR_CAPTION_FOLD_LEVEL_1,"Plegar el Primer Nivel"),ipre+_T("fold1.png"),LANG(TOOLBAR_DESC_FOLD_LEVEL_1,""));
		AddToolbarItem(tbVIEW,myToolbarItem("fold_2",menues[mnVIEW],mxID_FOLD_HIDE_2)); // 2,LANG(TOOLBAR_CAPTION_FOLD_LEVEL_2,"Plegar el Segundo Nivel"),ipre+_T("fold2.png"),LANG(TOOLBAR_DESC_FOLD_LEVEL_2,""));
		AddToolbarItem(tbVIEW,myToolbarItem("fold_3",menues[mnVIEW],mxID_FOLD_HIDE_3)); // 3,LANG(TOOLBAR_CAPTION_FOLD_LEVEL_3,"Plegar el Tercer Nivel"),ipre+_T("fold3.png"),LANG(TOOLBAR_DESC_FOLD_LEVEL_3,""));
		AddToolbarItem(tbVIEW,myToolbarItem("fold_4",menues[mnVIEW],mxID_FOLD_HIDE_4)); // 3,LANG(TOOLBAR_CAPTION_FOLD_LEVEL_3,"Plegar el Tercer Nivel"),ipre+_T("fold3.png"),LANG(TOOLBAR_DESC_FOLD_LEVEL_3,""));
		AddToolbarItem(tbVIEW,myToolbarItem("fold_5",menues[mnVIEW],mxID_FOLD_HIDE_5)); // 3,LANG(TOOLBAR_CAPTION_FOLD_LEVEL_3,"Plegar el Tercer Nivel"),ipre+_T("fold3.png"),LANG(TOOLBAR_DESC_FOLD_LEVEL_3,""));
		AddToolbarItem(tbVIEW,myToolbarItem("unfold_all",menues[mnVIEW],mxID_FOLD_SHOW_ALL));
		AddToolbarItem(tbVIEW,myToolbarItem("unfold_1",menues[mnVIEW],mxID_FOLD_SHOW_1)); // 1,LANG(TOOLBAR_CAPTION_UNFOLD_LEVEL_1,"Desplegar el Primer Nivel"),ipre+_T("unfold1.png"),LANG(TOOLBAR_DESC_UNFOLD_LEVEL_1,""));
		AddToolbarItem(tbVIEW,myToolbarItem("unfold_2",menues[mnVIEW],mxID_FOLD_SHOW_2)); // 2,LANG(TOOLBAR_CAPTION_UNFOLD_LEVEL_2,"Desplegar el Segundo Nivel"),ipre+_T("unfold2.png"),LANG(TOOLBAR_DESC_UNFOLD_LEVEL_2,""));
		AddToolbarItem(tbVIEW,myToolbarItem("unfold_3",menues[mnVIEW],mxID_FOLD_SHOW_3)); // 3,LANG(TOOLBAR_CAPTION_UNFOLD_LEVEL_3,"Desplegar el Tercer Nivel"),ipre+_T("unfold3.png"),LANG(TOOLBAR_DESC_UNFOLD_LEVEL_3,""));
		AddToolbarItem(tbVIEW,myToolbarItem("unfold_4",menues[mnVIEW],mxID_FOLD_SHOW_4)); // 3,LANG(TOOLBAR_CAPTION_UNFOLD_LEVEL_3,"Desplegar el Tercer Nivel"),ipre+_T("unfold3.png"),LANG(TOOLBAR_DESC_UNFOLD_LEVEL_3,""));
		AddToolbarItem(tbVIEW,myToolbarItem("unfold_5",menues[mnVIEW],mxID_FOLD_SHOW_5)); // 3,LANG(TOOLBAR_CAPTION_UNFOLD_LEVEL_3,"Desplegar el Tercer Nivel"),ipre+_T("unfold3.png"),LANG(TOOLBAR_DESC_UNFOLD_LEVEL_3,""));
	}
	
	toolbars[tbRUN].Init("run",LANG(CAPTION_TOOLBAR_RUN,"Ejecuci�n"),"T:1:2"); {
		AddToolbarItem(tbRUN,myToolbarItem("compile",menues[mnRUN],mxID_RUN_COMPILE).Visible());
		AddToolbarItem(tbRUN,myToolbarItem("run",menues[mnRUN],mxID_RUN_RUN).Label(LANG(TOOLBAR_CAPTION_RUN_RUN,"Guardar, compilar y ejecutar...")).Visible());
		AddToolbarItem(tbRUN,myToolbarItem("run_old",menues[mnRUN],mxID_RUN_RUN_OLD));
		AddToolbarItem(tbRUN,myToolbarItem("stop",menues[mnRUN],mxID_RUN_STOP).Visible());
		AddToolbarItem(tbRUN,myToolbarItem("clean",menues[mnRUN],mxID_RUN_CLEAN));
		AddToolbarItem(tbRUN,myToolbarItem("options",menues[mnRUN],mxID_RUN_CONFIG).Visible());
		AddToolbarItem(tbRUN,myToolbarItem("debug",menues[mnDEBUG],mxID_DEBUG_RUN).Visible());
#ifndef __WIN32__
		AddToolbarItem(tbRUN,myToolbarItem("debug_attach",menues[mnDEBUG],mxID_DEBUG_ATTACH));
		AddToolbarItem(tbRUN,myToolbarItem("load_core_dump",menues[mnDEBUG],mxID_DEBUG_CORE_DUMP));
#endif
		AddToolbarItem(tbRUN,myToolbarItem("break_toggle",menues[mnDEBUG],mxID_DEBUG_TOGGLE_BREAKPOINT));
		AddToolbarItem(tbRUN,myToolbarItem("break_options",menues[mnDEBUG],mxID_DEBUG_BREAKPOINT_OPTIONS));
		AddToolbarItem(tbRUN,myToolbarItem("break_list",menues[mnDEBUG],mxID_DEBUG_LIST_BREAKPOINTS));
		AddToolbarItem(tbRUN,myToolbarItem("inspections",menues[mnDEBUG],mxID_DEBUG_INSPECT));
	}
	
	
	toolbars[tbDEBUG].Init("debug",LANG(CAPTION_TOOLBAR_DEBUG,"Depuraci�n"),"t:3:0"); {
		AddToolbarItem(tbDEBUG,myToolbarItem("start",menues[mnDEBUG],mxID_DEBUG_RUN).Visible());
		AddToolbarItem(tbDEBUG,myToolbarItem("pause",menues[mnDEBUG],mxID_DEBUG_PAUSE).Visible());
		AddToolbarItem(tbDEBUG,myToolbarItem("stop",menues[mnDEBUG],mxID_DEBUG_STOP).Visible());
		AddToolbarItem(tbDEBUG,myToolbarItem("step_in",menues[mnDEBUG],mxID_DEBUG_STEP_IN).Visible());
		AddToolbarItem(tbDEBUG,myToolbarItem("step_over",menues[mnDEBUG],mxID_DEBUG_STEP_OVER).Visible());
		AddToolbarItem(tbDEBUG,myToolbarItem("step_out",menues[mnDEBUG],mxID_DEBUG_STEP_OUT).Visible());
		AddToolbarItem(tbDEBUG,myToolbarItem("run_until",menues[mnDEBUG],mxID_DEBUG_RUN_UNTIL).Visible());
		AddToolbarItem(tbDEBUG,myToolbarItem("function_return",menues[mnDEBUG],mxID_DEBUG_RETURN).Visible());
		AddToolbarItem(tbDEBUG,myToolbarItem("jump",menues[mnDEBUG],mxID_DEBUG_JUMP).Visible());
#ifndef __WIN32__
		AddToolbarItem(tbDEBUG,myToolbarItem("enable_inverse_exec",menues[mnDEBUG],mxID_DEBUG_ENABLE_INVERSE_EXEC).Checkeable());
		AddToolbarItem(tbDEBUG,myToolbarItem("inverse_exec",menues[mnDEBUG],mxID_DEBUG_INVERSE_EXEC).Checkeable());
		AddToolbarItem(tbDEBUG,myToolbarItem("set_signals",menues[mnDEBUG],mxID_DEBUG_SET_SIGNALS));
		AddToolbarItem(tbDEBUG,myToolbarItem("send_signal",menues[mnDEBUG],mxID_DEBUG_SEND_SIGNAL));
#endif
		AddToolbarItem(tbDEBUG,myToolbarItem("inspections",menues[mnDEBUG],mxID_DEBUG_INSPECT));
		AddToolbarItem(tbDEBUG,myToolbarItem("backtrace",menues[mnDEBUG],mxID_DEBUG_BACKTRACE));
		AddToolbarItem(tbDEBUG,myToolbarItem("threadlist",menues[mnDEBUG],mxID_DEBUG_THREADLIST));
		AddToolbarItem(tbDEBUG,myToolbarItem("break_toggle",menues[mnDEBUG],mxID_DEBUG_TOGGLE_BREAKPOINT));
		AddToolbarItem(tbDEBUG,myToolbarItem("break_options",menues[mnDEBUG],mxID_DEBUG_BREAKPOINT_OPTIONS));
		AddToolbarItem(tbDEBUG,myToolbarItem("break_list",menues[mnDEBUG],mxID_DEBUG_LIST_BREAKPOINTS).Visible());
		AddToolbarItem(tbDEBUG,myToolbarItem("log_panel",menues[mnDEBUG],mxID_DEBUG_LOG_PANEL));
		AddToolbarItem(tbDEBUG,myToolbarItem("gdb_command",menues[mnDEBUG],mxID_DEBUG_GDB_COMMAND));
		AddToolbarItem(tbDEBUG,myToolbarItem("gdb_patch",menues[mnDEBUG],mxID_DEBUG_PATCH));
	}
	
	
	toolbars[tbTOOLS].Init("tools",LANG(CAPTION_TOOLBAR_TOOLS,"Herramientas"),"t:1:4"); {
		AddToolbarItem(tbTOOLS,myToolbarItem("draw_flow",menues[mnTOOLS],mxID_TOOLS_DRAW_FLOW));
		AddToolbarItem(tbTOOLS,myToolbarItem("draw_classes",menues[mnTOOLS],mxID_TOOLS_DRAW_CLASSES));
		AddToolbarItem(tbTOOLS,myToolbarItem("copy_code_from_h",menues[mnTOOLS],mxID_TOOLS_CODE_COPY_FROM_H).Visible());
		AddToolbarItem(tbTOOLS,myToolbarItem("align_comments",menues[mnTOOLS],mxID_TOOLS_ALIGN_COMMENTS));
		AddToolbarItem(tbTOOLS,myToolbarItem("remove_comments",menues[mnTOOLS],mxID_TOOLS_REMOVE_COMMENTS));
		AddToolbarItem(tbTOOLS,myToolbarItem("preproc_mark_valid",menues[mnTOOLS],mxID_TOOLS_PREPROC_MARK_VALID));
		AddToolbarItem(tbTOOLS,myToolbarItem("preproc_unmark_all",menues[mnTOOLS],mxID_TOOLS_PREPROC_UNMARK_ALL));
		AddToolbarItem(tbTOOLS,myToolbarItem("preproc_expand_macros",menues[mnTOOLS],mxID_TOOLS_PREPROC_EXPAND_MACROS).Visible());
		AddToolbarItem(tbTOOLS,myToolbarItem("generate_makefile",menues[mnTOOLS],mxID_TOOLS_MAKEFILE));
		AddToolbarItem(tbTOOLS,myToolbarItem("open_terminal",menues[mnTOOLS],mxID_TOOLS_CONSOLE).Visible());
		AddToolbarItem(tbTOOLS,myToolbarItem("exe_info",menues[mnTOOLS],mxID_TOOLS_EXE_PROPS));
		AddToolbarItem(tbTOOLS,myToolbarItem("proy_stats",menues[mnTOOLS],mxID_TOOLS_PROJECT_STATISTICS));
		AddToolbarItem(tbTOOLS,myToolbarItem("draw_classes",menues[mnTOOLS],mxID_TOOLS_DRAW_CLASSES));
		AddToolbarItem(tbTOOLS,myToolbarItem("open_shared",menues[mnTOOLS],mxID_TOOLS_SHARE_OPEN).Visible());
		AddToolbarItem(tbTOOLS,myToolbarItem("share_source",menues[mnTOOLS],mxID_TOOLS_SHARE_SHARE));
		AddToolbarItem(tbTOOLS,myToolbarItem("share_list",menues[mnTOOLS],mxID_TOOLS_SHARE_LIST));
		AddToolbarItem(tbTOOLS,myToolbarItem("diff_two_sources",menues[mnTOOLS],mxID_TOOLS_DIFF_TWO).Visible());
		AddToolbarItem(tbTOOLS,myToolbarItem("diff_other_file",menues[mnTOOLS],mxID_TOOLS_DIFF_DISK));
		AddToolbarItem(tbTOOLS,myToolbarItem("diff_himself",menues[mnTOOLS],mxID_TOOLS_DIFF_HIMSELF));
		AddToolbarItem(tbTOOLS,myToolbarItem("diff_show",menues[mnTOOLS],mxID_TOOLS_DIFF_SHOW));
		AddToolbarItem(tbTOOLS,myToolbarItem("diff_apply",menues[mnTOOLS],mxID_TOOLS_DIFF_APPLY));
		AddToolbarItem(tbTOOLS,myToolbarItem("diff_discard",menues[mnTOOLS],mxID_TOOLS_DIFF_DISCARD));
		AddToolbarItem(tbTOOLS,myToolbarItem("diff_clear",menues[mnTOOLS],mxID_TOOLS_DIFF_CLEAR));
		AddToolbarItem(tbTOOLS,myToolbarItem("doxy_generate",menues[mnTOOLS],mxID_TOOLS_DOXY_GENERATE).Visible());
		AddToolbarItem(tbTOOLS,myToolbarItem("doxy_config",menues[mnTOOLS],mxID_TOOLS_DOXY_CONFIG));
		AddToolbarItem(tbTOOLS,myToolbarItem("doxy_view",menues[mnTOOLS],mxID_TOOLS_DOXY_VIEW));
		AddToolbarItem(tbTOOLS,myToolbarItem("wxfb_config",menues[mnTOOLS],mxID_TOOLS_WXFB_CONFIG));
		AddToolbarItem(tbTOOLS,myToolbarItem("wxfb_new_res",menues[mnTOOLS],mxID_TOOLS_WXFB_NEW_RES));
		AddToolbarItem(tbTOOLS,myToolbarItem("wxfb_load_res",menues[mnTOOLS],mxID_TOOLS_WXFB_LOAD_RES));
		AddToolbarItem(tbTOOLS,myToolbarItem("wxfb_regen",menues[mnTOOLS],mxID_TOOLS_WXFB_REGEN));
		AddToolbarItem(tbTOOLS,myToolbarItem("wxfb_inherit",menues[mnTOOLS],mxID_TOOLS_WXFB_INHERIT_CLASS));
		AddToolbarItem(tbTOOLS,myToolbarItem("wxfb_update_inherit",menues[mnTOOLS],mxID_TOOLS_WXFB_UPDATE_INHERIT));
		AddToolbarItem(tbTOOLS,myToolbarItem("wxfb_help_wx",menues[mnTOOLS],mxID_TOOLS_WXFB_HELP_WX));
		AddToolbarItem(tbTOOLS,myToolbarItem("cppcheck_run",menues[mnTOOLS],mxID_TOOLS_CPPCHECK_RUN));
		AddToolbarItem(tbTOOLS,myToolbarItem("cppcheck_config",menues[mnTOOLS],mxID_TOOLS_CPPCHECK_CONFIG));
		AddToolbarItem(tbTOOLS,myToolbarItem("cppcheck_view",menues[mnTOOLS],mxID_TOOLS_CPPCHECK_VIEW));
		AddToolbarItem(tbTOOLS,myToolbarItem("gprof_activate",menues[mnTOOLS],mxID_TOOLS_GPROF_SET));
		AddToolbarItem(tbTOOLS,myToolbarItem("gprof_show_graph",menues[mnTOOLS],mxID_TOOLS_GPROF_SHOW));
		AddToolbarItem(tbTOOLS,myToolbarItem("gprof_list_output",menues[mnTOOLS],mxID_TOOLS_GPROF_LIST));
		AddToolbarItem(tbTOOLS,myToolbarItem("gcov_activate",menues[mnTOOLS],mxID_TOOLS_GCOV_SET));
		AddToolbarItem(tbTOOLS,myToolbarItem("gcov_show_bar",menues[mnTOOLS],mxID_TOOLS_GCOV_SHOW));
		AddToolbarItem(tbTOOLS,myToolbarItem("gcov_reset",menues[mnTOOLS],mxID_TOOLS_GCOV_RESET));
#ifndef __WIN32__
		AddToolbarItem(tbTOOLS,myToolbarItem("valgrind_run",menues[mnTOOLS],mxID_TOOLS_VALGRIND_RUN));
		AddToolbarItem(tbTOOLS,myToolbarItem("valgrind_view",menues[mnTOOLS],mxID_TOOLS_VALGRIND_VIEW));
#endif
		for (int i=0;i<MAX_CUSTOM_TOOLS;i++)
			AddToolbarItem(tbTOOLS,myToolbarItem("",menues[mnTOOLS],mxID_CUSTOM_TOOL_0+i));
		AddToolbarItem(tbTOOLS,myToolbarItem("custom_settings",menues[mnTOOLS],mxID_TOOLS_CUSTOM_TOOLS_SETTINGS));
	}
	
	
	toolbars[tbMISC].Init("misc",LANG(CAPTION_TOOLBAR_MISC,"Miscel�nea"),"T:1:6"); {
		AddToolbarItem(tbMISC,myToolbarItem("preferences",menues[mnFILE],mxID_FILE_PREFERENCES).Visible());
		AddToolbarItem(tbMISC,myToolbarItem("tutorials",menues[mnHELP],mxID_HELP_TUTORIAL));
		AddToolbarItem(tbMISC,myToolbarItem("help_ide",menues[mnHELP],mxID_HELP_GUI).Visible());
		AddToolbarItem(tbMISC,myToolbarItem("help_cpp",menues[mnHELP],mxID_HELP_CPP).Visible());
		AddToolbarItem(tbMISC,myToolbarItem("show_tips",menues[mnHELP],mxID_HELP_TIP));
		AddToolbarItem(tbMISC,myToolbarItem("about",menues[mnHELP],mxID_HELP_ABOUT));
		AddToolbarItem(tbMISC,myToolbarItem("opinion",menues[mnHELP],mxID_HELP_OPINION).Visible());
		AddToolbarItem(tbMISC,myToolbarItem("find_updates",menues[mnHELP],mxID_HELP_UPDATES));
		AddToolbarItem(tbMISC,myToolbarItem("exit",menues[mnFILE],wxID_EXIT));
	}
	
#warning agregar la de proyecto para que sea mas facil abajo crearla???
	toolbars[tbFIND].Init("find",LANG(CAPTION_TOOLBAR_FIND,"B�squeda"),"T:1:5");
	toolbars[tbPROJECT].Init("project",LANG(CAPTION_TOOLBAR_PROJECT,"Proyecto"),"T:1:7");
	toolbars[tbDIFF].Init("diff",LANG(CAPTION_TOOLBAR_DIFF,"Diff"),"t:3:1");
	
}

	
void MenusAndToolsConfig::PopulateMenu(int menu_id) {
	vector<wxMenu*> menu_stack;
	wxString menu_icon_prefix = DIR_PLUS_FILE("16","");
	wxMenu *current_menu = menues[menu_id].wx_menu = new wxMenu;
	wx_menu_bar->Append(current_menu,menues[menu_id].label);
	unsigned int items_size = menues[menu_id].items.size();
	for(unsigned int j=0;j<items_size;j++) { 
		myMenuItem &mi=menues[menu_id].items[j];
		int props=mi.properties;
		wxMenuItem *wx_item=NULL;
		if (props&maSEPARATOR) {
			current_menu->AppendSeparator();
		} else if (props&maBEGIN_SUBMENU) {
			wxMenu *new_menu = new wxMenu;
			wx_item = utils->AddSubMenuToMenu(current_menu,new_menu,mi.label,mi.description,menu_icon_prefix+mi.icon);
			if (props&maMAPPED) {
//					mapped_items.push_back(MappedItem(mi.wx_id,wx_item));
				mapped_menues.push_back(MappedSomething<wxMenu*>(mi.wx_id,new_menu));
			}
			menu_stack.push_back(current_menu);
			current_menu=new_menu;
		} else if (props&maEND_SUBMENU) {
			current_menu=menu_stack.back(); menu_stack.pop_back();
		} else if (!(props&maHIDDEN)) {
			if (props&(maCHECKED|maCHECKEABLE))
				wx_item = utils->AddCheckToMenu(current_menu,mi.wx_id,mi.label,mi.shortcut,mi.description,props&maCHECKED);
			else 
				wx_item = utils->AddItemToMenu(current_menu,mi.wx_id,mi.label,mi.shortcut,mi.description,menu_icon_prefix+mi.icon);
			if (props&maMAPPED) mapped_items.push_back(MappedSomething<wxMenuItem*>(mi.wx_id,wx_item));
		}
		if (props&maDEBUG) { items_debug.push_back(AutoenabligItem(wx_item,true)); }
		else if (props&maNODEBUG) { items_debug.push_back(AutoenabligItem(wx_item,false)); }
		if (props&maPROJECT) { items_project.push_back(AutoenabligItem(wx_item,true)); }
		else if (props&maNOPROJECT) { items_project.push_back(AutoenabligItem(wx_item,false)); }
	}
}

/**
* @brief Crea los men�es de la ventana principal y los configura en el modo inicial (no debug, no project)
**/
void MenusAndToolsConfig::CreateMenues () {		
	
	wx_menu_bar = new wxMenuBar;
	main_window->SetMenuBar(wx_menu_bar);
		
	// create regular menus
	for(unsigned int menu_id=0;menu_id<mnCOUNT;menu_id++) PopulateMenu(menu_id);
	
	// create some special submenues
//	main_window->UpdateCustomTools(false);
	wxString ipre=DIR_PLUS_FILE("16","recent");
	for(int k=0;k<2;k++) { 
		wxString *cfglast = k==0?config->Files.last_project:config->Files.last_source;
		wxMenuItem **mnihistory = k==0?menu_data->file_project_history:menu_data->file_source_history;
		wxMenu *mnurecent = menu_data->GetMenu(k==0?mxID_FILE_PROJECT_RECENT:mxID_FILE_SOURCE_RECENT);
		int history_id = k==0?mxID_FILE_PROJECT_HISTORY_0:mxID_FILE_SOURCE_HISTORY_0;
		for (int i=0;i<config->Init.history_len;i++)
			if (!cfglast[i].IsEmpty()) 
				mnihistory[i] = utils->AddItemToMenu(mnurecent, history_id+i,cfglast[i],"",cfglast[i],wxString(ipre+"recent")<<i<<(".png"),i);
	}
	
	// set items state
	SetProjectMode(false);
	SetDebugMode(false);
}

void MenusAndToolsConfig::CreateWxToolbar(int tb_id) {
	toolbars[tb_id].wx_toolbar = new wxToolBar(main_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER | (toolbars[tb_id].position.top?wxTB_HORIZONTAL:wxTB_VERTICAL));
	toolbars[tb_id].wx_toolbar->SetToolBitmapSize(wxSize(icon_size,icon_size)); 
	main_window->aui_manager.AddPane(toolbars[tb_id].wx_toolbar, wxAuiPaneInfo().Name(wxString("toolbar_")+toolbars[tb_id].key).Caption(toolbars[tb_id].label).ToolbarPane().Hide());
}

void MenusAndToolsConfig::UpdateToolbar(int tb_id, bool only_items) {
	if (!only_items) {
		// destroy the previous one
		main_window->aui_manager.DetachPane(toolbars[tb_id].wx_toolbar);
		toolbars[tb_id].wx_toolbar->Destroy();
		toolbars[tb_id].wx_toolbar=NULL;
		CreateWxToolbar(tb_id);
	} else {
		toolbars[tb_id].wx_toolbar->ClearTools();
	}
	PopulateToolbar(tb_id);
	AdjustToolbarSize(tb_id);
}
	
void MenusAndToolsConfig::CreateToolbars() {
	
	wxString ipre=DIR_PLUS_FILE(wxString()<<icon_size,"");
	
	if (!wxFileName::DirExists(DIR_PLUS_FILE(config->Files.skin_dir,wxString()<<icon_size))) {
		wxString icsz = wxString()<<icon_size<<"x"<<icon_size;
		mxMessageDialog(NULL,
			wxString()<<LANG1(MAIN_WINDOW_NO_ICON_SIZE,""
			"El tema de iconos seleccionado no tiene iconos del tama�o elegido (<{1}>)\n"
			"Se utilizaran los iconos del tama�o predeterminado (16x16).\n"
			"Para modificarlo utilice el cuadro de Preferencias (menu Archivo).",wxString()<<icsz),
			LANG(GENERAL_WARNING,"Advertencia"),mxMD_WARNING|mxMD_OK).ShowModal();
		icon_size=16;
		ipre=DIR_PLUS_FILE("16","");
	}
	
	// create empty wxToolBars 
	for(unsigned int tb_id=0;tb_id<tbCOUNT_FULL;tb_id++) CreateWxToolbar(tb_id);
	
	// barras estandar: FILE, EDIT, VIEW, RUN, DEBUG, TOOLS, MISC, PROJECT
	for(int tb_id=0;tb_id<tbPROJECT;tb_id++) PopulateToolbar(tb_id); 
	
	// barras especiales: busqueda
	{
		myToolbar &tb = toolbars[tbFIND];
//		tb.wx_toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
//		tb.wx_toolbar->SetToolBitmapSize(wxSize(icon_size,icon_size));
		tb.wx_toolbar->AddControl( toolbar_find_text = new wxTextCtrl(tb.wx_toolbar,mxID_TOOLBAR_FIND,wxEmptyString,wxDefaultPosition,wxSize(100,20),wxTE_PROCESS_ENTER) );
		toolbar_find_text->SetToolTip(LANG(TOOLBAR_FIND_TEXT,"Texto a Buscar"));
		utils->AddTool(tb.wx_toolbar,mxID_EDIT_TOOLBAR_FIND,LANG(TOOLBAR_FIND_CAPTION,"Busqueda Rapida"),ipre+_T("buscar.png"),LANG(TOOLBAR_FIND_BUTTON,"Buscar siguiente"));
//		main_window->aui_manager.AddPane(tb.wx_toolbar, wxAuiPaneInfo().Name(wxString("toolbar_")+tb.key).Caption(tb.label).ToolbarPane().Hide());
	}
	
	// barras especiales: estado de la depuracion
	{
		myToolbar &tb = toolbars[tbSTATUS];
//		tb.wx_toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
//		tb.wx_toolbar->SetToolBitmapSize(wxSize(icon_size,icon_size));
		tb.wx_toolbar->AddControl( toolbar_status_text = new wxStaticText(tb.wx_toolbar,wxID_ANY,"",wxDefaultPosition,wxSize(2500,20)) );
		toolbar_status_text->SetForegroundColour(wxColour("Z DARK BLUE"));
//		main_window->aui_manager.AddPane(tb.wx_toolbar, wxAuiPaneInfo().Name(wxString("toolbar_")+tb.key).Caption(tb.label).ToolbarPane().Top().Hide());
	}
	
	// barras especiales: diff
	{
		myToolbar &tb = toolbars[tbDIFF];
//		tb.wx_toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
//		tb.wx_toolbar->SetToolBitmapSize(wxSize(icon_size,icon_size));
		utils->AddTool(tb.wx_toolbar,mxID_TOOLS_DIFF_PREV,LANG(TOOLBAR_CAPTION_TOOLS_DIFF_PREV,"Diferencia Anterior"),ipre+_T("diff_prev.png"),LANG(TOOLBAR_DESC_TOOLS_DIFF_PREV,"Herramientas -> Comparar Archivos -> Ir a Diferencia Anterior"));
		utils->AddTool(tb.wx_toolbar,mxID_TOOLS_DIFF_NEXT,LANG(TOOLBAR_CAPTION_TOOLS_DIFF_NEXT,"Siguiente Diferencia"),ipre+_T("diff_next.png"),LANG(TOOLBAR_DESC_TOOLS_DIFF_NEXT,"Herramientas -> Comparar Archivos -> Ir a Siguiente Diferencia"));
		utils->AddTool(tb.wx_toolbar,mxID_TOOLS_DIFF_SHOW,LANG(TOOLBAR_CAPTION_TOOLS_DIFF_SHOW,"Mostrar Cambio"),ipre+_T("diff_show.png"),LANG(TOOLBAR_DESC_TOOLS_DIFF_SHOW,"Herramientas -> Comparar Archivos -> Mostrar Cambio"));
		utils->AddTool(tb.wx_toolbar,mxID_TOOLS_DIFF_APPLY,LANG(TOOLBAR_CAPTION_TOOLS_DIFF_APPLY,"Aplicar Cambio"),ipre+_T("diff_apply.png"),LANG(TOOLBAR_DESC_TOOLS_DIFF_APPLY,"Herramientas -> Comparar Archivos -> Aplicar Cambio"));
		utils->AddTool(tb.wx_toolbar,mxID_TOOLS_DIFF_DISCARD,LANG(TOOLBAR_CAPTION_TOOLS_DIFF_DISCARD,"Descartar Cambio"),ipre+_T("diff_discard.png"),LANG(TOOLBAR_DESC_TOOLS_DIFF_DISCARD,"Herramientas -> Comparar Archivos -> Descartar Cambio"));
		utils->AddTool(tb.wx_toolbar,mxID_TOOLS_DIFF_CLEAR,LANG(TOOLBAR_CAPTION_TOOLS_DIFF_CLEAR,"Borrar Marcas de Comparacion"),ipre+_T("diff_clear.png"),LANG(TOOLBAR_DESC_TOOLS_DIFF_CLEAR,"Herramientas -> Comparar Archivos -> Borrar Marcas"));
//		main_window->aui_manager.AddPane(tb.wx_toolbar, wxAuiPaneInfo().Name(wxString("toolbar_")+tb.key).Caption(tb.label).ToolbarPane().Top().Float().LeftDockable(false).RightDockable(false).Hide());
	}
	
	// ajustar tama�os
	for(unsigned int tb_id=0;tb_id<tbCOUNT_FULL;tb_id++) AdjustToolbarSize(tb_id);
	main_window->SortToolbars(false);
}

void MenusAndToolsConfig::PopulateToolbar(int tb_id) {
	
	wxToolBar *wx_toolbar = toolbars[tb_id].wx_toolbar;
	wxString ipre=DIR_PLUS_FILE(wxString()<<icon_size,"");
	
	if (tb_id!=tbPROJECT) { // items de la base de items
		vector<myToolbarItem> &items = toolbars[tb_id].items;
		for(unsigned int i=0;i<items.size();i++)
			if (items[i].visible) 
				utils->AddTool(wx_toolbar,items[i].wx_id,items[i].label,ipre+items[i].icon,items[i].description,items[i].checkeable?wxITEM_CHECK:wxITEM_NORMAL);
	
	} else { // caso especial, barra de proyecto
		// elementos especificos de proyectos wx
		if (project->GetWxfbActivated()) {
			int wx_ids[3] = { mxID_TOOLS_WXFB_CONFIG, mxID_TOOLS_WXFB_INHERIT_CLASS, mxID_TOOLS_WXFB_HELP_WX };
			for(int i=0;i<3;i++) {
				myToolbarItem item("",menues[mnTOOLS],wx_ids[i]);
				utils->AddTool(wx_toolbar,item.wx_id,item.label,ipre+item.icon,item.description,item.checkeable?wxITEM_CHECK:wxITEM_NORMAL);
			}
		}
		// herramientas personalizadas
		bool have_tool=false;
		for (int i=0;i<MAX_PROJECT_CUSTOM_TOOLS;i++) {
			if (project->custom_tools[i].on_toolbar) {
				have_tool=true;
				wxString str(LANG(TOOLBAR_CAPTION_TOOLS_CUSTOM_TOOL,"Herramienta Personalizada ")); str<<i<<" ("<<project->custom_tools[i].name<<")";;
				utils->AddTool(wx_toolbar,mxID_CUSTOM_PROJECT_TOOL_0+i,str,ipre+wxString("projectTool")<<i<<".png",str);
			}
		}
		if (!have_tool) { // si no hay definidas herramientas personalizadas, muestra el boton para configurarlas
			myToolbarItem item("",menues[mnTOOLS],mxID_TOOLS_PROJECT_TOOLS_SETTINGS);
			utils->AddTool(wx_toolbar,item.wx_id,item.label,ipre+item.icon,item.description,item.checkeable?wxITEM_CHECK:wxITEM_NORMAL);
		}
	}
	
}

void MenusAndToolsConfig::AdjustToolbarSize(int tb_id) {
	wxToolBar *wx_toolbar = toolbars[tb_id].wx_toolbar;
	if (wx_toolbar) { wx_toolbar->Realize(); main_window->aui_manager.GetPane(wx_toolbar).BestSize(wx_toolbar->GetBestSize()); }
}

bool MenusAndToolsConfig::ParseToolbarConfigLine (const wxString & key, const wxString & value) {
	if (key=="icon_size") { utils->ToInt(value,icon_size); return true; }
	int p=key.Index('.'); if (p==wxNOT_FOUND) return false;
	wxString tb_name=key.Mid(0,p);
	if (tb_name=="positions") {
		tb_name = key.AfterFirst('.');
		for(int tb_id=0;tb_id<tbCOUNT_FULL;tb_id++) { 
			if (toolbars[tb_id].key==tb_name) {
				toolbars[tb_id].position=value;
				return true;
			}
		}
	} else {
		for(int tb_id=0;tb_id<tbCOUNT_FULL;tb_id++) { 
			if (toolbars[tb_id].key==tb_name) {
				wxString name = key.AfterFirst('.');
				vector<myToolbarItem> &items = toolbars[tb_id].items;
				for(unsigned int i=0;i<items.size();i++) { 
					if (items[i].key==name) {
						items[i].visible = utils->IsTrue(value);
						return true;
					}
				}
			}
		}
	}
	return false;
}

void MenusAndToolsConfig::SetDebugMode (bool mode) {
	for(unsigned int i=0;i<items_debug.size();i++) 
		items_debug[i].Enable(mode);
}

void MenusAndToolsConfig::SetProjectMode (bool mode) {
	for(unsigned int i=0;i<items_project.size();i++) 
		items_project[i].Enable(mode);
}

void MenusAndToolsConfig::SaveToolbarConfig (wxTextFile & file) {
	file.AddLine(wxString("icon_size=")<<icon_size);
	for(int tb_id=0;tb_id<tbCOUNT_FULL;tb_id++) {
		file.AddLine(wxString("positions.")+toolbars[tb_id].key+"="+(wxString)toolbars[tb_id].position);
		wxString toolbar_key = toolbars[tb_id].key+".";
		vector<myToolbarItem> &items = toolbars[tb_id].items;
		for(unsigned int i=0;i<items.size();i++) {
			if (!items[i].key.IsEmpty())
				file.AddLine(toolbar_key+items[i].key+(items[i].visible?"=1":"=0"));
		}
	}
}

int MenusAndToolsConfig::ToolbarFromTool(int tool_id) {
	for(int tb_id=0;tb_id<tbCOUNT_FULL;tb_id++) { 
		vector<myToolbarItem> &items = toolbars[tb_id].items;
		for(unsigned int i=0;i<items.size();i++) {
			if (items[i].wx_id==tool_id) return tb_id;
		}
	}
	return -1;
}

void MenusAndToolsConfig::CreateMenuesAndToolbars (mxMainWindow * _main_window) {
	main_window=_main_window;
	TransferStatesFromConfig();
	CreateToolbars();
	CreateMenues();
}

MenusAndToolsConfig::myMenuItem *MenusAndToolsConfig::GetMyMenuItem (int menu_id, int item_id) {
	vector<myMenuItem> &v = menues[menu_id].items;
	for(unsigned int i=0;i<v.size();i++) { 
		if (v[i].wx_id==item_id) return &(v[i]);
	}
	return NULL;
}

MenusAndToolsConfig::myToolbarItem *MenusAndToolsConfig::GetMyToolbarItem (int toolbar_id, int item_id) {
	vector<myToolbarItem> &v = toolbars[toolbar_id].items;
	for(unsigned int i=0;i<v.size();i++) { 
		if (v[i].wx_id==item_id) return &(v[i]);
	}
	return NULL;
}

void MenusAndToolsConfig::TransferStatesFromConfig() {
	// sync menu check item with toolbar visibility status
	GetMyMenuItem(mnVIEW,mxID_VIEW_TOOLBAR_FILE)->Checkeable(_toolbar_visible(tbFILE));
	GetMyMenuItem(mnVIEW,mxID_VIEW_TOOLBAR_EDIT)->Checkeable(_toolbar_visible(tbEDIT));
	GetMyMenuItem(mnVIEW,mxID_VIEW_TOOLBAR_VIEW)->Checkeable(_toolbar_visible(tbVIEW));
	GetMyMenuItem(mnVIEW,mxID_VIEW_TOOLBAR_FIND)->Checkeable(_toolbar_visible(tbFIND));
	GetMyMenuItem(mnVIEW,mxID_VIEW_TOOLBAR_RUN)->Checkeable(_toolbar_visible(tbRUN));
	GetMyMenuItem(mnVIEW,mxID_VIEW_TOOLBAR_TOOLS)->Checkeable(_toolbar_visible(tbTOOLS));
	GetMyMenuItem(mnVIEW,mxID_VIEW_TOOLBAR_PROJECT)->Checkeable(_toolbar_visible(tbPROJECT));
	GetMyMenuItem(mnVIEW,mxID_VIEW_TOOLBAR_DEBUG)->Checkeable(_toolbar_visible(tbDEBUG));
	GetMyMenuItem(mnVIEW,mxID_VIEW_TOOLBAR_MISC)->Checkeable(_toolbar_visible(tbMISC));
	if (!config->Init.left_panels) GetMyMenuItem(mnVIEW,mxID_VIEW_LEFT_PANELS)->Hide();
	GetMyMenuItem(mnTOOLS,mxID_TOOLS_GPROF_DOT)->Checkeable(config->Init.graphviz_dot);
	GetMyMenuItem(mnTOOLS,mxID_TOOLS_GPROF_FDP)->Checkeable(config->Init.graphviz_dot);
	for (int i=0;i<MAX_CUSTOM_TOOLS;i++) {
		wxString str; str<<i<<": "<<config->CustomTools[i].name;
		wxString desc(LANG(MENUITEM_TOOLS_CUSTOM_TOOLS,"Herramientas Personalizables")); desc<<" -> "<<i<<": "<<config->CustomTools[i].command;
		GetMyMenuItem(mnTOOLS,mxID_CUSTOM_TOOL_0+i)->Label(str).Description(config->CustomTools[i].command).SetVisible(!config->CustomTools[i].name.IsEmpty());
		GetMyToolbarItem(mnTOOLS,mxID_CUSTOM_TOOL_0+i)->Label(str).Description(desc).SetVisible(config->CustomTools[i].on_toolbar);
	}
}