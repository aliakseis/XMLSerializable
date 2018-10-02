// SAXContentHandlerImpl.cpp: implementation of the SAXContentHandlerImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SAXContentHandlerImpl.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSAXContentHandlerImpl::CSAXContentHandlerImpl()
{
}

CSAXContentHandlerImpl::~CSAXContentHandlerImpl()
{
}



HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::putDocumentLocator( 
            /* [in] */ ISAXLocator *
            )
{
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::startDocument()
{
    return S_OK;
}
        

        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::endDocument( void)
{
    return S_OK;
}
        
        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::startPrefixMapping( 
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ wchar_t *,
            /* [in] */ int )
{
    return S_OK;
}
        
        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::endPrefixMapping( 
            /* [in] */ wchar_t *,
            /* [in] */ int )
{
    return S_OK;
}
        

        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::startElement( 
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ ISAXAttributes *)
{
    return S_OK;
}
        
       
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::endElement( 
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ wchar_t *,
            /* [in] */ int )
{
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::characters( 
            /* [in] */ wchar_t *,
            /* [in] */ int )
{
    return S_OK;
}
        

HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::ignorableWhitespace( 
            /* [in] */ wchar_t *,
            /* [in] */ int )
{
    return S_OK;
}
        

HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::processingInstruction( 
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ wchar_t *,
            /* [in] */ int )
{
    return S_OK;
}
        
        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::skippedEntity( 
            /* [in] */ wchar_t *,
            /* [in] */ int )
{
    return S_OK;
}


