/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaEditorView.h : interface of the CAreaEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AREAEDITORVIEW_H__30BE0361_E9F1_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_AREAEDITORVIEW_H__30BE0361_E9F1_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CAreaEditorView : public CTreeView
{
protected: // create from serialization only
	CAreaEditorView();
	DECLARE_DYNCREATE(CAreaEditorView)

// Attributes
public:

  CSplitterWnd * m_pSplitterWindow;

	CAreaEditorDoc* GetDocument();

  HTREEITEM m_hdlTreeArea;
  HTREEITEM m_hdlTreeHelps;
  HTREEITEM m_hdlTreeMobiles;
  HTREEITEM m_hdlTreeMudprogs;
  HTREEITEM m_hdlTreeObjects;
  HTREEITEM m_hdlTreeObjprogs;
  HTREEITEM m_hdlTreeResets;
  HTREEITEM m_hdlTreeRooms;
  HTREEITEM m_hdlTreeShops;
  HTREEITEM m_hdlTreeRepairs;

// Operations
public:


  HTREEITEM AddTreeItem (CMUDitem * pItem, 
                          const HTREEITEM hdlBranch,
                          const HTREEITEM hInsertAfter = TVI_LAST);

  HTREEITEM GetItem (void) const;

  void Refresh (void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAreaEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAreaEditorView)
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAreaDeleteItem();
	afx_msg void OnUpdateAreaDeleteItem(CCmdUI* pCmdUI);
	afx_msg void OnAreaAddItem();
	afx_msg void OnUpdateAreaAddItem(CCmdUI* pCmdUI);
	afx_msg void OnAreaFind();
	afx_msg void OnAreaFindNext();
	afx_msg void OnUpdateAreaFindNext(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateAreaDuplicateItem(CCmdUI* pCmdUI);
	afx_msg void OnAreaDuplicateItem();
	afx_msg void OnFilePrint();
	afx_msg void OnViewRefresh();
	afx_msg void OnAreaCheckallareas();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AreaEditorView.cpp
inline CAreaEditorDoc* CAreaEditorView::GetDocument()
   { return (CAreaEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREAEDITORVIEW_H__30BE0361_E9F1_11D1_A20A_0000B4595568__INCLUDED_)
