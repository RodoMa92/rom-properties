/***************************************************************************
 * ROM Properties Page shell extension. (GTK+ common)                      *
 * RomDataView.cpp: RomData viewer widget. (Private functions)             *
 *                                                                         *
 * Copyright (c) 2017-2022 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#ifndef __ROMPROPERTIES_GTK_ROMDATAVIEW_P_HPP__
#define __ROMPROPERTIES_GTK_ROMDATAVIEW_P_HPP__

#include "config.gtk.h"
#include <gtk/gtk.h>

#include "OptionsMenuButton.hpp"

// librpbase
namespace LibRpBase {
	class RomData;
	class RomFields;
}

// C++ includes
#include <vector>

#if GTK_CHECK_VERSION(3,0,0)
typedef GtkBoxClass superclass;
typedef GtkBox super;
#define GTK_TYPE_SUPER GTK_TYPE_BOX
#define USE_GTK_GRID 1	// Use GtkGrid instead of GtkTable.
#else /* !GTK_CHECK_VERSION(3,0,0) */
typedef GtkVBoxClass superclass;
typedef GtkVBox super;
#define GTK_TYPE_SUPER GTK_TYPE_VBOX
#endif /* GTK_CHECK_VERSION(3,0,0) */

// GTK+ property page class.
struct _RomDataViewClass {
	superclass __parent__;
};

// Multi-language stuff.
typedef std::pair<GtkWidget*, const LibRpBase::RomFields::Field*> Data_StringMulti_t;

struct Data_ListDataMulti_t {
	GtkListStore *listStore;
	GtkTreeView *treeView;
	const LibRpBase::RomFields::Field *field;

	Data_ListDataMulti_t(
		GtkListStore *listStore,
		GtkTreeView *treeView,
		const LibRpBase::RomFields::Field *field)
		: listStore(listStore)
		, treeView(treeView)
		, field(field) { }
};

// C++ objects.
struct _RomDataViewCxx {
	struct tab {
		GtkWidget	*vbox;		// Either parent page or a GtkVBox/GtkBox.
		GtkWidget	*table;		// GtkTable (2.x); GtkGrid (3.x)
		GtkWidget	*lblCredits;

		tab() : vbox(nullptr), table(nullptr), lblCredits(nullptr) { }
	};
	std::vector<tab> tabs;

	// Description labels.
	std::vector<GtkWidget*> vecDescLabels;

	// Multi-language functionality.
	uint32_t def_lc;

	// RFT_STRING_MULTI value labels.
	std::vector<Data_StringMulti_t> vecStringMulti;

	// RFT_LISTDATA_MULTI value GtkListStores.
	std::vector<Data_ListDataMulti_t> vecListDataMulti;
};

// GTK+ property page instance.
struct _RomDataView {
	super __parent__;

	_RomDataViewCxx		*cxx;		// C++ objects
	LibRpBase::RomData	*romData;	// ROM data
	gchar			*uri;		// URI (GVfs)

	// "Options" button. (OptionsMenuButton)
	GtkWidget	*btnOptions;
	gchar		*prevExportDir;

	// Header row.
	GtkWidget	*hboxHeaderRow_outer;
	GtkWidget	*hboxHeaderRow;
	GtkWidget	*lblSysInfo;
	GtkWidget	*imgIcon;
	GtkWidget	*imgBanner;

	// Tab layout.
	GtkWidget	*tabWidget;
	// Tabs moved to: cxx->tabs

	// MessageWidget for ROM operation notifications.
	GtkWidget	*messageWidget;

	// Multi-language combo box.
	GtkWidget	*cboLanguage;

	/* Timeouts */
	guint		changed_idle;

	// Description label format type.
	RpDescFormatType	desc_format_type;

	// Inhibit checkbox toggling for RFT_BITFIELD while updating.
	bool inhibit_checkbox_no_toggle;
	// Have we checked for achievements?
	bool hasCheckedAchievements;
};

G_BEGIN_DECLS

int	rom_data_view_update_field		(RomDataView		*page,
						 int			 fieldIdx);

void	btnOptions_triggered_signal_handler	(OptionsMenuButton	*menuButton,
						 gint		 	 id,
						 RomDataView		*page);

G_END_DECLS

#endif /* __ROMPROPERTIES_GTK_ROMDATAVIEW_P_HPP__ */