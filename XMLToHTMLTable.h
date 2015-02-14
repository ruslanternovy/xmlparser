#ifndef XMLToHTMLTable_H
#define XMLToHTMLTable_H

#include <QtCore/QObject>
#include <QDomDocument>

class XMLToHTMLTable
{
public:
	XMLToHTMLTable(QString _xmlFileName);
	virtual ~XMLToHTMLTable();
	bool runConversion();
private:
	bool readFile();
	void parseXMLcreateHTML();
	void createHTMLRow(const QDomNode &node, QString &tr) const;
	bool writeHTMLFile() const;
private:
	QDomDocument m_domDocument;
	QString m_htmlDocument;
	QString m_xmlFileName;
};

#endif // XMLToHTMLTable_H
