#define _CRT_SECURE_NO_WARNINGS
#include "Output.h"
#include <string>
#include <ctime>
#include <fstream>

int Output::warnings = 0,
	Output::needToFixes = 0,
	Output::fbxNumber = 0;

std::string
Output::initText =
"<!DOCTYPE html> \n"
"<html> \n"
"<link href = \"https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/css/bootstrap.min.css \" rel = \"stylesheet\" integrity = \"sha384-+0n0xVW2eSR5OomGNYDnhzAbDsOXxcvSN1TPprVMTNDbiYZCxYbOOl7+AMvyTG2x\" crossorigin = \"anonymous\"> \n"
"<script src = \"https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/js/bootstrap.bundle.min.js \" integrity = \"sha384-gtEjrD/SeCtmISkJkNUaaKMoLD0//ElJ19smozuHV6z3Iehds+3Ulb9Bn9Plx0x4\" crossorigin = \"anonymous\"></script> \n"
"<head>\n"
"<style>\n"
"body{\n"
"    background-color: black;\n"
"    font-family: \"Lucida Console\", \"Courier New\", monospace; \n"
"}\n"
"</style>\n"
"</head>\n"
"<body>\n",
Output::time_Init =
"<h1 class = \"display-1\" \n"
"style = \" color:white; \n"
"text-align :center; \" >-FbxChecker-</h1> \n"
"<span class = \"badge rounded-pill bg-secondary\" >",
Output::span_Finish =
"</span>\n",
Output::names_Init =
"<div class = \"accordion\" id = \"accordionPanelsStayOpenExample\"> \n",
Output::name_Init =
"<div class = \"accordion-item\"> \n"
"<h2 class = \"accordion-header\" id = \"panelsStayOpen-headingOne\"> \n"
"<button class = \"accordion-button collapsed\" type = \"button\" data-bs-toggle = \"collapse\" data-bs-target = \"#panelsStayOpen-collapseOne\" aria-expanded = \"false\" aria-controls = \"panelsStayOpen-collapseOne\"> \n",
Output::name_Finish =
"</button> \n"
"</h2> \n"
"<div id = \"panelsStayOpen-collapseOne\" class = \"accordion-collapse collapse\" aria-labelledby = \"panelsStayOpen-headingOne\"> \n",
Output::body_Init =
"<div class=\"accordion-body\"> \n",
Output::warning =
"<span class=\"badge bg-warning text-dark\">Warning</span> \n",
Output::needToFix =
"<span class=\"badge bg-danger\">Needs to be fixed</span> \n",
Output::succes =
"<span class=\"badge bg-success\">Success</span> \n",
Output::numberSpan =
"<span class=\"badge bg-dark\"> ",
Output::div_Finish =
"</div> \n",
Output::endFile =
"</div> \n"
"</body> \n"
"</html> \n",
Output::actualFile = " ", Output::problemsInfo = " ";


void Output::init()
{
	warnings = 0;
	needToFixes = 0;
	std::time_t now = std::time(0);
	actualFile = initText;
	actualFile += time_Init + std::ctime(&now) + span_Finish;
	actualFile += names_Init;
}

void Output::newFbx(std::string fbxName)
{
	fbxNumber++;
	problemsInfo = " ";
	warnings = 0;
	needToFixes = 0;
	actualFile += "<div class = \"accordion-item\"> \n <h2 class = \"accordion-header\" id = \"panelsStayOpen-heading" + std::to_string(fbxNumber) + "\"> \n"
		"<button class = \"accordion-button collapsed\" type = \"button\" data-bs-toggle = \"collapse\" data-bs-target = \"#panelsStayOpen-collapse" + std::to_string(fbxNumber) + "\""
		"aria-expanded = \"false\" aria-controls = \"panelsStayOpen-collapse" + std::to_string(fbxNumber) + "\"> \n" + fbxName;
}

void Output::newFbxProblem(int problemLvl, std::string message)
{
	problemsInfo += body_Init;
	switch (problemLvl) {
		case (1):
			warnings++;
			problemsInfo += warning;
			break;
		case (2):
			needToFixes++;
			problemsInfo += needToFix;
			break;
		default:
			break;
	}
	problemsInfo += message + div_Finish;
}

void Output::endFbx()
{
	if (needToFixes > 0)
		actualFile += needToFix + numberSpan + std::to_string(needToFixes) + span_Finish;
	if (warnings > 0)
		actualFile += warning  + numberSpan + std::to_string(warnings) + span_Finish;
	if(needToFixes == 0 && warnings == 0)
		actualFile += succes;

	actualFile += "</button> \n </h2> \n <div id = \"panelsStayOpen-collapse" + std::to_string(fbxNumber) 
					+ "\" class = \"accordion-collapse collapse\" aria-labelledby = \"panelsStayOpen-heading" + std::to_string(fbxNumber) +"\"> \n" ;
	actualFile += problemsInfo + div_Finish + div_Finish;
}

void Output::end()
{
	actualFile += endFile;
	std::time_t now = std::time(0);
	auto date = std::localtime(&now);
	std::string name = "fbxChecker_" +	std::to_string(date->tm_mon) + "-" +
										std::to_string(date->tm_mday) + "_" + 
										std::to_string(date->tm_hour) + "-" +
										std::to_string(date->tm_min) + "-" + 
										std::to_string(date->tm_sec) +".html";
	std::ofstream outfile(name);

	outfile << actualFile << std::endl;

	outfile.close();
}
