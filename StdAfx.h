// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__48755223_EEB1_11D8_9CE8_E32ABDA13601__INCLUDED_)
#define AFX_STDAFX_H__48755223_EEB1_11D8_9CE8_E32ABDA13601__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifndef STRICT
#define STRICT
#endif


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>

// TODO: reference additional headers your program requires here

#import <msxml3.dll> rename_namespace("MSXML") raw_interfaces_only

using namespace MSXML;

#include <atlbase.h>
#include <atlstr.h>


#include <vector>
#include <map>
#include <string>
#include <stack>
#include <sstream>
#include <iostream>
#include <algorithm>


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__48755223_EEB1_11D8_9CE8_E32ABDA13601__INCLUDED_)
