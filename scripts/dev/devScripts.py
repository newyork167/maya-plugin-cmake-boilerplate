import maya_socket

command = "import sys; sys.append(r'c:\path to my_script');"
command += "import my_script; my_script.run()"

maya_socket.sendCommand(command)