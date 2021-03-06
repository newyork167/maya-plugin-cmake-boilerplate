#include "../include/pluginMain.h"

/**
 * \brief Enter the name of your plugin here, will also create a command matching the name
 * This is for a simple command setup, for multiple commands you will need to change the initializePlugin and uninitializePlugin functions
 */
#define PLUGIN_NAME "MyPlugin"

/**
 * \brief This is the creator method that spawns new instances of your plugin, used in the initializePlugin function below
 */
void* MyPlugin::creator() { return new MyPlugin; }

/**
 * \brief This is the main function called by Maya when you run the "MyPlugin" command. For further examples refer to
 * https://help.autodesk.com/view/MAYAUL/2019/ENU/?guid=Maya_SDK_MERGED_Command_plug_ins_MPxCommand_html
 */
MStatus MyPlugin::doIt(const MArgList& argList) {
	MStreamUtils::stdOutStream() << "Hello World!";
	return MS::kSuccess;
}

/**
 * \brief This is where your plugin is initialized during the loading into Maya.
 * As a boilerplate this file includes the MyPlugin class. For a cleaner setup you will want to put each command in it's own
 * separate .cpp/.h files and/or folders.
 */
MStatus initializePlugin(MObject obj) {
	MFnPlugin plugin(obj, "Enter Your Name", "0.1", "Any");
	MStatus status = plugin.registerCommand(PLUGIN_NAME, MyPlugin::creator);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	return status;
}

/**
 * \brief This is where you deregister your plugin commands and if all goes well the plugin is unloaded from Maya
 */
MStatus uninitializePlugin(MObject obj) {
	MFnPlugin plugin(obj);
	MStatus status = plugin.deregisterCommand(PLUGIN_NAME);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	return status;
}