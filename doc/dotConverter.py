
from glob import glob
import os
from queue import Queue
import re

def convertfile(name):
    res = ''
    trans = {}
    try:
        with open(name) as file:
            for line in file:
                match = re.search('[ ]*(Node[\d]+) \[label=\"\{(.+?)\\\\', line)
                if match:
                    trans[match.groups()[0]] = match.groups()[1]
        
            file.seek(0)
            for line in file:
                res += line
        
            for k,v in trans.items():
                res = res.replace(' '+k+' ',' "'+v+'" ')

            #Remove gray filling
            res = res.replace('fillcolor="grey75"', 'fillcolor="white"')
    
        return res
    except FileNotFoundError:
        return ''


def mergefiles(name):
    if 'lexer' in name:
        print("LEX")
    inherit = convertfile(name+'__inherit__graph.dot')
    coll = convertfile(name+'__coll__graph.dot')

    linesSeen = set()

    with open(name+'__merged__graph.dot', 'w') as result:
        for line in coll.splitlines(True)[:-1]:
            if line not in linesSeen:
                linesSeen.add(line)
                result.write(line)
        
        for line in inherit.splitlines(True)[:-1]:
            if line not in linesSeen:
                linesSeen.add(line)
                result.write(line)
        
        result.write('}\n')

def parse_extra_conns(filename):
    rels = {}
    with open(filename) as readfile:
        for line in readfile:
            match = re.search('[ ]*"(.+?)" \[label=\"', line)
            if match:
                fromName = match.groups()[0]
                match = re.findall(r'std::vector\\+< (\b.+?\b).*?\\+> (\b.+?\b)', line)
                if match:
                    rels[fromName] = match
                    print(fromName, match)
    
    return rels

def dedup(filename):
    nodes = {}
    with open(filename) as file:
        with open(filename[:-4]+'_deduped.dot', "w") as out:
            for line in file:
                match = re.search('[ ]*"(.+?)" \[label=\"', line)
                if match:
                    name = match.groups()[0]
                    if name in nodes:
                        l = len(line)
                        if l > nodes[name][0]:
                            nodes[name] = (l, line)
                    else:
                        nodes[name] = (len(line), line)
                else:
                    if line != '}\n':
                        out.write(line)
        
            for _,(_,v) in nodes.items():
                out.write(v)
        
            out.write('}\n')



def write_extra_conns(filename, extra_conns):
    with open(filename[:-4]+'_final.dot', 'w') as out:
        with open(filename) as infile:
            for line in infile:
                if line != '}\n':
                    out.write(line)
        for toNode, conns in extra_conns.items():
            for fromNode, name in conns:
                out.write(f'"{fromNode}" -> "{toNode}" [color="grey25",fontsize="10",style="solid",label=" -{name}" ,arrowhead="odiamond",fontname="Helvetica"];\n')
        
        out.write('}\n')



def merge_all(path):
    files = glob(path+'/*__merged__graph.dot')

    linesSeen = set()

    with open(path+'/merged.dot', 'w') as result:
        #header
        result.write('digraph Merged\n{\n // LATEX_PDF_SIZE\n  edge [fontname="Helvetica",fontsize="10",labelfontname="Helvetica",labelfontsize="10"];\nnode [fontname="Helvetica",fontsize="10",shape=record];\n')

        for filename in files:
            with open(filename) as file:
                for line in file.readlines()[5:-1]:
                    if line not in linesSeen:
                        linesSeen.add(line)
                        result.write(line)
        
        
        #footer
        result.write('}\n')


def convertdir(path):
    files = glob(path+'/*__coll__graph.dot')

    #Get file begin
    names = [x[:-17] for x in files]

    for name in names:
        mergefiles(name)

def do_bfs(graph, start, maxDepth):
    visited = [start, ]
    qu = [start, ]

    depth = 0
    while qu:
        s = qu.pop(0)

        if depth >= maxDepth:
            break
        
        try:
            for neighbour in graph[s]:
                if neighbour not in visited:
                    visited.append(neighbour)
                    qu.append(visited)
        except KeyError:
            pass
        depth+=1
    
    return visited

def get_complete_uml(mergedUMLFileName, classname):
    graph = {}
    with open(mergedUMLFileName) as file:
        for line in file:
            if 'odiamond' in line:
                match = re.findall('"(.+?)" -> "(.+?)"', line)
                if match:
                    to, fr = match[0]
                    if fr in graph:
                        if to not in graph[fr]:
                            graph[fr].append(to)
                    else:
                        graph[fr] = [to,]
    
    neededNodes = do_bfs(graph, classname, 1)

    with open('/'.join(mergedUMLFileName.split('/')[:-1])+'/'+classname+'.dot', 'w') as out:
        with open(mergedUMLFileName) as infile:
            lines = infile.readlines()
            out.writelines(lines[:5])

            for line in lines[5:-1]:
                if '->' in line:
                    to, fr = re.findall('"(.+?)" -> "(.+?)"', line)[0]
                    if to in neededNodes and fr in neededNodes:
                        out.write(line)
                else:
                    name = re.findall('[ ]*"(.+?)" \[label=\"', line)[0]
                    if name in neededNodes:
                        out.write(line)
            
            out.write('}\n')

if __name__ == "__main__":
    dir = os.getcwd()
    if not dir.endswith('doc'):
        dir += '/doc'
    """convertdir(dir+'/dotfiles')
    merge_all(dir+'/dotfiles')
    dedup(dir+'/dotfiles/merged.dot')
    extra = parse_extra_conns(dir+'/dotfiles/merged_deduped.dot')
    write_extra_conns(dir+'/dotfiles/merged_deduped.dot', extra)"""
    get_complete_uml(dir+'/dotfiles/merged_deduped_final.dot', 'ModuleConnection')