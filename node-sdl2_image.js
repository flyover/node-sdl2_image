/**
 * Copyright (c) Flyover Games, LLC.  All rights reserved. 
 *  
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated 
 * documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to 
 * whom the Software is furnished to do so, subject to the 
 * following conditions: 
 *  
 * The above copyright notice and this permission notice shall 
 * be included in all copies or substantial portions of the 
 * Software. 
 *  
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY 
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 */

var node_sdl2_image = null;
try { node_sdl2_image = node_sdl2_image || require('./build/Release/node-sdl2_image.node'); } catch (err) {}
try { node_sdl2_image = node_sdl2_image || process._linkedBinding('node_sdl2_image'); } catch (err) {}
try { node_sdl2_image = node_sdl2_image || process.binding('node_sdl2_image'); } catch (err) {}
module.exports = node_sdl2_image;

node_sdl2_image.version = node_sdl2_image.version || node_sdl2_image.SDL_IMAGE_MAJOR_VERSION + "." + node_sdl2_image.SDL_IMAGE_MINOR_VERSION + "." + node_sdl2_image.SDL_IMAGE_PATCHLEVEL;

node_sdl2_image.IMG_CheckError = node_sdl2_image.IMG_CheckError || function ()
{
	var error = node_sdl2_image.IMG_GetError(); node_sdl2_image.IMG_ClearError();
	if (error) { console.error("SDL_image", error); }
	return error;
};

/// var node_sdl2_image = require('@flyover/node-sdl2_image');
/// var sdl_image = node_sdl2_image.IMG();
/// node_sdl2_image.IMG_* -> sdl_image.*
node_sdl2_image.IMG = function (out) {
	out = out || {};
	var re = /^(IMG_)(.*)/;
	for (var key in node_sdl2_image) {
		var match = key.match(re);
		if (match && match[2]) {
			//console.log(key, match[2]);
			out[match[2]] = node_sdl2_image[key];
		} else {
			//console.log("!!!", key);
			out[key] = node_sdl2_image[key];
		}
	}
	return out;
}

//node_sdl2_image.IMG();
