# ProxyLoader

**A lightweight proxy DLL loader targeting IL2CPP Unity applications.**

---

## Overview

**ProxyLoader** is a DLL proxy that forwards exported functions, allowing you to intercept calls between an IL2CPP-based Unity game and its native libraries. It’s designed to be minimal and flexible, making it easy to inject logging, hooks, or custom behavior without patching the original binary.

## Features

- Built with **MSYS2 ucrt64** and **Ninja**.  
- Uses **MinHook** (included as a git submodule) for inline function hooking.  
- Supports custom exports via a `.def` file.  
- Clean wrapper types for library handles and function pointers.  
- Focused on simplicity and extensibility.

## Custom Exports

Exports are defined in a `.def` file. You can edit this file to control which symbols are forwarded, for example:

```def
LIBRARY version
EXPORTS
    D3D10CreateDevice
    D3D11CreateDevice
    DirectSoundCreate
```
When built, the resulting DLL will be named version.dll and will forward or intercept only the functions listed.
