/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 OpenGL view subclass.
 */

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

@interface GLEssentialsGLView : NSOpenGLView <NSWindowDelegate>
{
	CVDisplayLinkRef displayLink;
}

@end
