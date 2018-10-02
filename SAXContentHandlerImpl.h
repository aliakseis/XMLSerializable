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

	virtual ULONG STDMETHODCALLTYPE AddRef()  override
	{
		return 1;
	}

	virtual ULONG STDMETHODCALLTYPE Release() override
	{
		return 1;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(const IID& rGuid, void** ppOut) override
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
        /* [in] */ ISAXLocator *pLocator)  override;
    
    virtual HRESULT STDMETHODCALLTYPE startDocument( void)  override;
    
    virtual HRESULT STDMETHODCALLTYPE endDocument( void)  override;
    
    virtual HRESULT STDMETHODCALLTYPE startPrefixMapping( 
        /* [in] */ unsigned short *pwchPrefix,
        /* [in] */ int cchPrefix,
        /* [in] */ unsigned short *pwchUri,
        /* [in] */ int cchUri)  override;
    
    virtual HRESULT STDMETHODCALLTYPE endPrefixMapping( 
        /* [in] */ unsigned short *pwchPrefix,
        /* [in] */ int cchPrefix)  override;
    
    virtual HRESULT STDMETHODCALLTYPE startElement( 
        /* [in] */ unsigned short *pwchNamespaceUri,
        /* [in] */ int cchNamespaceUri,
        /* [in] */ unsigned short *pwchLocalName,
        /* [in] */ int cchLocalName,
        /* [in] */ unsigned short *pwchRawName,
        /* [in] */ int cchRawName,
        /* [in] */ ISAXAttributes *pAttributes)  override;
    
    virtual HRESULT STDMETHODCALLTYPE endElement( 
        /* [in] */ unsigned short *pwchNamespaceUri,
        /* [in] */ int cchNamespaceUri,
        /* [in] */ unsigned short *pwchLocalName,
        /* [in] */ int cchLocalName,
        /* [in] */ unsigned short *pwchRawName,
        /* [in] */ int cchRawName);
    
    virtual HRESULT STDMETHODCALLTYPE characters( 
        /* [in] */ unsigned short *pwchChars,
        /* [in] */ int cchChars)  override;
    
    virtual HRESULT STDMETHODCALLTYPE ignorableWhitespace( 
        /* [in] */ unsigned short *pwchChars,
        /* [in] */ int cchChars)  override;
    
    virtual HRESULT STDMETHODCALLTYPE processingInstruction( 
        /* [in] */ unsigned short *pwchTarget,
        /* [in] */ int cchTarget,
        /* [in] */ unsigned short *pwchData,
        /* [in] */ int cchData)  override;
    
    virtual HRESULT STDMETHODCALLTYPE skippedEntity( 
        /* [in] */ unsigned short *pwchName,
        /* [in] */ int cchName)  override;

};

#endif // !defined(AFX_SAXCONTENTHANDLERIMPL_H__517D91C0_0BCF_474D_A77C_10EE27231233__INCLUDED_)
