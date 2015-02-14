#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <QDebug>
#include "XMLToHTMLTable.h"

#define HTML_HEADER	"<!DOCTYPE HTML><HTML><HEAD><TITLE></TITLE></HEAD><BODY><TABLE>"
#define HTML_FOOTER	"</TABLE></BODY>"
#define TD_OPEN_TAG	"<TD>"
#define TD_CLOSE_TAG	"</TD>"
#define TR_OPEN_TAG	"<TR>"
#define TR_CLOSE_TAG	"</TR>"

using std::cerr;
using std::endl;

XMLToHTMLTable::XMLToHTMLTable(QString _xmlFileName)
	: m_xmlFileName (_xmlFileName)
{
}

XMLToHTMLTable::~XMLToHTMLTable()
{
}
/**
 * @brief runs functionality for converting xml to html table
 */
bool XMLToHTMLTable::runConversion()
{
	if(!readFile()) {
		return false;
	}

	parseXMLcreateHTML();

	if(writeHTMLFile()) {
		return false;
	}

	return true;
}
/**
 * @brief reads xml file into QDomDocument
 * @return returns true if successfuly read file and dom content otherwise - false
 */
bool XMLToHTMLTable::readFile() 
{
	QFile file(m_xmlFileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		cerr << "Error: Cannot read file " << qPrintable(m_xmlFileName)
			<< ": "
			<< qPrintable(file.errorString())
			<< endl;

		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;

	if (!m_domDocument.setContent(&file, true, &errorStr, &errorLine, 
		&errorColumn)) {
		cerr << "Error: Parse error at line "
			<< errorLine
			<< " column "
			<< errorColumn
			<< " : "
			<< qPrintable(file.errorString())
			<< endl;

		return false;
	}

	return true;
}
/**
 * @brief creates html document
 * @remark code looks mixed up (reading xml/writing html),
 * but could not find more optimal solution for current task
 */
void XMLToHTMLTable::parseXMLcreateHTML() 
{
	QDomElement element = m_domDocument.documentElement();
	/**
	 * start building html document
	 */
	m_htmlDocument = HTML_HEADER;

	if(element.isElement()) {
		QString tr("");
		createHTMLRow(element, tr);
		m_htmlDocument += tr;
	}

	m_htmlDocument += HTML_FOOTER;
}
/**
 * @brief parses tag CD with nested nodes, adds corresponding tags to html
 * @param [in] cdNode QDomNode with nested nodes of record
 * @param [in,out] tr QString record to be filled
 */
void XMLToHTMLTable::createHTMLRow(const QDomNode &node, QString &tr) const
{
	tr += TR_OPEN_TAG;
	/**
	 * add tag itself
	 */
	tr += TD_OPEN_TAG;
	tr += node.toElement().tagName();
	tr += TD_CLOSE_TAG;

	QDomNodeList headerList = node.childNodes();

	for(int i = 0; i < headerList.size(); i++) {
		QDomElement nested = headerList.at(i).toElement();
		if(nested.isElement()) {
			createHTMLRow(nested, tr);
		} else {
			tr += TD_OPEN_TAG;
			tr += node.toElement().text();
			tr += TD_CLOSE_TAG;
		}
	}
}
/**
 * @brief writes html document to file
 */
bool XMLToHTMLTable::writeHTMLFile() const
{
	QString htmlFileName(m_xmlFileName + ".html");
	QFile file(htmlFileName);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		cerr << "Open the html file for writing failed" << endl;

		return false;
	} else {
		QTextStream stream(&file);
		stream << m_htmlDocument;
		file.close();

		return true;
	}
}
