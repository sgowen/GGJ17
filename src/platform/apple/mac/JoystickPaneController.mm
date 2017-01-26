/*
 * Copyright (c) 2007 Dave Dribin
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#import "JoystickPaneController.h"

#import "DDHidJoystick.h"
#import "DDHidElement.h"
#import "ButtonState.h"

// C++
#include "InputManager.h"
#include "GamePadEventType.h"
#include "GameSession.h"

@interface JoystickPaneController (Private)

- (void) setJoysticks: (NSArray *) theJoysticks;

@end

@implementation JoystickPaneController

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        mJoystickButtons = [[NSMutableArray alloc] init];
        
        m_fStateTime = 0;
    }
    
    return self;
}

- (void)scan
{
    [self performSelector:@selector(scan) withObject:nil afterDelay:1];
    
    if (GAME_SESSION->isSessionLive())
    {
        return;
    }
    
    NSArray * joysticks = [DDHidJoystick allJoysticks];
    
    [mJoystickButtons removeAllObjects];
    
    [joysticks makeObjectsPerformSelector: @selector(setDelegate:)
                               withObject: self];
    [self setJoysticks: joysticks];
    
    int numPlayers = [mJoysticks count];
    for (int i = 0; i < numPlayers; i++)
    {
        [self listenOnJoystick:i];
    }
    
    GAME_SESSION->setNumPlayersConnected(numPlayers);
}

//===========================================================
//  joysticks 
//=========================================================== 
- (NSArray *) joysticks
{
    return mJoysticks; 
}

- (NSArray *) joystickButtons;
{
    return mJoystickButtons;
}

//=========================================================== 
//  joystickIndex 
//=========================================================== 
- (NSUInteger) joystickIndex
{
    return mJoystickIndex;
}

- (void) listenOnJoystick: (NSUInteger) theJoystickIndex
{
    if (theJoystickIndex != NSNotFound)
    {
        DDHidJoystick *currentJoystick = [mJoysticks objectAtIndex: theJoystickIndex];
        [currentJoystick setTag:theJoystickIndex];
        [currentJoystick startListening];
        
        [mJoystickButtons addObject:[[NSMutableArray alloc] init]];
        
        NSArray * buttons = [currentJoystick buttonElements];
        NSEnumerator * e = [buttons objectEnumerator];
        DDHidElement * element;
        while (element = [e nextObject])
        {
            ButtonState * state = [[ButtonState alloc] initWithName: [[element usage] usageName]];
            [state autorelease];
            [mJoystickButtons[theJoystickIndex] addObject: state];
        }
    }
}

- (void) ddhidJoystick: (DDHidJoystick *)  joystick
                 stick: (unsigned) stick
              xChanged: (int) value;
{
    float x = value;
    x /= 65536.0f;
    
    int index = [joystick tag] * 2;
    
    mJoystickAxis[index] = x;
    
    INPUT_MANAGER->onGamePadInput(STICK_LEFT, [joystick tag], mJoystickAxis[index], mJoystickAxis[index + 1]);
    NSLog(@"X Value %f", x);
}

- (void) ddhidJoystick: (DDHidJoystick *)  joystick
                 stick: (unsigned) stick
              yChanged: (int) value;
{
    float y = value;
    y /= 65536.0f;
    y *= -1;
    
    int index = [joystick tag] * 2;
    
    mJoystickAxis[index + 1] = y;
    
    INPUT_MANAGER->onGamePadInput(STICK_LEFT, [joystick tag], mJoystickAxis[index], mJoystickAxis[index + 1]);
    NSLog(@"Y Value %f", y);
}

- (void) ddhidJoystick: (DDHidJoystick *) joystick
                 stick: (unsigned) stick
             otherAxis: (unsigned) otherAxis
          valueChanged: (int) value;
{
    // Empty
}

- (void) ddhidJoystick: (DDHidJoystick *) joystick
                 stick: (unsigned) stick
             povNumber: (unsigned) povNumber
          valueChanged: (int) value;
{
    // Empty
}

- (void) ddhidJoystick: (DDHidJoystick *) joystick
            buttonDown: (unsigned) buttonNumber;
{
    int index = [joystick tag];
    
    NSMutableArray *buttonStates = [mJoystickButtons objectAtIndex:index];
    ButtonState * state = [buttonStates objectAtIndex: buttonNumber];
    [state setPressed: YES];
    
    if (buttonNumber == 1)
    {
        // X
        INPUT_MANAGER->onGamePadInput(A_BUTTON, index, 0, 0);
    }
    else if (buttonNumber == 6)
    {
        // left trigger
        INPUT_MANAGER->onGamePadInput(TRIGGER, index, 1, 0);
    }
    else if (buttonNumber == 7)
    {
        // right trigger
        INPUT_MANAGER->onGamePadInput(TRIGGER, index, 0, 1);
    }
}

- (void) ddhidJoystick: (DDHidJoystick *) joystick
              buttonUp: (unsigned) buttonNumber;
{
    int index = [joystick tag];
    NSMutableArray *buttonStates = [mJoystickButtons objectAtIndex:index];
    ButtonState * state = [buttonStates objectAtIndex: buttonNumber];
    [state setPressed: NO];
    
    if (buttonNumber == 6)
    {
        // left trigger
        INPUT_MANAGER->onGamePadInput(TRIGGER, index, 0, 0);
    }
    else if (buttonNumber == 7)
    {
        // right trigger
        INPUT_MANAGER->onGamePadInput(TRIGGER, index, 0, 0);
    }
    else if (buttonNumber == 9)
    {
        // start
        GAME_SESSION->setNumPlayersConnected([mJoysticks count]);
        INPUT_MANAGER->onGamePadInput(START_BUTTON, index, 0, 0);
    }
    else if (buttonNumber == 8)
    {
        // select
        if (GAME_SESSION->isSessionLive())
        {
            INPUT_MANAGER->onGamePadInput(BACK_BUTTON, index, 0, 0);
        }
        else
        {
            [NSApp terminate:self];
        }
    }
}

@end

@implementation JoystickPaneController (Private)

- (void) setJoysticks: (NSArray *) theJoysticks
{
    if (mJoysticks != theJoysticks)
    {
        [mJoysticks release];
        mJoysticks = [theJoysticks retain];
    }
}

@end
