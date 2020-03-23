import maya_socket

with open('CMakeLists.txt') as cmake_file:
	for line in cmake_file.readlines():
		if "project(" in line:
			plugin_name = line.split("project(")[-1].split(")")[0]
			break
print("Loading {plugin_name}".format(plugin_name=plugin_name))
maya_socket.SendCommand('print("Unloading plugin\\n")')
maya_socket.SendCommand('unloadPlugin "{plugin_name}"'.format(plugin_name=plugin_name))