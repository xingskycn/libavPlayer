//
//  LAVPStream.h
//  libavPlayer
//
//  Created by Takashi Mochizuki on 11/06/18.
//  Copyright 2011 MyCometG3. All rights reserved.
//
/*
 This file is part of livavPlayer.
 
 livavPlayer is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 SimplePlayer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with xvidEncoder; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#import <Cocoa/Cocoa.h>

extern NSString * const LAVPStreamDidEndNotification;

@class LAVPDecoder;

@interface LAVPStream : NSObject {
	NSURL	*url;
	LAVPDecoder *decoder;
	uint64_t _htOffset;	// CVHostTime offset when play
	double_t _rate;	// movie playback ratio
	double_t _posOffset;	// movie time in {0.0, 1.0} 
	NSTimer *timer;	// notification timer when EndOfMovie reached
}

@property (retain, readonly) NSURL *url;

- (id) initWithURL:(NSURL *)url error:(NSError **)errorPtr;
+ (id) streamWithURL:(NSURL *)url error:(NSError **)errorPtr;

- (NSSize) frameSize;
- (BOOL) readyForCurrent;
- (BOOL) readyForTime:(const CVTimeStamp*)ts;
- (CVPixelBufferRef) getCVPixelBufferForCurrent;
- (CVPixelBufferRef) getCVPixelBufferForTime:(const CVTimeStamp*)ts;

- (double_t) duration;
- (double_t) position;
- (void) setPosition:(double_t)newPosition;
- (double_t) rate;
- (void) setRate:(double_t)newRate;
- (void) play;
- (void) stop;
- (void) gotoBeggining;
- (void) gotoEnd;

@end

#if 0
@interface LAVStream (control)
- (void) setCurrentTime:(QTTime)newTime;
- (void) stepForward;
- (void) stepBackward;
- (QTTime) duration;
- (QTTime) currentTime;
- (float) rate;
- (void) setRate:(float)rate;
- (float) volume;
- (void) setVolume:(float)volume;
- (BOOL) muted;
- (void) setMuted:(BOOL)muted;
@end

@interface LAVStream (attributes)
- (id) attributeForKey:(NSString *)attributeKey;
- (void) setAttribute:(id)attr ForKey:(id)key;
- (NSDictionary *) movieAttributes;
- (void) setMovieAttributes:(NSDictionary *)attrDict;
- (NSString *)description;
@end
#endif