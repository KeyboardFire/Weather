/*
 * Copyright 2015 Przemysław Buczkowski <przemub@przemub.pl>
 * Copyright 2014 George White
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_


#include <Bitmap.h>
#include <Button.h>
#include <GridLayout.h>
#include <GridView.h>
#include <GroupView.h>
#include <MenuBar.h>
#include <Resources.h>
#include <String.h>
#include <StringView.h>
#include <View.h>
#include <Window.h>

#include "ForecastView.h"
#include "ForecastDayView.h"
#include "PreferencesWindow.h"
#include "SelectionWindow.h"

const BRect kDefaultMainWindowRect = BRect(150,150,0,0);
const uint32 kCitySelectionMessage = 'SelC';
const uint32 kOpenPreferencesMessage = 'OPrf';
const uint32 kDeskbarMessage = 'DBar';

class MainWindow : public BWindow {
public:
					MainWindow(void);
	virtual void	MessageReceived(BMessage* msg);
	virtual bool	QuitRequested();
	
private:
	status_t		_LoadSettings(BMessage& settings);
	status_t		_SaveSettings();
	BMenuBar*		_PrepareMenuBar(void);
	ForecastView*	fForecastView;

	bool			fShowForecast;

	BRect			fMainWindowRect;
	SelectionWindow*	fSelectionWindow;
	PreferencesWindow* fPreferencesWindow;
	
	BMenuItem*		fShowForecastMenuItem;
};

#endif // _MAINWINDOW_H_
