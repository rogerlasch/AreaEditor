////////////////////////////////////////////////////////////////
// CWindowPlacement 1996 Microsoft Systems Journal.
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
#include "stdafx.h"
#include "AreaEditor.h"
#include "mainfrm.h"
#include "winplace.h"

CWindowPlacement::CWindowPlacement()
{
   // Note: "length" is inherited from WINDOWPLACEMENT
   length = sizeof(WINDOWPLACEMENT);
}

CWindowPlacement::~CWindowPlacement()
{
}

//////////////////
// Restore window placement from profile key
BOOL CWindowPlacement::Restore(LPCSTR lpKeyName, 
                               CWnd* pWnd,
                               const bool bDesktop)
{
   GetProfileWP(lpKeyName);

   // Only restore if window intersets the screen.
   //
   CRect rcTemp, rcScreen;

   if (bDesktop)
     Frame.GetDesktopWindow ()->GetClientRect (rcScreen);
   else
     ::GetClientRect (((CMDIFrameWnd *)&Frame)->m_hWndMDIClient, &rcScreen);

   rcScreen.InflateRect (-10, -10); // margin for error

   if (!::IntersectRect(&rcTemp, &rcNormalPosition, &rcScreen))
      return FALSE;

   pWnd->SetWindowPlacement(this);  // set placement
   return TRUE;
}

//////////////////
// Get window placement from profile.
void CWindowPlacement::GetProfileWP(LPCSTR lpKeyName)
{
   CWinApp *pApp = AfxGetApp();
   ASSERT_VALID(pApp);

   showCmd = pApp->GetProfileInt(lpKeyName, "wp.showCmd", showCmd);
   flags   = pApp->GetProfileInt(lpKeyName, "wp.flags", flags);

ptMinPosition.x = pApp->GetProfileInt(lpKeyName, "wp.ptMinPosition.x", 
      ptMinPosition.x);
ptMinPosition.y = pApp->GetProfileInt(lpKeyName, "wp.ptMinPosition.y",
      ptMinPosition.y);
ptMaxPosition.x = pApp->GetProfileInt(lpKeyName, "wp.ptMaxPosition.x", 
      ptMaxPosition.x);
ptMaxPosition.y = pApp->GetProfileInt(lpKeyName, "wp.ptMaxPosition.y",
      ptMaxPosition.y);

   RECT& rc = rcNormalPosition;  // because I hate typing
   rc.left  = pApp->GetProfileInt(lpKeyName, "wp.left",   rc.left);
   rc.right = pApp->GetProfileInt(lpKeyName, "wp.right",  rc.right);
   rc.top   = pApp->GetProfileInt(lpKeyName, "wp.top",    rc.top);
   rc.bottom= pApp->GetProfileInt(lpKeyName, "wp.bottom", rc.bottom);
}

////////////////
// Save window placement in app profile
void CWindowPlacement::Save(LPCSTR lpKeyName, CWnd* pWnd)
{
   pWnd->GetWindowPlacement(this);
   WriteProfileWP(lpKeyName);
}

//////////////////
// Write window placement to app profile
void CWindowPlacement::WriteProfileWP(LPCSTR lpKeyName)
{
   CWinApp *pApp = AfxGetApp();
   ASSERT_VALID(pApp);
   pApp->WriteProfileInt(lpKeyName, "wp.showCmd",         showCmd);
   pApp->WriteProfileInt(lpKeyName, "wp.flags",           flags);
   pApp->WriteProfileInt(lpKeyName, "wp.ptMinPosition.x", ptMinPosition.x);
   pApp->WriteProfileInt(lpKeyName, "wp.ptMinPosition.y", ptMinPosition.y);
   pApp->WriteProfileInt(lpKeyName, "wp.ptMaxPosition.x", ptMaxPosition.x);
   pApp->WriteProfileInt(lpKeyName, "wp.ptMaxPosition.y", ptMaxPosition.y);
   pApp->WriteProfileInt(lpKeyName, "wp.left",  rcNormalPosition.left);
   pApp->WriteProfileInt(lpKeyName, "wp.right", rcNormalPosition.right);
   pApp->WriteProfileInt(lpKeyName, "wp.top",   rcNormalPosition.top);
   pApp->WriteProfileInt(lpKeyName, "wp.bottom",rcNormalPosition.bottom);
}


//////////////////
// Write window placement to archive
// WARNING: archiving functions are untested.
CArchive& operator<<(CArchive& ar, const CWindowPlacement& wp)
{
   ar << wp.length;
   ar << wp.flags;
   ar << wp.showCmd;
   ar << wp.ptMinPosition;
   ar << wp.ptMaxPosition;
   ar << wp.rcNormalPosition;
   return ar;
}

//////////////////
// Read window placement from archive
// WARNING: archiving functions are untested.
CArchive& operator>>(CArchive& ar, CWindowPlacement& wp)
{
   ar >> wp.length;
   ar >> wp.flags;
   ar >> wp.showCmd;
   ar >> wp.ptMinPosition;
   ar >> wp.ptMaxPosition;
   ar >> wp.rcNormalPosition;
   return ar;
}
