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

#include "node-sdl2_image.h"

#include <stdlib.h> // malloc, free
#include <string.h> // strdup

#ifndef strdup
#define strdup(str) strcpy((char*)malloc(strlen(str)+1),str)
#endif

#if defined(__ANDROID__)
#include <android/log.h>
#define printf(...) __android_log_print(ANDROID_LOG_INFO, "printf", __VA_ARGS__)
#endif

#define countof(_a) (sizeof(_a)/sizeof((_a)[0]))

namespace node_sdl2_image {

// load surface

class Task_IMG_Load : public Nanx::SimpleTask
{
public:
	Nan::Persistent<v8::Function> m_callback;
	char* m_file;
	SDL_Surface* m_surface;
	char* m_error;
public:
	Task_IMG_Load(v8::Local<v8::String> file, v8::Local<v8::Function> callback) : 
		m_file(strdup(*v8::String::Utf8Value(file))), 
		m_surface(NULL),
		m_error(NULL)
	{
		m_callback.Reset(callback);
	}
	~Task_IMG_Load()
	{
		m_callback.Reset();
		free(m_file); m_file = NULL; // strdup
		if (m_surface) { SDL_FreeSurface(m_surface); m_surface = NULL; }
		free(m_error); m_error = NULL; // strdup
	}
	void DoWork()
	{
		m_surface = IMG_Load(m_file);
		const char* error = IMG_GetError();
		SDL_ClearError();
		if (error) { m_error = strdup(error); }
	}
	void DoAfterWork(int status)
	{
		Nan::HandleScope scope;
		v8::Local<v8::Value> argv[] = { node_sdl2::WrapSurface::Hold(m_surface), NANX_STRING(m_error) };
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), Nan::New<v8::Function>(m_callback), countof(argv), argv);
		m_surface = NULL; // script owns pointer
	}
};

// save surface

class Task_IMG_SavePNG : public Nanx::SimpleTask
{
public:
	Nan::Persistent<v8::Value> m_hold_surface;
	Nan::Persistent<v8::Function> m_callback;
	SDL_Surface* m_surface;
	char* m_file;
	int m_err;
	char* m_error;
public:
	Task_IMG_SavePNG(v8::Local<v8::Value> surface, v8::Local<v8::String> file, v8::Local<v8::Function> callback) : 
		m_surface(node_sdl2::WrapSurface::Peek(surface)),
		m_file(strdup(*v8::String::Utf8Value(file))), 
		m_err(0),
		m_error(NULL)
	{
		m_hold_surface.Reset(surface);
		m_callback.Reset(callback);
	}
	~Task_IMG_SavePNG()
	{
		m_hold_surface.Reset();
		m_callback.Reset();
		free(m_file); m_file = NULL; // strdup
		free(m_error); m_error = NULL; // strdup
	}
	void DoWork()
	{
		m_err = IMG_SavePNG(m_surface, m_file);
		const char* error = IMG_GetError();
		SDL_ClearError();
		if (error) { m_error = strdup(error); }
	}
	void DoAfterWork(int status)
	{
		Nan::HandleScope scope;
		v8::Local<v8::Value> argv[] = { Nan::New(m_err), NANX_STRING(m_error) };
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), Nan::New<v8::Function>(m_callback), countof(argv), argv);
	}
};

NANX_EXPORT(IMG_Init)
{
	::Uint32 flags = NANX_Uint32(info[0]);
	int err = IMG_Init(flags);
	if (err < 0)
	{
		printf("IMG_Init error: %d\n", err);
	}
	info.GetReturnValue().Set(Nan::New(err));
}

NANX_EXPORT(IMG_Quit)
{
	IMG_Quit();
}

NANX_EXPORT(IMG_GetError)
{
	const char* sdl_image_error = IMG_GetError();
	info.GetReturnValue().Set(NANX_STRING(sdl_image_error));
}

NANX_EXPORT(IMG_ClearError)
{
	SDL_ClearError();
}

NANX_EXPORT(IMG_Load)
{
	v8::Local<v8::String> file = v8::Local<v8::String>::Cast(info[0]);
	v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(info[1]);
	int err = Nanx::SimpleTask::Run(new Task_IMG_Load(file, callback));
	info.GetReturnValue().Set(Nan::New(err));
}

NANX_EXPORT(IMG_SavePNG)
{
	v8::Local<v8::Value> surface = info[0];
	v8::Local<v8::String> file = v8::Local<v8::String>::Cast(info[1]);
	v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(info[2]);
	int err = Nanx::SimpleTask::Run(new Task_IMG_SavePNG(surface, file, callback));
	info.GetReturnValue().Set(Nan::New(err));
}

NAN_MODULE_INIT(init)
{
	// SDL_image.h

	NANX_CONSTANT(target, SDL_IMAGE_MAJOR_VERSION);
	NANX_CONSTANT(target, SDL_IMAGE_MINOR_VERSION);
	NANX_CONSTANT(target, SDL_IMAGE_PATCHLEVEL);

	NANX_CONSTANT(target, IMG_INIT_JPG);
	NANX_CONSTANT(target, IMG_INIT_PNG);
	NANX_CONSTANT(target, IMG_INIT_TIF);
	NANX_CONSTANT(target, IMG_INIT_WEBP);

	NANX_EXPORT_APPLY(target, IMG_Init);
	NANX_EXPORT_APPLY(target, IMG_Quit);

	NANX_EXPORT_APPLY(target, IMG_GetError);
	NANX_EXPORT_APPLY(target, IMG_ClearError);

	NANX_EXPORT_APPLY(target, IMG_Load);
	NANX_EXPORT_APPLY(target, IMG_SavePNG);
}

} // namespace node_sdl2_image

NODE_MODULE(node_sdl2_image, node_sdl2_image::init)
