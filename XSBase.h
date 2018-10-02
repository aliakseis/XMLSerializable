// File: XSBase.h

#pragma once

#ifdef XS_BASE
#define XS_API __declspec(dllexport)
#else
#define XS_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
// common part



typedef std::basic_string<TCHAR> CSTLString;

//////////////////////////////////////////////////////////////////////////
//	XmlSerializable

struct CMetaInfo;

class CXmlSerializable
{
friend class CSAXObjectContentHandlerImpl;

public:
	CXmlSerializable() : m_pParent(NULL) {}
	virtual ~CXmlSerializable() {}

	void SetParent(CXmlSerializable* pParent) { m_pParent = pParent; }
	const CXmlSerializable* GetParent() const { return m_pParent; }

	virtual void ToXml(std::wostream&, LPCWSTR /*pwszRoot*/ = NULL) const {}

private:
	virtual const CMetaInfo* GetMetaInfo() const { return NULL; }

	CXmlSerializable* m_pParent;
};


template<typename T> struct PROP_TYPE_TRAITS 
{ 
	typedef const T& TSetterArg; 
	typedef T TGetterReturn; 
};


template<> struct PROP_TYPE_TRAITS<CSTLString> 
{ 
	typedef LPCTSTR TSetterArg; 
	typedef CSTLString TGetterReturn; 
};


#ifdef XS_BASE

#include "XSInternal.h"

#else// XS_BASE

#define META_PROP_INTERNAL(type, name)
#define META_OBJECTS_INTERNAL(type, name)
#define BEGIN_META_MAP(classname)
#define END_META_MAP														\
	private:																\
		virtual XS_API const CMetaInfo* GetMetaInfo() const;				\
	public:																	\
		virtual XS_API void ToXml(std::wostream&, LPCWSTR = NULL) const;

#endif// XS_BASE


#define PROP_GETTER(type, name)												\
	public:																	\
		PROP_TYPE_TRAITS<type >::TGetterReturn Get_##name() const			\
		{ return m_##name; }												

#define PROP_SETTER(type, name)												\
	public:																	\
		void Set_##name(PROP_TYPE_TRAITS<type >::TSetterArg value)			\
		{ m_##name = value; }												

#define META_PROP_READONLY(type, name)										\
	private:																\
		type m_##name;														\
	public:																	\
	PROP_GETTER(type, name)													\
	META_PROP_INTERNAL(type, name)

#define META_PROP(type, name)												\
	PROP_SETTER(type, name)													\
	META_PROP_READONLY(type, name)


#define META_OBJECTS(type, name)											\
	public:																	\
		std::deque<type > m_v##name;										\
	META_OBJECTS_INTERNAL(type, name)

