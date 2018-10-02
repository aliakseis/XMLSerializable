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
        /* [in] */ unsigned short *pwchNamespaceUri,
        /* [in] */ int cchNamespaceUri,
        /* [in] */ unsigned short *pwchLocalName,
        /* [in] */ int cchLocalName,
        /* [in] */ unsigned short *pwchRawName,
        /* [in] */ int cchRawName,
        /* [in] */ ISAXAttributes *pAttributes) override;
    
    virtual HRESULT STDMETHODCALLTYPE endElement( 
        /* [in] */ unsigned short *pwchNamespaceUri,
        /* [in] */ int cchNamespaceUri,
        /* [in] */ unsigned short *pwchLocalName,
        /* [in] */ int cchLocalName,
        /* [in] */ unsigned short *pwchRawName,
        /* [in] */ int cchRawName) override;
    
    virtual HRESULT STDMETHODCALLTYPE characters( 
        /* [in] */ unsigned short *pwchChars,
        /* [in] */ int cchChars) override;

	virtual HRESULT STDMETHODCALLTYPE processingInstruction( 
            /* [in] */ unsigned short *pwchTarget,
            /* [in] */ int cchTarget,
            /* [in] */ unsigned short *pwchData,
            /* [in] */ int cchData) override;

private:
	typedef std::map<std::wstring, CXmlSerializable*> CMapObjects;
	CMapObjects m_mapRootObjects;

	std::stack<bool> m_stObjPushedFlags;
	std::stack<CXmlSerializable*> m_stObjects;
};
