#include "stdafx.h"
#include "Note.h"
#include "sstream"

CNote::CNote()
{
	for (int i = 0; i <= 5; i++) {
		sends[i] = (i == 0) ? 1.0 : 0.0; 
	}
}


CNote::~CNote()
{
}

void CNote::XmlLoad(IXMLDOMNode * xml, std::wstring & instrument)
{
	// Remember the xml node and the instrument.
	m_node = xml;
	m_instrument = instrument;

	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i<len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "measure")
		{
			// The file has measures that start at 1.  
			// We'll make them start at zero instead.
			value.ChangeType(VT_I4);
			m_measure = value.intVal - 1;
		}
		else if (name == "beat")
		{
			// Same thing for the beats.
			value.ChangeType(VT_R8);
			m_beat = value.dblVal - 1;
		}
		else
		{
			for (int i = 0; i <= 5; i++) {
				std::ostringstream convert;
				convert << "send";
				convert << i;
				std::string temp = convert.str();
				std::wstring nodeName = std::wstring(temp.begin(), temp.end());
				if (wcscmp(name, nodeName.c_str()) == 0) {
					value.ChangeType(VT_R8);
					sends[i] = value.dblVal;
				}
			}
		}

	}
}
bool CNote::operator<(const CNote &b)
{
	if (m_measure < b.m_measure)
		return true;
	if (m_measure > b.m_measure)
		return false;
	if (m_beat < b.m_beat)
		return true;

	return false;
}

void CNote::SetSend(int send, double value) {
	if (send > 5) {
		//index out of range. TODO: Should throw exception if time permits.
		return;
	}
	sends[send] = value;
}

double CNote::GetSend(int send) {
	if (send > 5) {
		//index out of range. TODO: Should throw exception if time permits.
		return 0.0;
	}
	return sends[send];
}