# To update the files download web-font 
# from https://materialdesignicons.com and copy _variables.scss 
# and MaterialIcons-Regular.ttf in this folder and run this python 
# file to generate the qml file

# Copyright (C) 2017 Aseman Team





#Create the file
def _createFile ():
	file = open("MaterialDesignIcons.qml", "w+")
	file.write(_header + "\n" + _content +"}")
	file.close()

_header = """ /*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

pragma Singleton
import QtQuick 2.10

QtObject {
    readonly property string family: "Material Design Icons"; """




lookup = '$mdi-icons: ('
lineNumber = int()
_content = ""
_defaultString = """readonly property string """
materialFile = open("_variables.scss", "r")

try: 
	#Find the line starts with icon variables
	for num, line in enumerate(materialFile, 1):
		if lookup in line:
			# print ('found at line:' , num)
			lineNumber = num +1
			break

	#Add contents
	for i, line in enumerate(materialFile):
		if i >= num and line != ');':

			line = line.replace(',' , '')
			line = line.replace('"', '').strip()
			head, sep, tail = line.partition(':')

			head = 'mdi_' + head
			head = head.replace('-' , '_')
			tail = '"\\u'+tail.strip() + '";'
			# print (head + sep + tail)
			_content += "\t" + _defaultString + head + sep + tail + "\n"



finally:
	materialFile.close()

_createFile()

