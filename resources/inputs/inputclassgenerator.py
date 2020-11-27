import json
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
        actionsGetter.append("Action "+ actionName + ";")
        actionSrcInit.append(actionName + "{ \"" + actionObj["name"] + "\" }")
        actionFuncCallCstr.append(actionName + "Setup();")
        bindings = []
        for bindingObj in actionObj["bindings"]:
            param = []
            for keyObj in bindingObj["keys"]:
                param.append("InputType::"+keyObj["type"])
                param.append(str(keyObj["key"]))
            param.append("\""+bindingObj["name"] +"\"")
            bindingCreation = classtemplate.bindingDeclaration
            bindingCreation = bindingCreation.replace("${ACTION_NAME}", actionName)
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

    hFile = open(output + "/" + filename + ".h", "x")
    hFile.write(header)
    hFile.close

    sFile = open(output + "/" + filename + ".cpp", "x")
    sFile.write(source)
    sFile.close


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
else:
    outPath = str(defaultPath)

jsonFile = open(filePath)
jsonContent = json.load(jsonFile)

actionMapClassNames = []
actionMapIncludeFile = []
for map in jsonContent["maps"]:
    name = map["name"]
    createActionMap(name, map["actions"], outPath)
    actionMapClassNames.append(name + "ActionMap " + name + ";")
    actionMapIncludeFile.append("#include \"" + name.lower() + "actionmap.h\"")
controlScheme = classtemplate.controlSchemeHeaderFile
controlScheme = controlScheme.replace("${NAME}", jsonContent["name"])
controlScheme = controlScheme.replace("${ACTION_MAPS}", "\n".join(actionMapClassNames))
controlScheme = controlScheme.replace("${ACTION_MAP_INCLUDES}", "\n".join(actionMapIncludeFile))
hFile = open(outPath + "/" + jsonContent["name"].lower() + ".h", "x")
hFile.write(controlScheme)




