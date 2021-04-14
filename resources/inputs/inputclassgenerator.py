import json
import os
import pathlib
import argparse
import classtemplate

def createActionMap(mapName, jsonActionMap, output):
    actionsSetupFunction = []
    actionsGetter = []
    actionSrcInit = []
    actionFuncInit = []
    actionFuncCallCstr = []
    for actionObj in jsonActionMap:
        actionName = actionObj["name"][0].lower() + actionObj["name"][1:]
        actionsSetupFunction.append("void " + actionName + "Setup();")
        actionsGetter.append(actionObj["bindingType"] + "Action "+ actionName + ";")
        actionSrcInit.append(actionName + "{ \"" + actionObj["name"] + "\" }")
        actionFuncCallCstr.append(actionName + "Setup();")
        bindings = []
        for bindingObj in actionObj["bindings"]:
            param = []
            for keyObj in bindingObj["keys"]:
                param.append("InputType::"+keyObj["type"])
                param.append(str(keyObj["key"]))
            param.append(actionName + ", \""+bindingObj["name"] +"\"")
            bindingCreation = classtemplate.bindingDeclaration
            bindingCreation = bindingCreation.replace("${TYPE}", actionObj["bindingType"])
            bindingCreation = bindingCreation.replace("${PARAM}", ", ".join(param))
            bindings.append(bindingCreation)
        actionInit = classtemplate.mapClassActionSetupTemplate
        actionInit = actionInit.replace("${NAME}", mapName)
        actionInit = actionInit.replace("${ACTION_NAME}", actionName)
        actionInit = actionInit.replace("${ACTION_BINDINGS}", "\n\t".join(bindings))
        actionFuncInit.append(actionInit)

    header = classtemplate.mapClassHeaderFile
    header = header.replace("${NAME}", mapName)
    header = header.replace("${ACTIONS_NAMES}", "\n\t".join(actionsGetter))
    header = header.replace("${ACTIONS_SETUP_FUNCTIONS_DECLARATION}", "\n\t".join(actionsSetupFunction))

    source = classtemplate.mapClassSourceFile
    filename = classtemplate.mapClassFileName.replace("${NAME}", mapName.lower())
    source = source.replace("${NAME}", mapName).replace("${GENERATED_HEADER_MAP_FILENAME}",filename)
    source = source.replace("${ACTIONS_INIT}", ",".join(actionSrcInit))
    source = source.replace("${ACTION_SETUP_FUNCTION_DEFINITION}", "\n\t".join(actionFuncInit))
    source = source.replace("${ACTIONS_SETUP_FUNCTION_CALLING}", "\n\t".join(actionFuncCallCstr))

    file = open(output + "/" + filename + ".h", "w")
    file.write(header)
    file.close

    file = open(output + "/" + filename + ".cpp", "w")
    file.write(source)
    file.close


parser = argparse.ArgumentParser()
parser.add_argument("-i", "--input", help="Json input file name to parse and convert")
parser.add_argument("-o", "--output", help="Where to output the result file")

args = parser.parse_args()

if not args.input:
    print("The script cannot run without a input file specified.")
    exit()

defaultPath = pathlib.Path().absolute()
filePath = args.input

if filePath.find("/") == -1:
    filePath = str(defaultPath) + "\\" + filePath
if args.output:
    outPath = args.output
    if not os.path.exists(outPath):
        os.makedirs(outPath)
else:
    outPath = str(defaultPath)

jsonFile = open(filePath)
jsonContent = json.load(jsonFile)

actionMapClassNames = []
actionMapIncludeFile = []
actionMapAdd = []
for map in jsonContent["maps"]:
    name = map["name"]
    createActionMap(name, map["actions"], outPath)
    actionMapClassNames.append(name + "ActionMap " + name + ";")
    actionMapIncludeFile.append("#include \"" + name.lower() + "actionmap.h\"")
    actionMapAdd.append("m_actionMaps.push_back(&" + name + ");")
controlSchemeHeader = classtemplate.controlSchemeHeaderFile
controlSchemeHeader = controlSchemeHeader.replace("${NAME}", jsonContent["name"])
controlSchemeHeader = controlSchemeHeader.replace("${ACTION_MAPS}", "\n".join(actionMapClassNames))
controlSchemeHeader = controlSchemeHeader.replace("${ACTION_MAP_INCLUDES}", "\n".join(actionMapIncludeFile))
file = open(outPath + "/" + jsonContent["name"].lower() + ".h", "w")
file.write(controlSchemeHeader)
file.close()

controlSchemeSrc = classtemplate.controlSchemeSourceFile
controlSchemeSrc = controlSchemeSrc.replace("${HEADER_FILE_NAME}", jsonContent["name"].lower())
controlSchemeSrc = controlSchemeSrc.replace("${CLASSNAME}", jsonContent["name"])
controlSchemeSrc = controlSchemeSrc.replace("${ADD_ACTION_MAPS}", "\n".join(actionMapAdd))
file = open(outPath + "/" + jsonContent["name"].lower() + ".cpp", "w")
file.write(controlSchemeSrc)
file.close()




