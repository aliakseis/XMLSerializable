#pragma once
#include "saxcontenthandlerimpl.h"

class CXmlSerializable;

class CSAXObjectContentHandlerImpl :
	public CSAXContentHandlerImpl
{
public:
	CSAXObjectContentHandlerImpl();
	~CSAXObjectContentHandlerImpl();

	void AddRootObject(const wchar_t* pwszName, CXmlSerializable* pObject); 

protected:
    virtual HRESULT STDMETHODCALLTYPE startElement( 
        /* [in] */ wchar_t *pwchNamespaceUri,
        /* [in] */ int cchNamespaceUri,
        /* [in] */ wchar_t *pwchLocalName,
        /* [in] */ int cchLocalName,
        /* [in] */ wchar_t *pwchRawName,
        /* [in] */ int cchRawName,
        /* [in] */ ISAXAttributes *pAttributes);
    
    virtual HRESULT STDMETHODCALLTYPE endElement( 
        /* [in] */ wchar_t *pwchNamespaceUri,
        /* [in] */ int cchNamespaceUri,
        /* [in] */ wchar_t *pwchLocalName,
        /* [in] */ int cchLocalName,
        /* [in] */ wchar_t *pwchRawName,
        /* [in] */ int cchRawName);
    
    virtual HRESULT STDMETHODCALLTYPE characters( 
        /* [in] */ wchar_t *pwchChars,
        /* [in] */ int cchChars);

	virtual HRESULT STDMETHODCALLTYPE processingInstruction( 
            /* [in] */ wchar_t *pwchTarget,
            /* [in] */ int cchTarget,
            /* [in] */ wchar_t *pwchData,
            /* [in] */ int cchData);

private:
	typedef std::map<std::wstring, CXmlSerializable*> CMapObjects;
	CMapObjects m_mapRootObjects;

	std::stack<bool> m_stObjPushedFlags;
	std::stack<CXmlSerializable*> m_stObjects;
};
