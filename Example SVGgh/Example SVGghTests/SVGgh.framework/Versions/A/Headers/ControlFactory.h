//
//  ControlFactory.h
//  SVGgh
// The MIT License (MIT)

//  Copyright (c) 2011-2014 Glenn R. Howes

//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.

//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//  Created by Glenn Howes on 3/25/12.

/*******
  The basis of a theme engine. This one only creates a GHButton control which is a color appropriate replacement (not a subclass)
 of the UIButton that Apple provides.
******/

#import <UIKit/UIKit.h>
@class GHButton;

enum  {
    // do not change the order of these as they are hard coded into storyboards
    kColorSchemeiOS,
    kColorSchemeMachine,
    kColorSchemeKeyboard,
    kColorSchemeClear,
    kColorSchemeEmpty,
    kColorSchemeHomeTheatre,
    kColorSchemeiOSVersionAppropriate,
    kLastColorScheme = kColorSchemeiOSVersionAppropriate,
    
    kColorSchemeNone,
};
typedef NSUInteger ColorScheme;


/*! @brief a singleton class devoted to storing configurations for themes and returning useful theme objects like gradients and buttons
 * @attention right now only returns a button
 */
@interface ControlFactory : NSObject

/*! @brief set a standard button type for your app. Call it early in the app creation process. Like in your app delegate's initialize method
@param defaultScheme one of an enumerated list. kColorSchemeEmpty or kColorSchemeClear is nice for iOS 7
*/
+(void) setDefaultScheme:(ColorScheme)defaultScheme;

/*! @brief the ColorScheme that was set by an earlier call to setDefaultScheme
 @return one of the enumerated list in the typedef ColorScheme
 @see setDefaultScheme:
*/
+(ColorScheme) defaultScheme;

/*! @brief utility routine to validate parameters to make sure the enumerated color scheme is known (in the list)
 @param scheme one of the enumerated list in the typedef ColorScheme
 @return YES if the scheme is known
*/
+(BOOL)isValidColorScheme:(ColorScheme)scheme;

/*! @brief part of what you do to make iOS programs unique is to give controls a color specifif to your app
*/
+(void) setDefaultButtonTint:(UIColor*)buttonTint;

/*! @brief default tinting color for GHButtons
@return aColor appropriate for tinting a button.
*/
+(UIColor*)buttonTint;

/*! @brief Appropriate color for light backgrounded widgets given the scheme
@param scheme one of the enumerated list in the typedef ColorScheme
@return a light color
*/
+(UIColor*) newLightBackgroundColorForScheme:(ColorScheme)scheme;

/*! @brief a gradient appropriate for coloring a button background
* @param scheme one of the enumerated list in the typedef ColorScheme
* @return a CGGradientRef
* @attention caller responsible for disposal
*/
+(CGGradientRef) newButtonBackgroundGradientForScheme:(ColorScheme)scheme;

/*! @brief a gradient appropriate for coloring a pressed button's background
 * @param scheme one of the enumerated list in the typedef ColorScheme
 * @return a CGGradientRef
 * @attention caller responsible for disposal
 */
+(CGGradientRef) newButtonBackgroundGradientPressedForScheme:(ColorScheme)scheme;

/*! @brief a gradient appropriate for coloring a selected button's background
 * @param scheme one of the enumerated list in the typedef ColorScheme
 * @return a CGGradientRef
 * @attention caller responsible for disposal
 */
+(CGGradientRef) newButtonBackgroundGradientSelectedForScheme:(ColorScheme)scheme;

/*! @brief Does the given scheme prefer Radial gradients?
 * @param scheme one of the enumerated list in the typedef ColorScheme
 * @return YES if radial gradients are preferred
 */
+(BOOL) preferRadialGradientForScheme:(ColorScheme)scheme;

/*! @brief makes a color appropriate for button text
 * @param scheme one of the enumerated list in the typedef ColorScheme
 * @return a color which willbe dark if backgrounds are light, and light if backgrounds are dark
 */
+(UIColor*) newTextColorForScheme:(ColorScheme)scheme;

/*! @brief makes a color appropriate for button text on a pressed button
 * @param scheme one of the enumerated list in the typedef ColorScheme
 * @return a color which willbe dark if backgrounds are light, and light if backgrounds are dark
 */
+(UIColor*) newTextColorPressedForScheme:(ColorScheme)scheme;

/*! @brief makes a color appropriate for drop shadow on text
 * @param scheme one of the enumerated list in the typedef ColorScheme
 * @return a color (if any) to use as the drop shadow color of text
 */
+(UIColor*) newTextShadowColorForScheme:(ColorScheme)scheme;

/*! @brief makes a color appropriate for the ring chrome around a button
 * @param scheme one of the enumerated list in the typedef ColorScheme
 * @return a color (if any) for use in a ring's outline
 */
+(UIColor*) newRingColorForScheme:(ColorScheme)scheme;

/*! @brief generates a button appropriate for the given scheme
 * @param scheme one of the enumerated list in the typedef ColorScheme
 * @return a GHButton (you can instantiate these without the factory too, like in a storyboard)
 */
+(GHButton*) newButtonForScheme:(ColorScheme)scheme; // not a subclass of UIButton as that's too hard to subclass

/*! @brief clone a color with a change in brightness
 * @param originalColor the starting Color
 * @param brightnessDelta number between -1,1 to ramp up or diminish the brightness (0.1 typical)
 * @return the cloned color
 */
+(UIColor*) newColor:(UIColor*)originalColor withBrightnessDelta:(CGFloat)brightnessDelta;


/*! @brief create a round rect path where the provided rect is given round corners
 * @param aRect a rectangle
 * @param radius ideally less than half the width or height of the rect
 * @return a path user responsible for disposal
 */
+(CGPathRef) newRoundRectPathForRect:(CGRect)aRect withRadius:(CGFloat) radius;

@end


@interface UIView (ControlFactory)
/*! @brief Just a routine to look for SVG documents in the resource folder
* @param theArtworkName a subpath to the svg document
* @attention Does not contain the ".svg" extension
* @return aURL if found, nil otherwise
*/
-(NSURL*) locateArtworkNamed:(NSString*)theArtworkName;
@end
