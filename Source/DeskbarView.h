#ifndef _DESKBAR_VIEW_H
#define _DESKBAR_VIEW_H

#include <View.h>

class BBitmap;

extern "C" _EXPORT BView* instantiate_deskbar_item();

class DeskbarView : public BView
{
public:
						DeskbarView();
						DeskbarView(BMessage* archive);

	static void			AddToDeskbar();
	void				AttachedToWindow();
	void				Draw(BRect rect);
	void				MessageReceived(BMessage* msg);
	void				MouseDown(BPoint point);
	static DeskbarView*	Instantiate(BMessage* archive);

private:
	BBitmap			*icon;
};

#endif
