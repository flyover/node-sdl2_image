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

var sdl2_image = null;
try { sdl2_image = sdl2_image || require('./build/Release/node-sdl2_image.node'); } catch (err) {}
try { sdl2_image = sdl2_image || process._linkedBinding('node_sdl2_image'); } catch (err) {}
try { sdl2_image = sdl2_image || process.binding('node_sdl2_image'); } catch (err) {}
module.exports = sdl2_image;

sdl2_image.version = sdl2_image.version || sdl2_image.SDL_IMAGE_MAJOR_VERSION + "." + sdl2_image.SDL_IMAGE_MINOR_VERSION + "." + sdl2_image.SDL_IMAGE_PATCHLEVEL;

