#ifndef INC_XMLPARSER_
#define INC_XMLPARSER_

#pragma warning (disable : 4786 )

#include <string>
#include <map>

class MKeyValue : public std::map<std::string, std::string> 
{
	void writeAttributes ( std::ostream &os ) const;

public:
	void put( const char *what, int value );
	void put( const char *what, float value );
	void put( const char *what, bool value );
	void put( const char *what, const char *value );

	int    getInt (const char *what, int default_value) const;
	float  getFloat (const char *what, float default_value) const;
	bool   getBool (const char *what, bool default_value) const;
	
	std::string getString(const std::string &what, const std::string default_value) const;

	void	 writeSingle (std::ostream &os, const char *what) const;

	void   writeStartElement( std::ostream &os, const char *what) const;
	void   writeEndElement( std::ostream &os, const char *what) const;
};


class CXMLParser 
{
	static void xmlStartElement(void *userData, const char *elem, const char **atts);
	static void xmlData(void *userData, const char *data, int length);
	static void xmlEndElement(void *userData, const char *elem);
 
	bool				abort_parse;
	bool				notify_missing_files;

protected:
	std::string xml_error;
	void				xmlSetNotifyMissingFilesError( bool how ) { notify_missing_files = how; }

public:
	CXMLParser( );
	virtual void onStartElement (const std::string &elem, MKeyValue &atts);
	virtual void onData (const std::string &data);
	virtual void onEndElement (const std::string &elem);

	void xmlAbortParse( );
	bool xmlParseFile (const std::string &filename);
	bool xmlParseStream (std::istream &is, const char *stream_name = NULL);
	const std::string &getError() const { return xml_error; }
};


#endif 
