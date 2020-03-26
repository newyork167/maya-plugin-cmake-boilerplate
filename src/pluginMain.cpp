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

MStatus executeMELCommand(std::string melCommand) {
    // Execute the MEL code
    MString commandString = MString(melCommand.c_str());
    return MGlobal::executeCommand(commandString);
}

/**
* \brief This will set up a basic menu to call our test command and set up test menu items that don't do anything yet (For you to attach something to!)
*/
void MyPlugin::setupMenu(std::string menuName) {
    // Setup the main menu button
    std::string menuCommand = "";
    menuCommand += "if (`menu -exists " + menuName + "`) {";
    menuCommand += "\tdeleteUI " + menuName + ";";
    menuCommand += "}";
    menuCommand += "menu -p \"MayaWindow\" -label \"" + menuName + "\" " + menuName + ";";
    menuCommand += "menuItem -label \"Run\" -command " + menuName + ";";
    menuCommand += "menuItem - label \"Open\";";
    menuCommand += "menuItem - label \"Save\";";
    menuCommand += "menuItem - divider true;";
    menuCommand += "menuItem - label \"Quit\";";
    menuCommand += "menu - label \"Help\" - helpMenu true;";
    menuCommand += "menuItem - label \"About Application...\";";

    // Execute the MEL code
    MStatus melRunStatus = executeMELCommand(menuCommand);
}

void MyPlugin::deleteMenu(std::string menuName) {
    std::string menuCommand = "";

    menuCommand += "if (`menu -exists " + menuName + "`) {";
    menuCommand += "\tdeleteUI " + menuName + ";";
    menuCommand += "}";

    MStatus melRunStatus = executeMELCommand(menuCommand);
}

MSelectionList MyPlugin::getCurrentSelectedObject() {
	MDagPath node;
	MObject component;
	MSelectionList list;
	MFnDagNode nodeFn;
	MGlobal::getActiveSelectionList(list);
	for (unsigned int index = 0; index < list.length(); index++)
	{
		list.getDagPath(index, node, component);
		nodeFn.setObject(node);
		MStreamUtils::stdOutStream() << nodeFn.name().asChar() << " is selected" << endl;
	}

    return list;
}

/**
 * \brief This is the main function called by Maya when you run the "MyPlugin" command. For further examples refer to
 * https://help.autodesk.com/view/MAYAUL/2019/ENU/?guid=Maya_SDK_MERGED_Command_plug_ins_MPxCommand_html
 */
MStatus MyPlugin::doIt(const MArgList& argList) {
    MStreamUtils::stdOutStream() << "Running " << PLUGIN_NAME << "!" << std::endl;

    // Test function to get the currently selected objects in the scene
    MSelectionList selectedObjects = this->getCurrentSelectedObject();

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
    MyPlugin::setupMenu(PLUGIN_NAME);
    return status;
}

/**
 * \brief This is where you deregister your plugin commands and if all goes well the plugin is unloaded from Maya
 */
MStatus uninitializePlugin(MObject obj) {
    MFnPlugin plugin(obj);
    MyPlugin::deleteMenu(PLUGIN_NAME);
    MStatus status = plugin.deregisterCommand(PLUGIN_NAME);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return status;
}