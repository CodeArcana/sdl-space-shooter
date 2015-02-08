/*******************************************************************//*
 * Implementation of the StateEntityParser class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-07
 * @modified    2015-02-08
 *********************************************************************/
#include "StateEntityParser.h"

#include "ApplicationState.h"
#include "tinyxml.h"

StateEntityParser::StateEntityParser()
{
}

StateEntityParser::~StateEntityParser()
{
}

// This function will parse through an XML file to construct an array of
// EntityXmlStruct structures
std::vector<EntityXmlStruct> StateEntityParser::parse(ApplicationState* state,
                                                    int parsingLayer)
{
    std::vector<EntityXmlStruct> error;

    TiXmlDocument xmlDoc;

    // Return false if the XML file is not found
    if (!xmlDoc.LoadFile(state->getXmlPath().c_str()))
    {
        fprintf(stderr, "[ERROR] parse(): Xml file not found.\n");
        return error;
    }

    // The root element of this xml file
    TiXmlElement* rootElement = xmlDoc.RootElement();

    // The parsing layer root element of this xml file
    TiXmlElement* rootParsingLayer = NULL;

    // Parses through State subelements to find correct parsing layer
    // element, then assigning it to it's own root variable
    for (   TiXmlElement* e = rootElement->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        if (e->Value() == mapEnumeration(parsingLayer))
        {
            rootParsingLayer = e;
        }
    }

    // Return false if the parsing layer element is not found
    if (rootParsingLayer == NULL)
    {
        fprintf(stderr, "[ERROR] parse(): Parsing layer element not found.\n");
        return error;
    }

    // Gets the number of elements in order to construct array
    int arraySize = 0;
    for (   TiXmlElement* e = rootParsingLayer->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        arraySize++;
    }
    EntityXmlStruct xmlStruct[arraySize];

    // Parses through subelements of the parsing layer element and
    // fills values of the array of EntityXmlStruct as we go
    int index = 0;
    for (   TiXmlElement* e = rootParsingLayer->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        if (e->Attribute("id") != NULL)
        {
            // Converting c_str to std::string
            const char* cString = e->Attribute("id");
            int cStringSize = strlen(cString);
            xmlStruct[index].id.assign(cString, cStringSize);
        }

        if (e->Attribute("name") != NULL)
        {
            // Converting c_str to std::string
            const char* cString = e->Attribute("name");
            int cStringSize = strlen(cString);
            xmlStruct[index].name.assign(cString, cStringSize);
        }

        if (e->Attribute("type") != NULL)
        {
            // Converting c_str to std::string
            const char* cString = e->Attribute("type");
            int cStringSize = strlen(cString);
            xmlStruct[index].type.assign(cString, cStringSize);
        }

        if (e->Attribute("data") != NULL)
        {
            // Converting c_str to std::string
            const char* cString = e->Attribute("data");
            int cStringSize = strlen(cString);
            xmlStruct[index].data.assign(cString, cStringSize);
        }

        if (e->Attribute("texture") != NULL)
        {
            // Converting c_str to std::string
            const char* cString = e->Attribute("texture");
            int cStringSize = strlen(cString);
            xmlStruct[index].texture.assign(cString, cStringSize);
        }

        if (e->Attribute("function") != NULL)
        {
            // Converting c_str to std::string
            const char* cString = e->Attribute("function");
            int cStringSize = strlen(cString);
            xmlStruct[index].function.assign(cString, cStringSize);
        }

        if (e->Attribute("x") != NULL)
        {
            xmlStruct[index].renderRect.x = atoi(e->Attribute("x"));
        }

        if (e->Attribute("y") != NULL)
        {
            xmlStruct[index].renderRect.y = atoi(e->Attribute("y"));
        }

        if (e->Attribute("width") != NULL)
        {
            xmlStruct[index].renderRect.w = atoi(e->Attribute("width"));
        }

        if (e->Attribute("height") != NULL)
        {
            xmlStruct[index].renderRect.h = atoi(e->Attribute("height"));
        }

        if (e->Attribute("alphaEnabled") != NULL)
        {
            xmlStruct[index].alphaEnabled = true;
        }

        index++;
    }

    std::vector<EntityXmlStruct> xmlStructVector(xmlStruct, xmlStruct + sizeof(xmlStruct)/sizeof(EntityXmlStruct));
    return xmlStructVector;
}

// Private method that takes an enumerated int and returns a string
// representation of it
std::string StateEntityParser::mapEnumeration(int parsingLayer)
{
    std::string mappedString = "";
    switch (parsingLayer)
    {
        case PARSE_BACKGROUND:
            mappedString = "Background";
            break;

        case PARSE_PHYSICAL:
            mappedString = "Physical";
            break;

        case PARSE_EFFECT:
            mappedString = "Effect";
            break;

        case PARSE_UI:
            mappedString = "Ui";
            break;
    }
    return mappedString;
}