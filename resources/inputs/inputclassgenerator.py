import json
import pathlib
import argparse
import classtemplate

parser = argparse.ArgumentParser()
parser.add_argument("-i", "--input", help="Json input file name to parse and convert")
parser.add_argument("-o", "--output", help="Where to output the result file")

args = parser.parse_args()

if not args.input:
    print("The script cannot run without a input file specified.")
    exit()

defaultPath = pathlib.Path().absolute()
filePath = args.input
#filePath = filePath.replace("\\\\", "/")
if filePath.find("/") == -1:
    filePath = str(defaultPath) + "\\" + filePath
if args.output:
    outPath = args.output

jsonFile = open(filePath)
jsonContent = json.load(jsonFile)

for map in jsonContent["maps"]:
    name = map["name"]



firstMap = classtemplate.mapclass
firstMap = firstMap.replace("${NAME}", "HelloIamName")
firstMap = firstMap.replace("$1", "public: int i = 1;")
