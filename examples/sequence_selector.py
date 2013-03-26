from optparse import OptionParser
from sets import Set

parser = OptionParser()
parser.add_option("-s", "--solect", dest="sel", help="(input) list of selected entries", default="", metavar="FILE")
parser.add_option("-t", "--sel_column", dest="scol", help="(input) column in --select with the entries", default="1", metavar="FILE")
parser.add_option("-a", "--all", dest="all", help="(input) a file with a line with info for each entry", default="", metavar="FILE")
parser.add_option("-c", "--all_column", dest="acol", help="(input) column in --all with the entries", default="1", metavar="FILE")
(options, args) = parser.parse_args()

selef = open(options.sel)
selected = []
for line in selef:
	token = line.split()
	selected.append( token[int(options.scol)-1] )

selecteds = Set(selected)

allf = open(options.all)
for line in allf:
	token = line.split()
	if (token[int(options.acol)-1] in selected ):
		print line,
