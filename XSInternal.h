// File: XSInternal.h

#pragma once


inline bool IsSerializatonNeeded(...)
{
    return true;
}


template<typename T> 
inline bool IsSerializatonNeeded(const std::basic_string<T>& str)
{
    return !str.empty();
}

inline bool IsSerializatonNeeded(const GUID& rGuid)
{
    return !InlineIsEqualGUID(GUID_NULL, rGuid);
}


typedef bool (* SET_DATA_FUNC)(CXmlSerializable*, const wchar_t*, size_t);
typedef CXmlSerializable* (* ADD_NEW_OBJECT_FUNC)(CXmlSerializable*);


template<typename T>
inline bool Convert(const wchar_t* pwsz, size_t nLength, T& out)
{
    if (0 == nLength)
    {
        return true;
    }
    return !(std::wistringstream(std::wstring(pwsz, nLength)) >> out).fail();
}


template<>
inline bool Convert(const wchar_t* pwsz, size_t nLength, GUID& out)
{
    if (pwsz[0] != L'{')
    {
        return SUCCEEDED(CLSIDFromString(
            const_cast<LPOLESTR>((L'{' + std::wstring(pwsz, nLength) + L'}').c_str()), &out));
    }
    else
    {
        return SUCCEEDED(CLSIDFromString(const_cast<LPOLESTR>(pwsz), &out));
    }
}

template<>
inline bool Convert(const wchar_t* pwsz, size_t nLength, std::string& out)
{
    CAtlStringA buf(pwsz, (int)nLength);
    out.assign(buf, buf.GetLength());
    return true;
}

template<>
inline bool Convert(const wchar_t* pwsz, size_t nLength, std::wstring& out)
{
    out.assign(pwsz, nLength);
    return true;
}


inline std::wostream& 
operator <<(std::wostream& s, const std::string& rstr)
{
    return s << static_cast<LPCWSTR>(CAtlStringW(rstr.c_str(), (int)rstr.length()));
}


template<typename T> 
inline bool ReadField(CXmlSerializable* , T& field            
            , const wchar_t* pwszData, size_t nLength)
{
    return Convert(pwszData, nLength, field);                                
}


template<typename T> 
inline void WriteField(std::wostream& s, const T& data)
{
    std::wostringstream ostr;
    ostr << data;

    // TODO escape
    s << ostr.str();
}


template<> 
inline void WriteField(std::wostream& s, const LONG& data)
{
    s << data;
}


template<> 
inline void WriteField(std::wostream& s, const GUID& data)
{
    OLECHAR wszGuid[100] = {0};
    int nLength = StringFromGUID2(data, wszGuid, sizeof(wszGuid) / sizeof(wszGuid[0]));
    if (nLength > 1)
    {
        wszGuid[nLength - 2] = 0;
        s << wszGuid + 1;
    }
}


#pragma intrinsic(memcmp)

// STRING_DATA construction should be re-enterable 
struct STRING_DATA
{
    const wchar_t* pwsz;
    int nLength;

    template<typename T> STRING_DATA& operator = (const T& src)
    {
        // Use cast to ensure that we only allow character arrays
        (static_cast<const wchar_t[sizeof(src) / sizeof(src[0])]>(src));
        pwsz = src;
        nLength = sizeof(src) / sizeof(src[0]) - 1;
        return *this;
    }

    bool operator == (const STRING_DATA& other) const
    {
        return nLength == other.nLength 
            && !memcmp(pwsz, other.pwsz, nLength * sizeof(wchar_t));
    }
};

#pragma function(memcmp)

template<typename T>
inline bool operator == (const std::pair<STRING_DATA, T>& left, const STRING_DATA& right)
{
    return left.first == right;
}


template<typename T> struct STRING_FUNC_PAIR
{
    STRING_DATA first;
    T second;
};

template<typename T> 
bool operator == (const STRING_FUNC_PAIR<T>& left, const STRING_DATA& right)
{
    return left.first == right;
}

typedef STRING_FUNC_PAIR<SET_DATA_FUNC> SET_DATA_FUNC_PAIR;
typedef STRING_FUNC_PAIR<ADD_NEW_OBJECT_FUNC> ADD_OBJ_FUNC_PAIR;


// CMetaInfo construction should be re-enterable 
// Inilialized in descendants
struct CMetaInfo
{
    SET_DATA_FUNC_PAIR* m_pSetDataFunc;
    int m_nSetDataFuncSize;

    ADD_OBJ_FUNC_PAIR* m_pAddObjFunc;
    int m_nAddObjFuncSize;
};

template<typename T, int size>
class CMetaInfoData
{
    SET_DATA_FUNC_PAIR m_arrSetDataFunc[size];    
public:
    CMetaInfoData()
    {
        static_cast<T*>(this)->m_pSetDataFunc = m_arrSetDataFunc;
        static_cast<T*>(this)->m_nSetDataFuncSize = size;
    }
};

template<typename T>
class CMetaInfoData<T, 0>
{
public:
    CMetaInfoData()
    {
        static_cast<T*>(this)->m_pSetDataFunc = NULL;
        static_cast<T*>(this)->m_nSetDataFuncSize = 0;
    }
};


template<typename T, int size>
class CMetaInfoObj
{
    ADD_OBJ_FUNC_PAIR    m_arrAddObjFunc[size];
public:
    CMetaInfoObj()
    {
        static_cast<T*>(this)->m_pAddObjFunc = m_arrAddObjFunc;
        static_cast<T*>(this)->m_nAddObjFuncSize = size;
    }
};

template<typename T>
class CMetaInfoObj<T, 0>
{
public:
    CMetaInfoObj()
    {
        static_cast<T*>(this)->m_pAddObjFunc = NULL;
        static_cast<T*>(this)->m_nAddObjFuncSize = 0;
    }
};

template<typename T>
inline T* Append(std::deque<T>& v)
{
    size_t nSize = v.size();                                            
    v.resize(nSize + 1);                                            
    T* pChild = &v[nSize];
    return pChild;
}


#define META_PROP_INTERNAL(name)                                                \
    private:                                                                    \
        static bool ClassSet##name(CXmlSerializable* pObj                       \
            , const wchar_t* pwszData, size_t nLength)                          \
        {                                                                       \
            return ReadField(pObj, static_cast<TheClass*>(pObj)->m_##name       \
                , pwszData, nLength);                                           \
        }                                                                       \
        template<int id> struct CDescriptor<id, __COUNTER__-ID_REFERENCE_POINT> \
        {                                                                       \
            enum                                                                \
            {                                                                   \
                ESetDataFuncPos = CDescriptor<id-1>::ESetDataFuncPos + 1,       \
                EAddObjFuncPos = CDescriptor<id-1>::EAddObjFuncPos              \
            };                                                                  \
            static void Setup(CMetaInfo* pInfo)                                 \
            {                                                                   \
                CDescriptor<id-1>::Setup(pInfo);                                \
                pInfo->m_pSetDataFunc[ESetDataFuncPos].first = L#name;          \
                pInfo->m_pSetDataFunc[ESetDataFuncPos].second = ClassSet##name; \
            }                                                                   \
            static void SaveAttributes(const TheClass* pObj                     \
                , std::wostream& s)                                             \
            {                                                                   \
                CDescriptor<id-1>::SaveAttributes(pObj, s);                     \
                if (IsSerializatonNeeded(pObj->m_##name))                       \
                {                                                               \
                    s << L" " L#name L"=\"";                                    \
                    WriteField(s, pObj->m_##name);                              \
                    s << L"\"";                                                 \
                }                                                               \
            }                                                                   \
            static void SaveElements(const TheClass* pObj                       \
                , std::wostream& s)                                             \
            {                                                                   \
                CDescriptor<id-1>::SaveElements(pObj, s);                       \
            }                                                                   \
        };

#define META_OBJECTS_INTERNAL(name)                                             \
    private:                                                                    \
        static CXmlSerializable* ClassAddNew##name(CXmlSerializable* pObj)      \
        {                                                                       \
            auto& v = static_cast<TheClass*>(pObj)->m_v##name;                  \
            return Append(v);                                                   \
        }                                                                       \
        template<int id> struct CDescriptor<id, __COUNTER__-ID_REFERENCE_POINT> \
        {                                                                       \
            enum                                                                \
            {                                                                   \
                ESetDataFuncPos = CDescriptor<id-1>::ESetDataFuncPos,           \
                EAddObjFuncPos = CDescriptor<id-1>::EAddObjFuncPos + 1          \
            };                                                                  \
            static void Setup(CMetaInfo* pInfo)                                 \
            {                                                                   \
                CDescriptor<id-1>::Setup(pInfo);                                \
                pInfo->m_pAddObjFunc[EAddObjFuncPos].first = L#name;            \
                pInfo->m_pAddObjFunc[EAddObjFuncPos].second = ClassAddNew##name;\
            }                                                                   \
            static void SaveAttributes(const TheClass* pObj                     \
                , std::wostream& s)                                             \
            {                                                                   \
                CDescriptor<id-1>::SaveAttributes(pObj, s);                     \
            }                                                                   \
            static void SaveElements(const TheClass* pObj                       \
                , std::wostream& s)                                             \
            {                                                                   \
                CDescriptor<id-1>::SaveElements(pObj, s);                       \
                for (const auto& v : pObj->m_v##name)                           \
                    v.ToXml(s, L#name);                                         \
            }                                                                   \
        };

#define BEGIN_META_MAP(classname)                                               \
        template<int id, int> friend struct CDescriptor;                        \
    private:                                                                    \
        enum { ID_REFERENCE_POINT = __COUNTER__ };                              \
        typedef classname TheClass;                                             \
        template<int id, int=id> struct CDescriptor                             \
        {                                                                       \
            enum                                                                \
            {                                                                   \
                ESetDataFuncPos = CDescriptor<id-1>::ESetDataFuncPos,           \
                EAddObjFuncPos = CDescriptor<id-1>::EAddObjFuncPos              \
            };                                                                  \
            static void Setup(CMetaInfo* pInfo)                                 \
            {                                                                   \
                CDescriptor<id-1>::Setup(pInfo);                                \
            }                                                                   \
            static void SaveAttributes(const TheClass* pObj                     \
                , std::wostream& s)                                             \
            {                                                                   \
                CDescriptor<id-1>::SaveAttributes(pObj, s);                     \
            }                                                                   \
            static void SaveElements(const TheClass* pObj                       \
                , std::wostream& s)                                             \
            {                                                                   \
                CDescriptor<id-1>::SaveElements(pObj, s);                       \
            }                                                                   \
        };                                                                      \
        template<int id> struct CDescriptor<id, 0>                              \
        {                                                                       \
            enum                                                                \
            {                                                                   \
                ESetDataFuncPos = -1,                                           \
                EAddObjFuncPos = -1                                             \
            };                                                                  \
            static void Setup(CMetaInfo*) {}                                    \
            static void SaveAttributes(const TheClass*, std::wostream&) {}      \
            static void SaveElements(const TheClass*, std::wostream&) {}        \
        };

#define END_META_MAP                                                            \
    private:                                                                    \
        typedef CDescriptor<__COUNTER__ - ID_REFERENCE_POINT - 1> CFinalDescr;  \
        struct CFinalMetaInfo : public CMetaInfo                                \
        , public CMetaInfoData<CFinalMetaInfo, CFinalDescr::ESetDataFuncPos + 1>\
        , public CMetaInfoObj<CFinalMetaInfo, CFinalDescr::EAddObjFuncPos + 1>  \
        {                                                                       \
            CFinalMetaInfo()                                                    \
            {                                                                   \
                CFinalDescr::Setup(this);                                       \
            }                                                                   \
        };                                                                      \
        XS_API const CMetaInfo* GetMetaInfo() const override                    \
        {                                                                       \
            static const CFinalMetaInfo g_metaInfo;                             \
            return &g_metaInfo;                                                 \
        }                                                                       \
        static void ToXml(const TheClass* pObj, std::wostream& s                \
            , LPCWSTR pwszTag)                                                  \
        {                                                                       \
            s << L"<" << pwszTag;                                               \
            CFinalDescr::SaveAttributes(pObj, s);                               \
            if (CFinalDescr::EAddObjFuncPos > -1)                               \
            {                                                                   \
                s << L">";                                                      \
                CFinalDescr::SaveElements(pObj, s);                             \
                s << L"</" << pwszTag << L">";                                  \
            }                                                                   \
            else                                                                \
                s << L"/>";                                                     \
        }                                                                       \
    public:                                                                     \
        XS_API void ToXml(std::wostream& s                                      \
            , LPCWSTR pwszRoot = NULL) const override                           \
        {                                                                       \
            ToXml(this, s, (NULL == pwszRoot)? L"object" : pwszRoot);           \
        }
