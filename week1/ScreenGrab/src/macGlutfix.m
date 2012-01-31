




#include <Cocoa/Cocoa.h>
#include <AppKit/NSOpenGL.h>
#include "macGlutfix.h"

// The standard ScreenSaverView class actually sets the window
// level to 2002, not the 1000 defined by NSScreenSaverWindowLevel
// and kCGScreenSaverWindowLevel
#define RealSaverLevel 1
// Glut sets the window level to 100 when it sets full screen mode
#define GlutFullScreenWindowLevel 100

// Delay when switching to screensaver mode to reduce annoying flashes
#define SAVERDELAY 30

void MacGLUTFix(bool isScreenSaver) {
    static NSMenu * emptyMenu;
    NSOpenGLContext * myContext = nil;
    NSView *myView = nil;
    NSWindow* myWindow = nil;
	
	
    if (false) {
        if (emptyMenu == nil) {
            emptyMenu = [ NSMenu alloc ];
            [ NSApp setMainMenu:emptyMenu ];
        }
    }
	
    // In screensaver mode, set our window's level just above
    // our BOINC screensaver's window level so it can appear
    // over it.  This doesn't interfere with the screensaver
    // password dialog because the dialog appears only after
    // our screensaver is closed.
    myContext = [ NSOpenGLContext currentContext ];
    if (myContext)
        myView = [ myContext view ];
    if (myView)
        myWindow = [ myView window ];
    if (myWindow == nil)
        return;
	
    if (!isScreenSaver) {
        NSButton *closeButton = [myWindow standardWindowButton:NSWindowCloseButton ];
        [closeButton setEnabled:YES];
        [myWindow setDocumentEdited: NO];
        return;
    }
	
	
    if ([ myWindow level ] == GlutFullScreenWindowLevel)
        [ myWindow setLevel:RealSaverLevel ];
}

void BringAppToFront() {
    [ NSApp activateIgnoringOtherApps:YES ];
}

void HideThisApp() {
    [ NSApp hide:NSApp ];
}



CGImageRef capturedImage;

unsigned char * pixelsBelowWindow(int x, int y, int w, int h)
{
    // Get the CGWindowID of supplied window
	
	
	NSOpenGLContext * myContext = nil;
    NSView *myView = nil;
    NSWindow* window = nil;
	
    // In screensaver mode, set our window's level just above
    // our BOINC screensaver's window level so it can appear
    // over it.  This doesn't interfere with the screensaver
    // password dialog because the dialog appears only after
    // our screensaver is closed.
    myContext = [ NSOpenGLContext currentContext ];
    if (myContext)
        myView = [ myContext view ];
    if (myView)
        window = [ myView window ];
    if (window == nil)
        return NULL;
	
	
    CGWindowID windowID = [window windowNumber];
    
    // Get window's rect in flipped screen coordinates
    CGRect windowRect = NSRectToCGRect( [window frame] );
    windowRect.origin.y = NSMaxY([[window screen] frame]) - NSMaxY([window frame]);
    
	windowRect.origin.x = x;
	windowRect.origin.y = y;
	windowRect.size.width = w;
	windowRect.size.height = h;
	
	
    // Get a composite image of all the windows beneath your window
     capturedImage = CGWindowListCreateImage( windowRect, kCGWindowListOptionOnScreenBelowWindow, windowID, kCGWindowImageDefault );
    
    // The rest is as in the previous example...
    if(CGImageGetWidth(capturedImage) <= 1) {
        CGImageRelease(capturedImage);
        //return nil;
		return NULL;
    }
    
    // Create a bitmap rep from the window and convert to NSImage...
    NSBitmapImageRep *bitmapRep = [[[NSBitmapImageRep alloc] initWithCGImage: capturedImage] autorelease];
    NSImage *image = [[[NSImage alloc] init] autorelease];
    [image addRepresentation: bitmapRep];
    
	uint32* bitmapPixels = (uint32*) [bitmapRep bitmapData];
	
	CGImageRelease(capturedImage);
    return (unsigned char *) bitmapPixels;
    //return image;
}

