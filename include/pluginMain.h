#pragma once
#include <maya/MSimple.h>
#include <maya/MPxCommand.h>
#include <maya/MStreamUtils.h>
#include <maya/MArgList.h>
#include <maya/MGlobal.h>
#include <fstream>
#include <iostream> 
#include <string>

/**
 * \brief This is a basic Maya command setup, you can also use DeclareSimpleCommand for very simple command classes
 * https://help.autodesk.com/view/MAYAUL/2019/ENU/?guid=Maya_SDK_MERGED_A_First_Plugin_HelloWorld_html
 */
class MyPlugin : public MPxCommand
{
public:
	MyPlugin() {};
	virtual MStatus doIt(const MArgList& args) override;
	static void* creator();
};