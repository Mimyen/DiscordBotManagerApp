#pragma once

#include <wx/wx.h>
#include <wx/dc.h>
#include <wx/rawbmp.h>
#include <wx/graphics.h>
#include <wx/image.h>
#include <wx/panel.h>
#include <wx/icon.h>
#include <wx/bitmap.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/popupwin.h>
#include <wx/dcbuffer.h>
#include <wx/msw/winundef.h>
#include <wx/msw/wrapwin.h>
#include <Windows.h>
#include <dwmapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <functional>
#include <string>
#include <vector>
#include <fstream>
#include <d2d1.h>
#include <boost/asio.hpp>

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define _CRT_SECURE_NO_WARNINGS