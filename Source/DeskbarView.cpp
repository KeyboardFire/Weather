#include <Bitmap.h>
#include <Catalog.h>
#include <Deskbar.h>
#include <MenuItem.h>
#include <NodeInfo.h>
#include <PopUpMenu.h>
#include <Roster.h>

#include "DeskbarView.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "DeskbarView"

extern const char* kSignature;
const char* kDeskbarItemName = "Weather";

const uint32 kOpenApplication = 'open';
const uint32 kRemoveReplicant = 'rmDb';

BView* instantiate_deskbar_item()
{
	return new DeskbarView();
}


DeskbarView::DeskbarView()
	:
	BView(BRect(0, 0, 15, 15), kDeskbarItemName, B_FOLLOW_ALL,
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
	// set the appropriate background so that the transparency in the icon is
	// displayed appropriately
	AdoptParentColors();

	// retrieve the application icon
	entry_ref ref;
	icon = new BBitmap(BRect(0, 0, B_MINI_ICON - 1, B_MINI_ICON - 1),
		B_RGBA32);
	be_roster->FindApp(kSignature, &ref);
	BNode file(&ref);
	BNodeInfo* info = new BNodeInfo(&file);
	info->GetIcon(icon, B_MINI_ICON);
	delete info;
}


void DeskbarView::Draw(BRect rect)
{
	// all we need to do is draw the icon
	SetDrawingMode(B_OP_ALPHA);
	DrawBitmap(icon);
}


void DeskbarView::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
		case kOpenApplication:
			be_roster->Launch(kSignature);
			break;
		case kRemoveReplicant:
		{
			BDeskbar deskbar;
			deskbar.RemoveItem(kDeskbarItemName);
			break;
		}
	}
}


void DeskbarView::MouseDown(BPoint point)
{
	BPopUpMenu* menu = new BPopUpMenu(B_EMPTY_STRING, false, false);
	menu->SetAsyncAutoDestruct(true);
	menu->SetFont(be_plain_font);

	menu->AddItem(new BMenuItem(B_TRANSLATE("Open Weather"),
		new BMessage(kOpenApplication)));
	menu->AddItem(new BMenuItem(B_TRANSLATE("Remove from deskbar"),
		new BMessage(kRemoveReplicant)));

	menu->SetTargetForItems(this);

	ConvertToScreen(&point);
	menu->Go(point, true, true, true);
}


DeskbarView* DeskbarView::Instantiate(BMessage* archive)
{
	return new DeskbarView(archive);
}
