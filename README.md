# XMLSerializable
Taken from https://www.codeguru.com/cpp/cpp/cpp_mfc/serial/article.php/c8083/Defining-XML-Serializable-Objects-Using-Macros.htm

It is often necessary to make your C++ objects serializable to/from XML. It is simple to do so in Java or C#, for example, by using reflection, but not always in C++. It would be interesting to introduce some brief but portable way to describe objects' serializable properties. The prototype presented allows defining XML serializable objects using macros in an attributes-like manner because each serializable object/property needs to be described only once in the class definition, for example:

<pre>class CEmployee : public CXmlSerializable
{
public:
   BEGIN_META_MAP(CEmployee)
      META_PROP(CSTLString,     Region)
   END_META_MAP
};

class COrder : public CXmlSerializable
{
   BEGIN_META_MAP(COrder)
      META_PROP(CSTLString,     ShipCity)
      META_PROP(CSTLString,     EmployeeName)
      META_OBJECTS(CEmployee,   Employees)
   END_META_MAP
};

class CCustomer : public CXmlSerializable
{
   BEGIN_META_MAP(CCustomer)
      META_PROP(CSTLString,     CustomerID)
      META_PROP(CSTLString,     ContactName)
      META_OBJECTS(COrder,      Orders)
   END_META_MAP
};

class CCustomersList : public CXmlSerializable
{
   BEGIN_META_MAP(CCustomersList)
      META_OBJECTS(CCustomer,   Customers)
   END_META_MAP
};
</pre>

Microsoft SAX parser implementation is used here to read XML. The META_PROP and META_OBJECTS macros assemble mapping arrays of helper methods for the parser content handler and the bodies of the objects ToXml() methods.

One small challenge here was finding a way to assemble something like a linked list at compile time to glue properties declarations together. The solution found is to use templatized inner classes along with the \_\_LINE__ macro (this code is a part of the META_PROP macro, back slashes at the row ends are omitted here, all the \_\_LINE__ values are equal inside each META_PROP or META_OBJECTS macro):

<pre>
template&lt;int id> struct CDescriptor&lt;id, __LINE__>
{
   enum
   {
      ESetDataFuncPos = CDescriptor&lt;id-1>::ESetDataFuncPos,
      EAddObjFuncPos  = CDescriptor&lt;id-1>::EAddObjFuncPos + 1
   };
   static void Setup(CMetaInfo* pInfo)
   {
      CDescriptor&lt;id-1>::Setup(pInfo);
      pInfo->m_pAddObjFunc[EAddObjFuncPos].first = L#name;
      pInfo->m_pAddObjFunc[EAddObjFuncPos].second =
             ClassAddNew##name;
   }
   ...
};
</pre>

ClassAddNew##name here is a static inner helper function; it has the next prototype:

<pre>typedef bool (* SET_DATA_FUNC)(CXmlSerializable*,
                               const wchar_t*, size_t);
</pre>

Objects data writing to XML is implemented in the similar manner. Because the

<pre>
template&lt;typename T>
inline bool Convert(const wchar_t* pwsz, size_t nLength, T& out)
</pre>

and

<pre>
template&lt;typename T>
inline void WriteField(std::wostream& s, const T& data)
</pre>

data exchange functions involved are templatized, they can be customized for specific data types such as COleDateTime or std::vector<BYTE> for binary/image data.

The XS_BASE macro can be manipulated to hide implementation details in the separate data access objects library.

The sample application is intended to demonsrate the mechanism proposed. It just loads an XML document example to the data object and then makes the object write itself to the standard output stream. It's as simple as that (error handling omitted for brevity):

<pre>CComPtr&lt;ISAXXMLReader> pSAXXMLReader;
CSAXObjectContentHandlerImpl saxObjectContentHandler;

HRESULT hr = pSAXXMLReader.CoCreateInstance(__uuidof(SAXXMLReader));

hr = pSAXXMLReader->putContentHandler(&saxObjectContentHandler);

CCustomersList customersList;
// add root objects
saxObjectContentHandler.AddRootObject(L"ROOT", &customersList);

hr = pSAXXMLReader->parse(CComVariant(g_pszXml));

std::wostringstream ostr;
customersList.ToXml(ostr);
</pre>

