# dlopen-tracer

A `LD_PRELOAD` library that intercepts `dlopen` calls and prints out the full paths to the dynamic libraries loaded.

## Usage

```console
$ make
$ LD_PRELOAD=./dltracer.so python3
[DLTRACER] Calling dlopen on /usr/lib/python3.12/lib-dynload/readline.cpython-312-x86_64-linux-gnu.so
[DLTRACER] /usr/lib/python3.12/lib-dynload/readline.cpython-312-x86_64-linux-gnu.so -> /usr/lib/python3.12/lib-dynload/readline.cpython-312-x86_64-linux-gnu.so
Python 3.12.3 (main, Sep 11 2024, 14:17:37) [GCC 13.2.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> from ctypes import cdll
[DLTRACER] Calling dlopen on /usr/lib/python3.12/lib-dynload/_ctypes.cpython-312-x86_64-linux-gnu.so
[DLTRACER] /usr/lib/python3.12/lib-dynload/_ctypes.cpython-312-x86_64-linux-gnu.so -> /usr/lib/python3.12/lib-dynload/_ctypes.cpython-312-x86_64-linux-gnu.so
[DLTRACER] Calling dlopen on <NULL>
[DLTRACER] <NULL> -> 
>>> cdll.LoadLibrary('libcurl.so.4')
[DLTRACER] Calling dlopen on libcurl.so.4
[DLTRACER] libcurl.so.4 -> /lib/x86_64-linux-gnu/libcurl.so.4
<CDLL 'libcurl.so.4', handle 34d16e40 at 0x72b345af38c0>
```
