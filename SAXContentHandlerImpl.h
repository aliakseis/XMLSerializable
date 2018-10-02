// SAXContentHandlerImpl.h: interface for the SAXContentHandlerImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAXCONTENTHANDLERIMPL_H__517D91C0_0BCF_474D_A77C_10EE27231233__INCLUDED_)
#define AFX_SAXCONTENTHANDLERIMPL_H__517D91C0_0BCF_474D_A77C_10EE27231233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSAXContentHandlerImpl 
	: public ISAXContentHandler  
{
public:
    CSAXContentHandlerImpl();
    virtual ~CSAXContentHandlerImpl();

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		return 1;
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		return 1;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(const IID& rGuid, void** ppOut)
	{
		if (NULL == ppOut)
			return E_POINTER;

		if (IsEqualGUID(__uuidof(ISAXContentHandler), rGuid))
		{
			*ppOut = static_cast<ISAXContentHandler*>(this);
		}
		else if(IsEqualGUID(__uuidof(IUnknown), rGuid))
		{
			*ppOut = static_cast<IUnknown*>(this);
		}
		else
		{
			return E_NOINTERFACE;
		}
		return S_OK;
	}

protected:
    virtual HRESULT STDMETHODCALLTYPE putDocumentLocator( 
        /* [in] */ ISAXLocator *pLocator);
    
    virtual HRESULT STDMETHODCALLTYPE startDocument( void);
    
    virtual HRESULT STDMETHODCALLTYPE endDocument( void);
    
    virtual HRESULT STDMETHODCALLTYPE startPrefixMapping( 
        /* [in] */ wchar_t *pwchPrefix,
        /* [in] */ int cchPrefix,
        /* [in] */ wchar_t *pwchUri,
        /* [in] */ int cchUri);
    
    virtual HRESULT STDMETHODCALLTYPE endPrefixMapping( 
        /* [in] */ wchar_t *pwchPrefix,
        /* [in] */ int cchPrefix);
    
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
    
    virtual HRESULT STDMETHODCALLTYPE ignorableWhitespace( 
        /* [in] */ wchar_t *pwchChars,
        /* [in] */ int cchChars);
    
    virtual HRESULT STDMETHODCALLTYPE processingInstruction( 
        /* [in] */ wchar_t *pwchTarget,
        /* [in] */ int cchTarget,
        /* [in] */ wchar_t *pwchData,
        /* [in] */ int cchData);
    
    virtual HRESULT STDMETHODCALLTYPE skippedEntity( 
        /* [in] */ wchar_t *pwchName,
        /* [in] */ int cchName);

};

#endif // !defined(AFX_SAXCONTENTHANDLERIMPL_H__517D91C0_0BCF_474D_A77C_10EE27231233__INCLUDED_)
