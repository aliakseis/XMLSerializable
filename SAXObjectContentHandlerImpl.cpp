#include "StdAfx.h"

#include "saxobjectcontenthandlerimpl.h"
#include "XSBase.h"


#define RETURN_FAILED_HR(statement)	\
{									\
	HRESULT hr = (statement);		\
	if (FAILED(hr))					\
	{								\
		ATLASSERT(FALSE);			\
		return hr;					\
	}								\
}


CSAXObjectContentHandlerImpl::CSAXObjectContentHandlerImpl()
{
}

CSAXObjectContentHandlerImpl::~CSAXObjectContentHandlerImpl()
{
}


HRESULT STDMETHODCALLTYPE CSAXObjectContentHandlerImpl::startElement( 
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ wchar_t *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ ISAXAttributes *pAttributes)
{
	CXmlSerializable* pObject = NULL;

	if (m_stObjects.empty())
	{
		std::wstring strLocalName(pwchLocalName, cchLocalName);
		CMapObjects::iterator iter = m_mapRootObjects.find(strLocalName);
		if (iter != m_mapRootObjects.end())
			pObject = iter->second;
	}
	else
	{
		CXmlSerializable* pParent = m_stObjects.top();
		if (pParent != NULL)
		{
			// Embedded objects
			const CMetaInfo* pMetaInfo = pParent->GetMetaInfo();
			if (pMetaInfo != NULL)
			{
				STRING_DATA stringData;
				stringData.pwsz = pwchLocalName;
				stringData.nLength = cchLocalName;

				ADD_OBJ_FUNC_PAIR* pEnd
					= pMetaInfo->m_pAddObjFunc + pMetaInfo->m_nAddObjFuncSize;
				ADD_OBJ_FUNC_PAIR* pFind
					= std::find(pMetaInfo->m_pAddObjFunc, pEnd, stringData);
				if (pFind != pEnd)
				{
					pObject = pFind->second(pParent);
				}
			}
		}
	}

	if (pObject != NULL)
	{
		m_stObjects.push(pObject);

		const CMetaInfo* pMetaInfo = pObject->GetMetaInfo();
		int nLength = 0;
		if (pMetaInfo != NULL && pAttributes != NULL
			&& S_OK == pAttributes->getLength(&nLength))
		{	// Object properties
			for (int i = 0; i < nLength; ++i)
			{
				STRING_DATA stringData = {0};
				RETURN_FAILED_HR(pAttributes->getLocalName(
					i, const_cast<wchar_t**>(&stringData.pwsz), &stringData.nLength));

				SET_DATA_FUNC_PAIR* pEnd 
					= pMetaInfo->m_pSetDataFunc + pMetaInfo->m_nSetDataFuncSize;
				SET_DATA_FUNC_PAIR* pFind 
					= std::find(pMetaInfo->m_pSetDataFunc, pEnd, stringData);
				if (pFind != pEnd)
				{
					wchar_t *pwchValue = NULL;
					int cchValue = 0;
					RETURN_FAILED_HR(pAttributes->getValue(i, &pwchValue, &cchValue));
					if (!pFind->second(pObject, pwchValue, cchValue))
					{
						return DISP_E_TYPEMISMATCH;
					}
				}
			}
		}
	}

	m_stObjPushedFlags.push(pObject != NULL);

    return S_OK;
}
        
       
HRESULT STDMETHODCALLTYPE CSAXObjectContentHandlerImpl::endElement( 
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ wchar_t *,
            /* [in] */ int ,
            /* [in] */ wchar_t *,
            /* [in] */ int )
{
	if (m_stObjPushedFlags.top())
		m_stObjects.pop();
	m_stObjPushedFlags.pop();

    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CSAXObjectContentHandlerImpl::characters( 
            /* [in] */ wchar_t *,
            /* [in] */ int )
{
    return S_OK;
}
        
void CSAXObjectContentHandlerImpl::AddRootObject(const wchar_t* pwszName, CXmlSerializable* pObject)
{
	m_mapRootObjects[pwszName] = pObject;
}

const wchar_t wszMSSQLError[] = L"MSSQLError";
const wchar_t wszHResult[] = L"HResult=\"0x";

HRESULT STDMETHODCALLTYPE CSAXObjectContentHandlerImpl::processingInstruction( 
            /* [in] */ wchar_t *pwchTarget,
            /* [in] */ int cchTarget,
            /* [in] */ wchar_t *pwchData,
            /* [in] */ int cchData)
{
	//MSSQLError
	if (cchTarget == sizeof(wszMSSQLError) / sizeof(wszMSSQLError[0]) - 1 
		&& !memcmp(wszMSSQLError, pwchTarget, sizeof(wszMSSQLError) - sizeof(wchar_t)))
	{
		if (cchData > sizeof(wszHResult) / sizeof(wszHResult[0]) - 1 
			&& !memcmp(wszHResult, pwchData, sizeof(wszHResult) - sizeof(wchar_t)))
		{
			HRESULT hr = wcstoul(pwchData + sizeof(wszHResult) / sizeof(wszHResult[0]) - 1, NULL, 16);
			if (FAILED(hr))
				return hr;
		}
		return E_FAIL;
	}
    return S_OK;
}
