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
            /* [in] */ unsigned short *,
            /* [in] */ int ,
            /* [in] */ unsigned short *,
            /* [in] */ int )
{
    return S_OK;
}
        
        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::endPrefixMapping( 
            /* [in] */ unsigned short *,
            /* [in] */ int )
{
    return S_OK;
}
        

        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::startElement( 
            /* [in] */ unsigned short *,
            /* [in] */ int ,
            /* [in] */ unsigned short *,
            /* [in] */ int ,
            /* [in] */ unsigned short *,
            /* [in] */ int ,
            /* [in] */ ISAXAttributes *)
{
    return S_OK;
}
        
       
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::endElement( 
            /* [in] */ unsigned short *,
            /* [in] */ int ,
            /* [in] */ unsigned short *,
            /* [in] */ int ,
            /* [in] */ unsigned short *,
            /* [in] */ int )
{
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::characters( 
            /* [in] */ unsigned short *,
            /* [in] */ int )
{
    return S_OK;
}
        

HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::ignorableWhitespace( 
            /* [in] */ unsigned short *,
            /* [in] */ int )
{
    return S_OK;
}
        

HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::processingInstruction( 
            /* [in] */ unsigned short *,
            /* [in] */ int ,
            /* [in] */ unsigned short *,
            /* [in] */ int )
{
    return S_OK;
}
        
        
HRESULT STDMETHODCALLTYPE CSAXContentHandlerImpl::skippedEntity( 
            /* [in] */ unsigned short *,
            /* [in] */ int )
{
    return S_OK;
}


