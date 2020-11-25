/*
The MIT License (MIT)

Copyright (c) 2016, Unity Technologies

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

This file is taken from:
https://github.com/Unity-Technologies/NativeRenderingPlugin
*/

#pragma once
#include "IUnityInterface.h"

#ifndef __OBJC__
    #error metal plugin is objc code.
#endif
#ifndef __clang__
    #error only clang compiler is supported.
#endif

@class NSBundle;
@protocol MTLDevice;
@protocol MTLCommandBuffer;
@protocol MTLCommandEncoder;
@protocol MTLTexture;
@class MTLRenderPassDescriptor;

// Should only be used on the rendering thread unless noted otherwise.
UNITY_DECLARE_INTERFACE(IUnityGraphicsMetal)
{
    NSBundle*               (UNITY_INTERFACE_API * MetalBundle)();
    id<MTLDevice>(UNITY_INTERFACE_API * MetalDevice)();

    id<MTLCommandBuffer>(UNITY_INTERFACE_API * CurrentCommandBuffer)();

    // for custom rendering support there are two scenarios:
    // you want to use current in-flight MTLCommandEncoder (NB: it might be nil)
    id<MTLCommandEncoder>(UNITY_INTERFACE_API * CurrentCommandEncoder)();
    // or you might want to create your own encoder.
    // In that case you should end unity's encoder before creating your own and end yours before returning control to unity
    void(UNITY_INTERFACE_API * EndCurrentCommandEncoder)();

    // returns MTLRenderPassDescriptor used to create current MTLCommandEncoder
    MTLRenderPassDescriptor* (UNITY_INTERFACE_API * CurrentRenderPassDescriptor)();

    // converting trampoline UnityRenderBufferHandle into native RenderBuffer
    UnityRenderBuffer(UNITY_INTERFACE_API * RenderBufferFromHandle)(void* bufferHandle);

    // access to RenderBuffer's texure
    // NB: you pass here *native* RenderBuffer, acquired by calling (C#) RenderBuffer.GetNativeRenderBufferPtr
    // AAResolvedTextureFromRenderBuffer will return nil in case of non-AA RenderBuffer or if called for depth RenderBuffer
    // StencilTextureFromRenderBuffer will return nil in case of no-stencil RenderBuffer or if called for color RenderBuffer
    id<MTLTexture>(UNITY_INTERFACE_API * TextureFromRenderBuffer)(UnityRenderBuffer buffer);
    id<MTLTexture>(UNITY_INTERFACE_API * AAResolvedTextureFromRenderBuffer)(UnityRenderBuffer buffer);
    id<MTLTexture>(UNITY_INTERFACE_API * StencilTextureFromRenderBuffer)(UnityRenderBuffer buffer);
};
UNITY_REGISTER_INTERFACE_GUID(0x992C8EAEA95811E5ULL, 0x9A62C4B5B9876117ULL, IUnityGraphicsMetal)
