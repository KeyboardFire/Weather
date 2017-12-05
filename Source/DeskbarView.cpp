#include <Bitmap.h>
#include <Deskbar.h>
#include <NodeInfo.h>
#include <Roster.h>

#include <fstream>

#include "DeskbarView.h"

extern const char* kSignature;

BView* instantiate_deskbar_item()
{
	return new DeskbarView();
}


DeskbarView::DeskbarView()
	:
	BView(BRect(0, 0, 15, 15), "weather", B_FOLLOW_ALL,
		B_WILL_DRAW | B_FRAME_EVENTS)
{
}


DeskbarView::DeskbarView(BMessage* archive)
	:
	BView(archive)
{
}


void DeskbarView::AddToDeskbar()
{
	BDeskbar deskbar;
	entry_ref ref;
	be_roster->FindApp(kSignature, &ref);
	deskbar.AddItem(&ref);
}


void DeskbarView::AttachedToWindow()
{
	entry_ref ref;
	icon = new BBitmap(BRect(0, 0, B_MINI_ICON - 1, B_MINI_ICON - 1), B_CMAP8);
	be_roster->FindApp(kSignature, &ref);
	BNode file(&ref);
	BNodeInfo* info = new BNodeInfo(&file);
	info->GetIcon(icon, B_MINI_ICON);
	delete info;
}


void DeskbarView::Draw(BRect rect)
{
	SetDrawingMode(B_OP_ALPHA);
	DrawBitmap(icon);
}


void DeskbarView::MouseDown(BPoint point)
{
	std::ofstream of("/boot/home/debug.txt", std::ios_base::app);
	of << "mouse down" << std::endl;
}


DeskbarView* DeskbarView::Instantiate(BMessage* archive)
{
	return new DeskbarView(archive);
}
