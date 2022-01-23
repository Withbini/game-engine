#include "ShipGame.hpp"
#include "AsteroidGame.hpp"
#include "openglGame.hpp"

#include <string>
#include <sstream>
#include <iostream>


#include "3dGame.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

bool ParseJson2(Document &doc, const std::string& jsonData)
{
	if (doc.Parse(jsonData.c_str()).HasParseError())
	{
		return false;
	}

	return doc.IsObject();
}

std::string JsonDocToString2(Document &doc)
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
	return buffer.GetString();
}

void TestJson_Parse2()
{
	// 1. Parse a JSON string into DOM.
	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
	Document doc;
	ParseJson2(doc, json);

	// 2. Modify it by DOM.
	Value& s = doc["stars"];
	s.SetInt(s.GetInt() + 1);

	std::string jsonString = JsonDocToString2(doc);
	printf(jsonString.c_str());
}

void TestJson_AddMember2()
{
	// 1. Parse a JSON string into DOM.
	//Document doc;
	//doc.SetObject();
	Document doc(kObjectType);

	Document::AllocatorType& allocator = doc.GetAllocator();
	doc.AddMember("project", "rapidjson", allocator);
	doc.AddMember("stars", 10, allocator);

	std::string jsonString = JsonDocToString2(doc);
	printf(jsonString.c_str());
}

int main(int argc,char* argv[])
{
	//Game game;
	//ShipGame game;
	//AsteroidGame game;
	//Game game;
	//openglGame game;
	GL3DGame game;
	bool success = game.Initialize();
	if(success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}
